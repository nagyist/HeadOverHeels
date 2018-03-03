
#include "Room.hpp"
#include "FloorTile.hpp"
#include "Wall.hpp"
#include "Item.hpp"
#include "GridItem.hpp"
#include "FreeItem.hpp"
#include "PlayerItem.hpp"
#include "Mediator.hpp"
#include "Camera.hpp"
#include "GameManager.hpp"
#include "Behavior.hpp"


namespace isomot
{

Room::Room( const std::string& roomFile, const std::string& scenery, int xTiles, int yTiles, int tileSize, const std::string& floor )
: Mediated( )
        , nameOfFileWithDataAboutRoom( roomFile )
        , scenery( scenery )
        , tileSize( tileSize )
        , kindOfFloor( floor )
        , wayOfExit( NoExit )
        , lastGridId( FirstGridId )
        , lastFreeId( FirstFreeId )
{
        playersYetInRoom.clear ();
        playersWhoEnteredRoom.clear ();

        this->numberOfTiles.first = xTiles;
        this->numberOfTiles.second = yTiles;
        this->mediator = new Mediator( this );
        this->camera = new Camera( this );

        this->bounds.clear ();
        this->bounds[ North ] = 64000;
        this->bounds[ South ] = 64000;
        this->bounds[ East ] = 64000;
        this->bounds[ West ] = 64000;
        this->bounds[ Northeast ] = 64000;
        this->bounds[ Southeast ] = 64000;
        this->bounds[ Southwest ] = 64000;
        this->bounds[ Northwest ] = 64000;
        this->bounds[ Eastnorth ] = 64000;
        this->bounds[ Eastsouth ] = 64000;
        this->bounds[ Westnorth ] = 64000;
        this->bounds[ Westsouth ] = 64000;

        this->doors.clear ();
        this->doors[ North ] = 0;
        this->doors[ South ] = 0;
        this->doors[ East ] = 0;
        this->doors[ West ] = 0;
        this->doors[ Northeast ] = 0;
        this->doors[ Southeast ] = 0;
        this->doors[ Southwest ] = 0;
        this->doors[ Northwest ] = 0;
        this->doors[ Eastnorth ] = 0;
        this->doors[ Eastsouth ] = 0;
        this->doors[ Westnorth ] = 0;
        this->doors[ Westsouth ] = 0;

        // create empty floor
        for ( int i = 0; i < xTiles * yTiles + 1; i++ )
        {
                this->floor.push_back( nilPointer );
        }

        // Creación del vector de índices. Asigna el contenido de los elementos de la siguiente forma
        // para, por ejemplo, una rejilla de 8 x 8, donde la longitud de "drawIndex" es 64
        //
        // Elemento del vector
        //                00
        //              02  01
        //            05  04  03
        //          09  08  07  06
        //        14  13  12  11  10
        //      20  19  18  17  16  15
        //    27  26  25  24  23  22  21
        //  35  34  33  32  31  30  29  28
        //    42  41  40  39  38  37  36
        //      48  47  46  45  44  43
        //        53  52  51  50  49
        //          57  56  55  54
        //            60  59  58
        //              62  61
        //                63
        //
        // Contenido del elemento
        //                00
        //              01  08
        //            02  09  16
        //          03  10  17  24
        //        04  11  18  25  32
        //      05  12  19  26  33  40
        //    06  13  20  27  34  41  48
        //  07  14  21  28  35  42  49  56
        //    15  22  29  36  43  50  57
        //      23  30  37  44  51  58
        //        31  38  45  52  59
        //          39  46  53  60
        //            47  54  61
        //              55  62
        //                63

        int pos = 0;
        this->drawIndex = new int[ xTiles * yTiles ];

        for ( int f = 0; f <= ( xTiles + yTiles - 1 ); f++ )
        {
                for ( int n = yTiles - 1; n >= 0; n-- )
                {
                        int temp = n * ( xTiles - 1 ) + f;
                        if ( ( temp >= n * xTiles ) && ( temp < ( n + 1 ) * xTiles ) )
                        {
                                this->drawIndex[ pos++ ] = temp;
                        }
                }
        }

        // Crea la imagen with suitable dimensions to draw the active room
        // single room ( id est up to 10 x 10 tiles ) just fits to the screen
        // but the image for double or triple room is larger
        if ( xTiles <= 10 && yTiles <= 10 )
        {
                picture = create_bitmap_ex( 32, ScreenWidth, ScreenHeight );
        }
        else if ( xTiles > 10 && yTiles > 10 )
        {
                picture = create_bitmap_ex( 32, ScreenWidth + 20 * ( tileSize << 1 ), ScreenHeight + 20 * tileSize );
        }
        else if ( xTiles > 10 || yTiles > 10 )
        {
                int w = ScreenWidth + ( xTiles > 10 ? ( ( xTiles - 10 ) * ( tileSize << 1 ) ) : 0 )
                                        + ( yTiles > 10 ? ( ( yTiles - 10 ) * ( tileSize << 1 ) ) : 0 );
                int h = ScreenHeight + ( xTiles > 10 ? ( ( xTiles - 10 ) * tileSize) : 0 )
                                        + ( yTiles > 10 ? ( ( yTiles - 10 ) * tileSize) : 0 );
                picture = create_bitmap_ex( 32, w, h );
        }

        // 128 for 50% opacity of shading or 256 for no shadows
        this->shadingScale = isomot::GameManager::getInstance()->getDrawShadows () ? 128 : 256 ;

        // Ahora la sala ya está activa
        this->active = true;
}

Room::~Room()
{
        // bin doors
        for ( std::map< Way, Door * >::const_iterator mi = doors.begin (); mi != doors.end (); ++mi )
        {
                delete mi->second ;
        }

        // bin floor
        std::for_each( floor.begin (), floor.end (), DeleteObject() );

        // bin walls
        std::for_each( wallX.begin (), wallX.end (), DeleteObject() );
        std::for_each( wallY.begin (), wallY.end (), DeleteObject() );

        // bin sequence of drawing
        delete[ ] drawIndex;

        delete camera;

        delete mediator;

        // bin players

        while ( ! this->playersYetInRoom.empty () )
        {
                PlayerItem* player = *( playersYetInRoom.begin () );
                playersYetInRoom.remove( player );
                delete player;
        }

        while ( ! this->playersWhoEnteredRoom.empty () )
        {
                const PlayerItem* player = *( playersWhoEnteredRoom.begin () );
                playersWhoEnteredRoom.remove( player );
                delete player;
        }

        destroy_bitmap( picture );
}

std::list < PlayerItem * > Room::getPlayersYetInRoom () const
{
        return playersYetInRoom ;
}

std::list < const PlayerItem * > Room::getPlayersWhoEnteredRoom () const
{
        return playersWhoEnteredRoom ;
}

void Room::addFloor( FloorTile * floorTile )
{
        floorTile->setMediator( mediator );
        floorTile->calculateOffset();

        this->floor[ floorTile->getColumn() ] = floorTile;
}

void Room::addWall( Wall * wall )
{
        wall->setMediator( mediator );
        wall->calculateOffset();

        if ( wall->isOnX() )
        {
                this->wallX.push_back( wall );
        }
        else
        {
                this->wallY.push_back( wall );
        }
}

void Room::addDoor( Door * door )
{
        door->setMediator( mediator );
        this->doors[ door->getWhereIsDoor() ] = door;

        // each door is actually three free items
        this->addFreeItem( door->getLeftJamb() );
        this->addFreeItem( door->getRightJamb() );
        this->addFreeItem( door->getLintel() );
}

void Room::addGridItem( GridItem * gridItem )
{
        if ( gridItem == nilPointer ) return;

        if ( ( gridItem->getCellX() < 0 || gridItem->getCellY() < 0 ) ||
                ( gridItem->getCellX() >= static_cast< int >( this->numberOfTiles.first ) ||
                        gridItem->getCellY() >= static_cast< int >( this->numberOfTiles.second ) ) )
        {
                std::cerr << "coordinates for " << gridItem->whichKindOfItem() << " are out of limits" << std::endl ;
                return;
        }

        if ( gridItem->getHeight() < 1 )
        {
                std::cerr << "can’t add " << gridItem->whichKindOfItem() << " which height is zero" << std::endl ;
                return;
        }

        mediator->clearStackOfCollisions ();

        // Asigna el identificador de Isomot
        gridItem->setId( this->lastGridId );

        // Si el elemento se va a colocar a una altura específica se buscan colisiones
        if ( gridItem->getZ() != Top )
        {
                mediator->findCollisionWithItem( gridItem );
        }
        // Si el elemento se va en los más alto de la columna se busca el valor de Z
        else
        {
                gridItem->setZ( mediator->findHighestZ( gridItem ) );
        }

        // Si se encontraron colisiones el elemento no se puede añadir
        if ( ! mediator->isStackOfCollisionsEmpty () )
        {
                std::cerr << "collision with " << gridItem->whichKindOfItem() << std::endl ;
                return;
        }

        // calculate offset of item’s image from origin of room
        if ( gridItem->getRawImage() )
        {
                std::pair< int, int > offset (
                        ( ( this->tileSize * ( gridItem->getCellX() - gridItem->getCellY() ) ) << 1 ) - ( gridItem->getRawImage()->w >> 1 ) + 1,
                        this->tileSize * ( gridItem->getCellX() + gridItem->getCellY() + 2 ) - gridItem->getRawImage()->h - gridItem->getZ() - 1
                ) ;
                gridItem->setOffset( offset );
        }

        /* std::cout << "add " << gridItem->whichKindOfItem() << " \"" << gridItem->getLabel() << "\" to room \"" << getNameOfFileWithDataAboutRoom() << "\"" << std::endl ; */

        gridItem->setMediator( mediator );
        gridItem->setColumn( this->numberOfTiles.first * gridItem->getCellY() + gridItem->getCellX() );
        mediator->addItem( gridItem );

        if ( this->shadingScale < 256 && gridItem->getImageOfShadow() )
        {
                mediator->reshadeGridItem( gridItem );
        }

        mediator->remaskGridItem( gridItem );

        this->lastGridId += 2;
}

void Room::addFreeItem( FreeItem * freeItem )
{
        if ( freeItem == nilPointer ) return;

        if ( freeItem->getX() < 0 || freeItem->getY() < 1 || freeItem->getZ() < Top )
        {
                std::cerr << "coordinates for " << freeItem->whichKindOfItem() << " are out of limits" << std::endl ;
                dumpItemInsideThisRoom( freeItem );
                return;
        }

        if ( freeItem->getHeight() < 1 || freeItem->getWidthX() < 1 || freeItem->getWidthY() < 1 )
        {
                std::cerr << "can’t add " << freeItem->whichKindOfItem() << " which dimension is zero" << std::endl ;
                return;
        }

        // El elemento no puede estar fuera de la sala
        if ( ( freeItem->getX() + static_cast< int >( freeItem->getWidthX() ) > static_cast< int >( this->numberOfTiles.first * this->tileSize ) )
                || ( freeItem->getY() - static_cast< int >( freeItem->getWidthY() ) < -1 )
                || ( freeItem->getY() > static_cast< int >( this->numberOfTiles.second * this->tileSize ) - 1 ) )
        {
                std::cerr << "coordinates for " << freeItem->whichKindOfItem() << " are out of room" << std::endl ;
                dumpItemInsideThisRoom( freeItem );
                return;
        }

        // Vacía la pila de colisiones
        mediator->clearStackOfCollisions ();

        // Asigna el identificador de Isomot
        freeItem->setId( this->lastFreeId );

        // Si el elemento se va a colocar a una altura específica se buscan colisiones
        if ( freeItem->getZ() > Top )
        {
                mediator->findCollisionWithItem( freeItem );
        }
        // Si el elemento se va en los más alto de la columna se busca el valor de Z
        else
        {
                freeItem->setZ( mediator->findHighestZ( freeItem ) );
        }

        // Si se encontraron colisiones el elemento no se puede añadir
        if ( ! mediator->isStackOfCollisionsEmpty () )
        {
                std::cerr << "collision with " << freeItem->whichKindOfItem() << std::endl ;
                dumpItemInsideThisRoom( freeItem );
                return;
        }

        // calculate offset of item’s image from origin of room
        if ( freeItem->getRawImage () )
        {
                std::pair< int, int > offset (
                        ( ( freeItem->getX() - freeItem->getY() ) << 1 ) + freeItem->getWidthX() + freeItem->getWidthY() - ( freeItem->getRawImage()->w >> 1 ) - 1,
                        freeItem->getX() + freeItem->getY() + freeItem->getWidthX() - freeItem->getRawImage()->h - freeItem->getZ()
                ) ;
                freeItem->setOffset( offset );
        }

        // add free item to room
        freeItem->setMediator( mediator );
        mediator->addItem( freeItem );

        if ( this->shadingScale < 256 && freeItem->getImageOfShadow() )
        {
                mediator->reshadeFreeItem( freeItem );
        }

        mediator->remaskFreeItem( freeItem );

        this->lastFreeId += 2;
}

bool Room::addPlayerToRoom( PlayerItem* playerItem, bool playerEntersRoom )
{
        if ( playerItem == nilPointer ) return false;

        for ( std::list< PlayerItem * >::const_iterator pi = playersYetInRoom.begin (); pi != playersYetInRoom.end (); ++pi )
        {
                if ( playerItem == *pi )
                {
                        // player is in room already
                        return false;
                }
        }

        if ( playerEntersRoom )
        {
                for ( std::list< const PlayerItem * >::const_iterator epi = playersWhoEnteredRoom.begin (); epi != playersWhoEnteredRoom.end (); ++epi )
                {
                        const PlayerItem* enteredPlayer = *epi ;

                        if ( enteredPlayer->getLabel() == "headoverheels" && playerItem->getLabel() != "headoverheels" )
                        {
                                // case when joined character enters room, splits in this room, and one of characters exits & re~enters
                                std::cout << "player \"" << playerItem->getLabel() << "\" enters but joined \"headoverheels\" entered the same room before" << std::endl ;

                                // bin joined character
                                this->playersWhoEnteredRoom.remove( enteredPlayer );
                                /*  epi-- ;  */
                                delete enteredPlayer ;

                                // add copy of another character as entered
                                copyAnotherCharacterAsEntered( playerItem->getLabel() );

                                break;
                        }

                        if ( enteredPlayer->getLabel() == playerItem->getLabel() )
                        {
                                // case when character returns back to this room, maybe via different way
                                std::cout << "player \"" << playerItem->getLabel() << "\" already entered this room some time ago" << std::endl ;

                                // bin previous entry
                                this->playersWhoEnteredRoom.remove( enteredPlayer );
                                /*  epi-- ;  */
                                delete enteredPlayer ;
                                break;
                        }
                }
        }

        if ( playerItem->getX() < 0 || playerItem->getY() < 1 || playerItem->getZ() < Top )
        {
                std::cerr << "coordinates for " << playerItem->whichKindOfItem() << " are out of limits" << std::endl ;
                dumpItemInsideThisRoom( playerItem );
                return false;
        }

        if ( playerItem->getHeight() < 1 || playerItem->getWidthX() < 1 || playerItem->getWidthY() < 1 )
        {
                std::cerr << "can’t add " << playerItem->whichKindOfItem() << " which dimension is zero" << std::endl ;
                return false;
        }

        if ( ( playerItem->getX() + static_cast< int >( playerItem->getWidthX() ) > static_cast< int >( this->numberOfTiles.first * this->tileSize ) )
                || ( playerItem->getY() - static_cast< int >( playerItem->getWidthY() ) < -1 )
                || ( playerItem->getY() > static_cast< int >( this->numberOfTiles.second * this->tileSize ) - 1 ) )
        {
                std::cerr << "coordinates for " << playerItem->whichKindOfItem() << " are out of room" << std::endl ;
                dumpItemInsideThisRoom( playerItem );
                return false;
        }

        mediator->clearStackOfCollisions ();

        // assign identifier for item
        playerItem->setId( this->lastFreeId );

        // for item which is placed at some height, look for collisions
        if ( playerItem->getZ() > Top )
        {
                mediator->findCollisionWithItem( playerItem );
                while ( ! mediator->isStackOfCollisionsEmpty () )
                {
                        playerItem->setZ( playerItem->getZ() + LayerHeight );
                        mediator->clearStackOfCollisions ();
                        mediator->findCollisionWithItem( playerItem );
                }
        }
        // for item at the top of column
        else
        {
                playerItem->setZ( mediator->findHighestZ( playerItem ) );
        }

        // collision is found, so can’t add this item
        if ( ! mediator->isStackOfCollisionsEmpty () )
        {
                std::cerr << "collision with " << playerItem->whichKindOfItem() << std::endl ;
                dumpItemInsideThisRoom( playerItem );
                return false;
        }

        // set offset of player’s image from origin of room
        if ( playerItem->getRawImage () )
        {
                std::pair< int, int > offset (
                        ( ( playerItem->getX() - playerItem->getY() ) << 1 ) + playerItem->getWidthX() + playerItem->getWidthY() - ( playerItem->getRawImage()->w >> 1 ) - 1,
                        playerItem->getX() + playerItem->getY() + playerItem->getWidthX() - playerItem->getRawImage()->h - playerItem->getZ()
                ) ;
                playerItem->setOffset( offset );
        }

        playerItem->setMediator( mediator );
        mediator->addItem( playerItem );

        if ( this->shadingScale < 256 && playerItem->getImageOfShadow() )
        {
                mediator->reshadeFreeItem( playerItem );
        }

        mediator->remaskFreeItem( playerItem );

        // add player item to room
        this->playersYetInRoom.push_back( playerItem );
        std::cout << "player \"" << playerItem->getLabel() << "\" is now in room \"" << nameOfFileWithDataAboutRoom << "\"" << std::endl ;

        if ( playerEntersRoom )
        {
                PlayerItem* copyOfPlayer = new PlayerItem( *playerItem );
                copyOfPlayer->assignBehavior( playerItem->getBehavior()->getNameOfBehavior(), playerItem->getDataOfItem() );
                this->playersWhoEnteredRoom.push_back( copyOfPlayer );

                std::cout << "copy of player \"" << copyOfPlayer->getLabel() << "\""
                                << " with behavior \"" << copyOfPlayer->getBehavior()->getNameOfBehavior() << "\""
                                << " is created to rebuild this room" << std::endl ;
        }

        this->lastFreeId += 2;

        return true;
}

void Room::dumpItemInsideThisRoom( const Item* item )
{
        std::cout << "   " << item->whichKindOfItem()
                        << " at " << item->getX() << " " << item->getY() << " " << item->getZ()
                        << " with dimensions " << item->getWidthX() << " x " << item->getWidthY() << " x " << item->getHeight()
                        << std::endl
                        << "   inside room \"" << this->nameOfFileWithDataAboutRoom << "\""
                        << " of " << this->numberOfTiles.first << " x " << this->numberOfTiles.second << " tiles"
                        << " each tile of " << this->tileSize << " pixels"
                        << std::endl ;
}

void Room::copyAnotherCharacterAsEntered( const std::string& name )
{
        for ( std::list< PlayerItem * >::const_iterator pi = playersYetInRoom.begin (); pi != playersYetInRoom.end (); ++pi )
        {
                if ( ( *pi )->getLabel() != name )
                {
                        bool alreadyThere = false;

                        for ( std::list< const PlayerItem * >::const_iterator epi = playersWhoEnteredRoom.begin (); epi != playersWhoEnteredRoom.end (); ++epi )
                        {
                                if ( ( *epi )->getLabel() == ( *pi )->getLabel() )
                                {
                                        alreadyThere = true;
                                        break;
                                }
                        }

                        if ( ! alreadyThere )
                        {
                                PlayerItem* copy = new PlayerItem( *( *pi ) );
                                copy->assignBehavior( ( *pi )->getBehavior()->getNameOfBehavior(), ( *pi )->getDataOfItem() );
                                copy->setWayOfEntry( JustWait );

                                playersWhoEnteredRoom.push_back( copy );
                        }
                }
        }
}

void Room::removeFloor( FloorTile * floorTile )
{
        this->floor[ floorTile->getColumn () ] = nilPointer;
        delete floorTile;
}

void Room::removeGridItem( GridItem * gridItem )
{
        try
        {
                mediator->removeItem( gridItem );

                if ( this->shadingScale < 256 && gridItem->getImageOfShadow() )
                {
                        mediator->reshadeGridItem( gridItem );
                }

                mediator->remaskGridItem( gridItem );

                delete gridItem;
        }
        catch ( const std::exception& e )
        {
                std::cout << e.what () << std::endl ;
        }
}

void Room::removeFreeItem( FreeItem * freeItem )
{
        try
        {
                mediator->removeItem( freeItem );

                if ( this->shadingScale < 256 && freeItem->getImageOfShadow() )
                {
                        mediator->reshadeFreeItem( freeItem );
                }

                mediator->remaskFreeItem( freeItem );

                delete freeItem;
        }
        catch ( const std::exception& e )
        {
                std::cout << e.what () << std::endl ;
        }
}

bool Room::removePlayerFromRoom( PlayerItem* playerItem, bool playerExitsRoom )
{
        for ( std::list< PlayerItem * >::const_iterator pi = playersYetInRoom.begin (); pi != playersYetInRoom.end (); ++pi )
        {
                if ( playerItem == *pi )
                {
                        mediator->removeItem( playerItem );

                        if ( this->shadingScale < 256 && playerItem->getImageOfShadow() )
                        {
                                mediator->reshadeFreeItem( playerItem );
                        }

                        mediator->remaskFreeItem( playerItem );

                        if ( playerItem == mediator->getActivePlayer() )
                        {
                                PlayerItem* nextPlayer = mediator->getWaitingPlayer();

                                if ( nextPlayer != nilPointer )
                                {
                                        // activate other player in room
                                        mediator->setActivePlayer( nextPlayer );

                                        std::cout << "player \"" << nextPlayer->getLabel() << "\""
                                                        << " is yet active in room \"" << getNameOfFileWithDataAboutRoom() << "\""
                                                        << std::endl ;
                                }
                        }

                        std::string nameOfPlayer = playerItem->getLabel();

                        std::cout << "removing player \"" << nameOfPlayer << "\""
                                        << " from room \"" << getNameOfFileWithDataAboutRoom() << "\""
                                                << std::endl ;

                        this->playersYetInRoom.remove( playerItem );
                        /// pi --; // not needed, this iteration is last one due to "return" below

                        delete playerItem;

                        // when player leaves room, bin its copy on entry
                        if ( playerExitsRoom )
                        {
                                for ( std::list< const PlayerItem * >::const_iterator epi = playersWhoEnteredRoom.begin (); epi != playersWhoEnteredRoom.end (); ++epi )
                                {
                                        const PlayerItem* enteredPlayer = *epi ;

                                        if ( enteredPlayer->getLabel() == nameOfPlayer )
                                        {
                                                std::cout << "also removing copy of player \"" << nameOfPlayer << "\" created on entry to this room" << std::endl ;

                                                this->playersWhoEnteredRoom.remove( enteredPlayer );
                                                /// epi-- ; // not needed because of "break"
                                                delete enteredPlayer ;
                                                break;
                                        }
                                }
                        }

                        return true;
                }
        }

        return false;
}

bool Room::isAnyPlayerStillInRoom () const
{
        return ! this->playersYetInRoom.empty () ;
}

void Room::removeBars ()
{
        std::list< FreeItem * > freeItems = this->mediator->getFreeItems ();
        unsigned int howManyBars = 0;

        for ( std::list< FreeItem * >::iterator fi = freeItems.begin (); fi != freeItems.end (); ++fi )
        {
                if ( ( *fi )->getLabel() == "bars-ns" || ( *fi )->getLabel() == "bars-ew" )
                {
                        this->removeFreeItem( *fi );
                        howManyBars ++;
                }
        }

        if ( howManyBars > 0 )
                std::cout << howManyBars << " bars are gone" << std::endl ;
}

void Room::draw( BITMAP* where )
{
        const unsigned int maxTilesOfSingleRoom = 10 ;

        // draw room when it is active
        if ( active )
        {
                // draw in picture of room itself when destination bitmap isn’t given
                if ( where == nilPointer )
                        where = this->picture ;

                // clean the image where to draw this room
                clear_bitmap( where );

                // acquire video memory before drawing
                if ( is_video_bitmap( where ) )
                {
                        acquire_bitmap( where );
                }

                // adjust position of camera
                if ( numberOfTiles.first > maxTilesOfSingleRoom || numberOfTiles.second > maxTilesOfSingleRoom )
                {
                        camera->centerOn( mediator->getActivePlayer () );
                }

                // draw tiles of room
                for ( unsigned int xCell = 0; xCell < this->numberOfTiles.first; xCell++ )
                {
                        for ( unsigned int yCell = 0; yCell < this->numberOfTiles.second; yCell++ )
                        {
                                unsigned int column = this->numberOfTiles.first * yCell + xCell;

                                if ( floor[ column ] != nilPointer )  // if there is tile of floor here
                                {
                                        // shade this tile when shadows are on
                                        if ( shadingScale < 256 && floor[ column ]->getRawImage() )
                                        {
                                                mediator->lockGridItemMutex();
                                                mediator->lockFreeItemMutex();

                                                floor[ column ]->requestShadow();

                                                mediator->unlockGridItemMutex();
                                                mediator->unlockFreeItemMutex();
                                        }

                                        // draw this tile o’floor
                                        floor[ column ]->draw( where );
                                }
                        }
                }

                // draw walls without doors
                for ( std::vector< Wall * >::iterator wx = this->wallX.begin (); wx != this->wallX.end (); ++wx )
                {
                        ( *wx )->draw( where );
                }
                for ( std::vector< Wall * >::iterator wy = this->wallY.begin (); wy != this->wallY.end (); ++wy )
                {
                        ( *wy )->draw( where );
                }

                mediator->lockGridItemMutex();
                mediator->lockFreeItemMutex();

                // draw grid items
                for ( unsigned int i = 0; i < this->numberOfTiles.first * this->numberOfTiles.second; i++ )
                {
                        for ( std::list< GridItem * >::iterator g = mediator->structure[ drawIndex[ i ] ].begin (); g != mediator->structure[ drawIndex[ i ] ].end (); ++g )
                        {
                                GridItem* gridItem = static_cast< GridItem * >( *g );

                                if ( shadingScale < 256 && gridItem->getRawImage() )
                                {
                                        gridItem->requestCastShadow( drawIndex[ i ] );
                                }

                                gridItem->draw( where );
                        }
                }

                // for free items there’re two steps of drawing

                // at first shade them with both of grid items and other free items
                for ( std::list< FreeItem * >::iterator f = mediator->freeItems.begin (); f != mediator->freeItems.end (); ++f )
                {
                        FreeItem* freeItem = static_cast< FreeItem * >( *f );

                        if ( freeItem->getRawImage() )
                        {
                                // shade an item when shadows are on
                                if ( shadingScale < 256 )
                                        freeItem->requestCastShadow();
                        }
                }

                // then mask them and finally draw them
                for ( std::list< FreeItem * >::iterator f = mediator->freeItems.begin (); f != mediator->freeItems.end (); ++f )
                {
                        FreeItem* freeItem = static_cast< FreeItem * >( *f );

                        if ( freeItem->getRawImage() )
                        {
                                freeItem->requestMask();
                                freeItem->draw( where );
                        }
                }

                mediator->unlockGridItemMutex();
                mediator->unlockFreeItemMutex();

                // free used video memory after drawing
                if ( is_video_bitmap( where ) )
                {
                        release_bitmap( where );
                }
        }
}

void Room::calculateBounds()
{
        bounds[ North ] = doors[ North ] || doors[ Northeast ] || doors[ Northwest ] || this->kindOfFloor == "none" ? tileSize : 0;
        bounds[ East ] = doors[ East ] || doors[ Eastnorth ] || doors[ Eastsouth ] || this->kindOfFloor == "none" ? tileSize : 0;
        bounds[ South ] = tileSize * numberOfTiles.first - ( doors[ South ] || doors[ Southeast ] || doors[ Southwest ]  ? tileSize : 0 );
        bounds[ West ] = tileSize * numberOfTiles.second - ( doors[ West ] || doors[ Westnorth ] || doors[ Westsouth ]  ? tileSize : 0 );

        // door limits of triple room
        bounds[ Northeast ] = doors[ Northeast ] ? doors[ Northeast ]->getLintel()->getX() + doors[ Northeast ]->getLintel()->getWidthX() - tileSize : bounds[ North ];
        bounds[ Northwest ] = doors[ Northwest ] ? doors[ Northwest ]->getLintel()->getX() + doors[ Northwest ]->getLintel()->getWidthX() - tileSize : bounds[ North ];
        bounds[ Southeast ] = doors[ Southeast ] ? doors[ Southeast ]->getLintel()->getX() + tileSize : bounds[ South ];
        bounds[ Southwest ] = doors[ Southwest ] ? doors[ Southwest ]->getLintel()->getX() + tileSize : bounds[ South ];
        bounds[ Eastnorth ] = doors[ Eastnorth ] ? doors[ Eastnorth ]->getLintel()->getY() + doors[ Eastnorth ]->getLintel()->getWidthY() - tileSize : bounds[ East ];
        bounds[ Eastsouth ] = doors[ Eastsouth ] ? doors[ Eastsouth ]->getLintel()->getY() + doors[ Eastsouth ]->getLintel()->getWidthY() - tileSize : bounds[ East ];
        bounds[ Westnorth ] = doors[ Westnorth ] ? doors[ Westnorth ]->getLintel()->getY() + tileSize : bounds[ West ];
        bounds[ Westsouth ] = doors[ Westsouth ] ? doors[ Westsouth ]->getLintel()->getY() + tileSize : bounds[ West ];
}

void Room::calculateCoordinates( bool hasNorthDoor, bool hasEastDoor, int deltaX, int deltaY )
{
        // Para calcular las coordenadas no se tiene en cuenta las losetas ocupadas por las puertas y sus muros
        int xGrid = hasNorthDoor || this->kindOfFloor == "none" ? numberOfTiles.first - 1 : numberOfTiles.first;
        int yGrid = hasEastDoor || this->kindOfFloor == "none" ? numberOfTiles.second - 1 : numberOfTiles.second;

        // Si las variables son impares quiere decir que hay puertas al sur y/o al oeste
        // Se resta 1 en tal caso para obtener el número de losetas hábiles de la sala
        xGrid += ( xGrid & 1 ? -1 : 0 );
        yGrid += ( yGrid & 1 ? -1 : 0 );

        // Para una sala de 8x8 (sin contar las puertas) el punto origen es x = anchura_imagen/2 e y = altura_imagen/3
        // Para una sala de dimensiones menores se desplaza el punto origen de tal manera que quede centrado
        // en la rejilla de 8x8. Por ejemplo: para una sala de 8x6, se desplaza la coordenada Y una loseta a la
        // izquierda respecto del punto origen
        int middlePointX = ( xGrid > 8 || yGrid > 8 ? picture->w : ScreenWidth ) >> 1;
        this->coordinates.first = middlePointX
                                - ( hasNorthDoor || this->kindOfFloor == "none" ? ( tileSize << 1 ) : 0)
                                + ( hasEastDoor || this->kindOfFloor == "none" ? ( tileSize << 1 ) : 0 );
        this->coordinates.second = ( ScreenHeight / 3 - deltaY )
                                 - ( hasNorthDoor || this->kindOfFloor == "none" ? tileSize : 0 )
                                 - ( hasEastDoor || this->kindOfFloor == "none" ? tileSize : 0 );

        if ( xGrid <= 8 && yGrid <= 8 )
        {
                this->coordinates.first += ( yGrid - xGrid ) * tileSize;
                this->coordinates.second += ( ( 16 - xGrid - yGrid ) >> 1 ) * tileSize;
        }
        else
        {
                this->coordinates.first = ( picture->w - ( ( xGrid + yGrid ) * ( tileSize << 1 ) ) ) / 2
                                        + ( yGrid * ( tileSize << 1 ) )
                                        - ( hasNorthDoor ? ( tileSize << 1 ) : 0 )
                                        + ( hasEastDoor ? ( tileSize << 1 ) : 0 );
        }
}

bool Room::activatePlayerByName( const std::string& player )
{
        for ( std::list< PlayerItem * >::const_iterator pi = playersYetInRoom.begin (); pi != playersYetInRoom.end (); ++pi )
        {
                if ( player == ( *pi )->getLabel() )
                {
                        mediator->setActivePlayer( *pi );
                        return true;
                }
        }

        return false;
}

void Room::activate()
{
        this->mediator->beginUpdate();
        this->active = true;
}

void Room::deactivate()
{
        this->mediator->endUpdate();
        this->active = false;
}

bool Room::swapPlayersInRoom ( ItemDataManager * itemDataManager )
{
        return mediator->selectNextPlayer( itemDataManager );
}

bool Room::continueWithAlivePlayer ( )
{
        PlayerItem* previouslyAlivePlayer = mediator->getActivePlayer();

        if ( previouslyAlivePlayer->getLives() == 0 )
        {
                // look for next player
                std::list< PlayerItem* >::iterator i =
                                std::find_if( this->playersYetInRoom.begin (), this->playersYetInRoom.end (),
                                                std::bind2nd( EqualLabelOfItem(), previouslyAlivePlayer->getLabel() ) );
                ++i ;
                mediator->setActivePlayer( i != this->playersYetInRoom.end () ? ( *i ) : *this->playersYetInRoom.begin () );

                // is there other alive player in room
                if ( previouslyAlivePlayer != mediator->getActivePlayer() )
                {
                        removePlayerFromRoom( previouslyAlivePlayer, true );

                        this->activate();
                        return true;
                }

                return false;
        }

        return true;
}

bool Room::calculateEntryCoordinates( const Way& wayOfEntry, int widthX, int widthY, int northBound, int eastBound, int southBound, int westBound, int* x, int* y, int* z )
{
        bool result = false;
        int differentSizeDeltaX = 0;
        int differentSizeDeltaY = 0;

        if ( wayOfEntry.toString() == "up" || wayOfEntry.toString() == "down" ||
                        wayOfEntry.toString() == "via teleport" || wayOfEntry.toString() == "via second teleport" )
        {
                const unsigned int maxTilesOfSingleRoom = 10 ;
                const int limitOfSingleRoom = maxTilesOfSingleRoom * tileSize ;

                // calculate the difference on X axis when moving from single room to double room or vice versa
                if ( ( bounds[ South ] - bounds[ North ] > limitOfSingleRoom && southBound - northBound <= limitOfSingleRoom ) ||
                        ( bounds[ South ] - bounds[ North ] <= limitOfSingleRoom && southBound - northBound > limitOfSingleRoom ) )
                {
                        differentSizeDeltaX = ( bounds[ South ] - bounds[ North ] - southBound + northBound ) >> 1;
                }

                // calculate the difference on Y axis when moving from single room to double room or vice versa
                if ( ( bounds[ West ] - bounds[ East ] > limitOfSingleRoom && westBound - eastBound <= limitOfSingleRoom ) ||
                        ( bounds[ West ] - bounds[ East ] <= limitOfSingleRoom && westBound - eastBound > limitOfSingleRoom ) )
                {
                        differentSizeDeltaY = ( bounds[ West ] - bounds[ East ] - westBound + eastBound ) >> 1;
                }
        }

        // calculate coordinates according to way of entry
        switch ( wayOfEntry.getIntegerOfWay () )
        {
                case North:
                        *x = bounds[ North ] - tileSize + 1;
                        *y = doors[ North ]->getLeftJamb()->getY() - doors[ North ]->getLeftJamb()->getWidthY();
                        *z = doors[ North ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case South:
                        *x = bounds[ South ] + tileSize - widthX;
                        *y = doors[ South ]->getLeftJamb()->getY() - doors[ South ]->getLeftJamb()->getWidthY();
                        *z = doors[ South ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case East:
                        *x = doors[ East ]->getLeftJamb()->getX() + doors[ East ]->getLeftJamb()->getWidthX();
                        *y = bounds[ East ] - tileSize + widthY;
                        *z = doors[ East ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case West:
                        *x = doors[ West ]->getLeftJamb()->getX() + doors[ West ]->getLeftJamb()->getWidthX();
                        *y = bounds[ West ] + tileSize - 1;
                        *z = doors[ West ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Northeast:
                        *x = bounds[ Northeast ];
                        *y = doors[ Northeast ]->getLeftJamb()->getY() - doors[ Northeast ]->getLeftJamb()->getWidthY();
                        *z = doors[ Northeast ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Northwest:
                        *x = bounds[ Northwest ];
                        *y = doors[ Northwest ]->getLeftJamb()->getY() - doors[ Northwest ]->getLeftJamb()->getWidthY();
                        *z = doors[ Northwest ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Southeast:
                        *x = bounds[ Southeast ] - widthX;
                        *y = doors[ Southeast ]->getLeftJamb()->getY() - doors[ Southeast ]->getLeftJamb()->getWidthY();
                        *z = doors[ Southeast ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Southwest:
                        *x = bounds[ Southwest ] - widthX;
                        *y = doors[ Southwest ]->getLeftJamb()->getY() - doors[ Southwest ]->getLeftJamb()->getWidthY();
                        *z = doors[ Southwest ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Eastnorth:
                        *x = doors[ Eastnorth ]->getLeftJamb()->getX() + doors[ Eastnorth ]->getLeftJamb()->getWidthX();
                        *y = bounds[ Eastnorth ] + widthY;
                        *z = doors[ Eastnorth ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Eastsouth:
                        *x = doors[ Eastsouth ]->getLeftJamb()->getX() + doors[ Eastsouth ]->getLeftJamb()->getWidthX();
                        *y = bounds[ Eastsouth ] + widthY;
                        *z = doors[ Eastsouth ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Westnorth:
                        *x = doors[ Westnorth ]->getLeftJamb()->getX() + doors[ Westnorth ]->getLeftJamb()->getWidthX();
                        *y = bounds[ Westnorth ] - widthY;
                        *z = doors[ Westnorth ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Westsouth:
                        *x = doors[ Westsouth ]->getLeftJamb()->getX() + doors[ Westsouth ]->getLeftJamb()->getWidthX();
                        *y = bounds[ Westsouth ] - widthY;
                        *z = doors[ Westsouth ]->getLeftJamb()->getZ();
                        result = true;
                        break;

                case Up:
                        *x += bounds[ North ] - northBound + ( ( bounds[ South ] - bounds[ North ] - southBound + northBound ) >> 1 );
                        *x += ( *x < ( ( bounds[ South ] - bounds[ North ] ) >> 1 ) ? -differentSizeDeltaX : differentSizeDeltaX );
                        *y += bounds[ East ] - eastBound + ( ( bounds[West] - bounds[East] - westBound + eastBound ) >> 1 );
                        *y += ( *y < ( ( bounds[ West ] - bounds[ East ] ) >> 1 ) ? -differentSizeDeltaY : differentSizeDeltaY );
                        *z = MaxLayers * LayerHeight;
                        result = true;
                        break;

                case Down:
                        *x += bounds[ North ] - northBound + ( ( bounds[ South ] - bounds[ North ] - southBound + northBound ) >> 1 );
                        *x += ( *x < ( ( bounds[ South ] - bounds[ North ] ) >> 1 ) ? -differentSizeDeltaX : differentSizeDeltaX );
                        *y += bounds[ East ] - eastBound + ( ( bounds[ West ] - bounds[ East ] - westBound + eastBound) >> 1 );
                        *y += ( *y < ( ( bounds[ West ] - bounds[ East ]) >> 1 ) ? -differentSizeDeltaY : differentSizeDeltaY );
                        *z = LayerHeight;
                        result = true;
                        break;

                case ByTeleport:
                case ByTeleportToo:
                        *x += bounds[ North ] - northBound + ( ( bounds[ South ] - bounds[ North ] - southBound + northBound ) >> 1 );
                        *x += ( *x < ( ( bounds[ South ] - bounds[ North ] ) >> 1 ) ? -differentSizeDeltaX : differentSizeDeltaX );
                        *y += differentSizeDeltaY + bounds[ East ] - eastBound + ( ( bounds[ West ] - bounds[ East ] - westBound + eastBound ) >> 1 );
                        *y += ( *y < ( ( bounds[ West ] - bounds[ East ] ) >> 1 ) ? -differentSizeDeltaY : differentSizeDeltaY );
                        result = true;
                        break;

                default:
                        ;
        }

        return result;
}

void Room::addTripleRoomInitialPoint( const Way& way, int x, int y )
{
        this->listOfInitialPointsForTripleRoom.push_back( TripleRoomInitialPoint( way, x, y ) );
}

void Room::assignTripleRoomBounds( int minX, int maxX, int minY, int maxY )
{
        this->tripleRoomBoundX.first = minX;
        this->tripleRoomBoundX.second = maxX;
        this->tripleRoomBoundY.first = minY;
        this->tripleRoomBoundY.second = maxY;
}

TripleRoomInitialPoint* Room::findInitialPointOfEntryToTripleRoom( const Way& way )
{
        std::list< TripleRoomInitialPoint >::iterator i = std::find_if(
                                                                listOfInitialPointsForTripleRoom.begin (),
                                                                listOfInitialPointsForTripleRoom.end (),
                                                                std::bind2nd( EqualTripleRoomInitialPoint(), way ) );

        return ( i != listOfInitialPointsForTripleRoom.end () ? ( &( *i ) ) : nilPointer );
}

TripleRoomInitialPoint::TripleRoomInitialPoint( const Way& way, int x, int y )
        : wayOfEntry( way )
        , x( x )
        , y( y )
{
}

bool EqualTripleRoomInitialPoint::operator()( TripleRoomInitialPoint point, const Way& wayOfEntry ) const
{
        return ( point.getWayOfEntry().getIntegerOfWay() == wayOfEntry.getIntegerOfWay() );
}

}
