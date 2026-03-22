
#include "Door.hpp"

#include "Color.hpp"
#include "DescriptionOfItem.hpp"
#include "ItemDescriptions.hpp"
#include "FreeItem.hpp"
#include "Mediator.hpp"
#include "GameManager.hpp"
#include "PoolOfPictures.hpp"
#include "UnlikelyToHappenException.hpp"

#include "util.hpp"
#include "ospaths.hpp"

#ifdef DEBUG
#  define SAVE_ITEM_FRAMES      0
#  define GRAYSCALE_JAMBS       0
#endif


Door::Door( const std::string & kind, int cx, int cy, int z, const std::string & on )
        : kindOfDoor( kind )
        , cellX( cx )
        , cellY( cy )
        , elevation( z )
        , onWhichSide( on )
        , leftJamb( nilPointer )
        , rightJamb( nilPointer )
        , lintel( nilPointer )
{
        // make sure the graphics of this door is loaded

        const DescriptionOfItem * whatIsLintel = ItemDescriptions::descriptions().getDescriptionByKind( kind + "~lintel" );

        if ( whatIsLintel == nilPointer ) {
                std::string message = "no description for the parts of " + kind ;
                std::cerr << message << std::endl ;
                throw UnlikelyToHappenException( message ) ;
        }

        const std::string & doorImageFile = whatIsLintel->getNameOfFramesFile() ;
        const NamedPicturePtr & pictureOfDoor = PoolOfPictures::getPoolOfPictures().getOrLoadAndGet( doorImageFile );

        if ( pictureOfDoor == nilPointer ) {
                std::string message = "the door graphics \"" + doorImageFile + "\" is absent" ;
                std::cerr << message << std::endl ;
                throw UnlikelyToHappenException( message ) ;
        }
}

/* static */
NamedPicture* Door::cutOutLintel( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                        unsigned int leftJambWidthX, unsigned int leftJambWidthY,
                                        unsigned int rightJambWidthX, unsigned int rightJambWidthY,
                                        const std::string & on )
{
        bool ns = ( on == "north" || on == "south" || on == "northeast" || on == "northwest" || on == "southeast" || on == "southwest" );

        unsigned int lintelWidth = ( widthX << 1 ) + ( widthY << 1 );
        unsigned int lintelHeight = height + widthY + widthX;

        NamedPicture * lintel = new NamedPicture( lintelWidth, lintelHeight );

        if ( ns )
        {
                allegro::bitBlit( door, lintel->getAllegroPict(), 0, 0, 0, 0, lintelWidth, height + widthX );

                unsigned int delta = lintelWidth;
                int noPixel = lintelWidth - ( ( rightJambWidthX + rightJambWidthY ) << 1 ) + 1;
                int yStart = noPixel;
                int yEnd = noPixel - 1;

                /////lintel->getAllegroPict().lockWriteOnly() ;

                for ( unsigned int yPic = height + widthX; yPic < lintelHeight; yPic++ ) {
                        for ( unsigned int xPic = delta; xPic > 0; xPic-- )
                        {
                                if ( yPic != height + widthX && ( static_cast< int >( xPic ) - 1 ) == noPixel )
                                {
                                        if ( noPixel > yEnd ) {
                                                noPixel -- ;
                                        }
                                        else {
                                                yStart += 2 ;
                                                noPixel = yStart;
                                        }
                                }
                                else if ( yPic < height + ( widthX << 1 ) || ( static_cast< int >( xPic ) - 1 ) < yEnd )
                                {
                                        lintel->getAllegroPict().putPixelAt( xPic - 1, yPic, door.getPixelAt( xPic - 1, yPic ) );
                                }
                        }

                        delta -= 2;
                }

                /////lintel->getAllegroPict().unlock() ;
        }
        else
        {
                allegro::bitBlit( door, lintel->getAllegroPict(), 0, 0, 0, 0, lintelWidth, height + widthY );

                unsigned int delta = 0;
                int noPixel = ( ( leftJambWidthX + leftJambWidthY ) << 1 ) - 2;
                int yStart = noPixel;
                int yEnd = noPixel + 1;

                /////lintel->getAllegroPict().lockWriteOnly() ;

                for ( unsigned int yPic = height + widthY; yPic < lintelHeight; yPic++ ) {
                        for ( unsigned int xPic = delta; xPic < lintelWidth; xPic++ )
                        {
                                if ( yPic != height + widthY && static_cast< int >( xPic ) == noPixel )
                                {
                                        if ( noPixel < yEnd ) {
                                                noPixel ++ ;
                                        }
                                        else {
                                                yStart -= 2 ;
                                                noPixel = yStart;
                                        }
                                }
                                else if ( yPic < height + ( widthY << 1 ) || static_cast< int >( xPic ) > yEnd )
                                {
                                        lintel->getAllegroPict().putPixelAt( xPic, yPic, door.getPixelAt( xPic, yPic ) );
                                }
                        }

                        delta += 2;
                }

                /////lintel->getAllegroPict().unlock() ;
        }

        return lintel ;
}

/* static */
NamedPicture* Door::cutOutLeftJamb( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                        /* unsigned int lintelWidthX, */ unsigned int lintelWidthY, unsigned int lintelHeight,
                                        const std::string & on )
{
        bool ns = ( on == "north" || on == "south" || on == "northeast" || on == "northwest" || on == "southeast" || on == "southwest" );
        unsigned int fixWidth = ( ns ? 7 : 0 );
        int fixY = ( ns ? -1 : 0 );

        NamedPicture * leftJamb = new NamedPicture( ( widthX << 1 ) + fixWidth + ( widthY << 1 ) , height + widthY + widthX ) ;

        allegro::bitBlit( door, leftJamb->getAllegroPict(),
                                fixY, lintelHeight + lintelWidthY - widthY + fixY,
                                0, 0,
                                leftJamb->getWidth(), leftJamb->getHeight() );

# if defined( GRAYSCALE_JAMBS ) && GRAYSCALE_JAMBS
        Color::pictureToGrayscale( leftJamb );
# endif

        return leftJamb ;
}

/* static */
NamedPicture* Door::cutOutRightJamb( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                        unsigned int lintelWidthX, /* unsigned int lintelWidthY, */ unsigned int lintelHeight,
                                        const std::string & on )
{
        bool ns = ( on == "north" || on == "south" || on == "northeast" || on == "northwest" || on == "southeast" || on == "southwest" );
        unsigned int fixWidth = ( ns ? 0 : 7 );
        int fixY = ( ns ? 0 : -2 );

        NamedPicture * rightJamb = new NamedPicture( ( widthX << 1 ) + fixWidth + ( widthY << 1 ) , height + widthY + widthX ) ;

        allegro::bitBlit( door, rightJamb->getAllegroPict(),
                                door.getW() - rightJamb->getWidth(), lintelHeight + lintelWidthX - widthY + fixY,
                                0, 0,
                                rightJamb->getWidth(), rightJamb->getHeight() );

# if defined( GRAYSCALE_JAMBS ) && GRAYSCALE_JAMBS
        Color::pictureToGrayscale( rightJamb );
# endif

        return rightJamb ;
}

const FreeItemPtr & Door::getLeftJamb()
{
        if ( this->leftJamb == nilPointer )
        {
                ItemDescriptions & descriptions = ItemDescriptions::descriptions() ;
                PoolOfPictures & imagePool = PoolOfPictures::getPoolOfPictures() ;

                const DescriptionOfItem & whatIsLeftJamb = * descriptions.getDescriptionByKind( getKind() + "~leftjamb" );

                const std::string & doorImageName = whatIsLeftJamb.getNameOfFramesFile() ;
                std::string leftJambName = "left jamb of " + doorImageName ;

                if ( imagePool.getPicture( leftJambName ) == nilPointer ) {
                        const DescriptionOfItem & whatIsLintel = * descriptions.getDescriptionByKind( getKind() + "~lintel" );

                        // cut out the left jamb
                        NamedPicture * leftJambCut = cutOutLeftJamb( imagePool.getPicture( doorImageName )->getAllegroPict(),
                                                whatIsLeftJamb.getWidthX(), whatIsLeftJamb.getWidthY(), whatIsLeftJamb.getHeight(),
                                                whatIsLintel.getWidthY(), whatIsLintel.getHeight(),
                                                getRoomSide() );

                        imagePool.putPicture( leftJambName, NamedPicturePtr( leftJambCut ) );

                # if defined( SAVE_ITEM_FRAMES ) && SAVE_ITEM_FRAMES
                        imagePool.getPicture( leftJambName )->saveAsPNG( ospaths::homePath() );
                # endif
                }

                const NamedPicturePtr & leftJambImage = imagePool.getPicture( leftJambName );
                if ( leftJambImage == nilPointer )
                        throw UnlikelyToHappenException( "nil image for the left jamb of " + getKind() );

                int oneCell = getMediator()->getRoom().getSizeOfOneCell ();

                int x = 0 ; int y = 0 ;

                switch ( Way( getRoomSide() ).toInteger() )
                {
                        case Way::North:
                        case Way::Northeast:
                        case Way::Northwest:
                                x = cellX * oneCell + whatIsLeftJamb.getWidthX() - 2 ;
                                y = ( cellY + 2 ) * oneCell - 2 ;
                                this->leftLimit = y + whatIsLeftJamb.getWidthY() ;
                                break;

                        case Way::South:
                        case Way::Southeast:
                        case Way::Southwest:
                                x = cellX * oneCell ;
                                y = ( cellY + 2 ) * oneCell - 2 ;
                                this->leftLimit = y + whatIsLeftJamb.getWidthY() ;
                                break;

                        case Way::East:
                        case Way::Eastnorth:
                        case Way::Eastsouth:
                                x = cellX * oneCell ;
                                y = ( cellY + 1 ) * oneCell - 1 ;
                                this->leftLimit = x + whatIsLeftJamb.getWidthX() ;
                                break;

                        case Way::West:
                        case Way::Westnorth:
                        case Way::Westsouth:
                                x = cellX * oneCell ;
                                y = ( cellY + 1 ) * oneCell - whatIsLeftJamb.getWidthY() + 1 ;
                                this->leftLimit = x + whatIsLeftJamb.getWidthX() ;
                                break;

                        default:
                                ;
                }

                leftJamb = FreeItemPtr( new FreeItem( whatIsLeftJamb, x, y, Room::FloorZ, onWhichSideOfTheFour() ) );
                leftJamb->addFrameTo( onWhichSideOfTheFour(), new NamedPicture( leftJambImage->getWidth(), leftJambImage->getHeight() ) );
                allegro::bitBlit( leftJambImage->getAllegroPict(), leftJamb->getCurrentRawImageToChangeIt ().getAllegroPict() );
                leftJamb->getCurrentRawImageToChangeIt().setName( leftJambImage->getName() );
                leftJamb->freshBothProcessedImages ();
                leftJamb->setUniqueName( leftJamb->getKind () + " " + util::makeRandomString( 8 ) );
        }

        return this->leftJamb ;
}

const FreeItemPtr & Door::getRightJamb()
{
        if ( this->rightJamb == nilPointer )
        {
                ItemDescriptions & descriptions = ItemDescriptions::descriptions() ;
                PoolOfPictures & imagePool = PoolOfPictures::getPoolOfPictures() ;

                const DescriptionOfItem & whatIsRightJamb = * descriptions.getDescriptionByKind( getKind() + "~rightjamb" );

                const std::string & doorImageName = whatIsRightJamb.getNameOfFramesFile() ;
                std::string rightJambName = "right jamb of " + doorImageName ;

                if ( imagePool.getPicture( rightJambName ) == nilPointer ) {
                        const DescriptionOfItem & whatIsLintel = * descriptions.getDescriptionByKind( getKind() + "~lintel" );

                        // cut out the right jamb
                        NamedPicture * rightJambCut = cutOutRightJamb( imagePool.getPicture( doorImageName )->getAllegroPict(),
                                                whatIsRightJamb.getWidthX(), whatIsRightJamb.getWidthY(), whatIsRightJamb.getHeight(),
                                                whatIsLintel.getWidthX(), whatIsLintel.getHeight(),
                                                getRoomSide() );

                        imagePool.putPicture( rightJambName, NamedPicturePtr( rightJambCut ) );

                # if defined( SAVE_ITEM_FRAMES ) && SAVE_ITEM_FRAMES
                        imagePool.getPicture( rightJambName )->saveAsPNG( ospaths::homePath() );
                # endif
                }

                const NamedPicturePtr & rightJambImage = imagePool.getOrLoadAndGet( rightJambName );
                if ( rightJambImage == nilPointer )
                        throw UnlikelyToHappenException( "nil image for the right jamb of " + getKind() );

                int oneCell = getMediator()->getRoom().getSizeOfOneCell ();

                int x = 0 ; int y = 0 ;

                switch ( Way( getRoomSide() ).toInteger() )
                {
                        case Way::North:
                        case Way::Northeast:
                        case Way::Northwest:
                                x = cellX * oneCell + whatIsRightJamb.getWidthX() - 2 ;
                                y = cellY * oneCell + whatIsRightJamb.getWidthY() - 1 ;
                                this->rightLimit = y ;
                                break;

                        case Way::South:
                        case Way::Southeast:
                        case Way::Southwest:
                                x = cellX * oneCell ;
                                y = cellY * oneCell + whatIsRightJamb.getWidthY() - 1 ;
                                this->rightLimit = y ;
                                break;

                        case Way::East:
                        case Way::Eastnorth:
                        case Way::Eastsouth:
                                x = ( cellX + 2 ) * oneCell - whatIsRightJamb.getWidthX() - 2 ;
                                y = ( cellY + 1 ) * oneCell - 1 ;
                                this->rightLimit = x ;
                                break;

                        case Way::West:
                        case Way::Westnorth:
                        case Way::Westsouth:
                                x = ( cellX + 2 ) * oneCell - whatIsRightJamb.getWidthX() - 2 ;
                                y = ( cellY + 1 ) * oneCell - whatIsRightJamb.getWidthY() + 1 ;
                                this->rightLimit = x ;
                                break;

                        default:
                                ;
                }

                rightJamb = FreeItemPtr( new FreeItem( whatIsRightJamb, x, y, Room::FloorZ, onWhichSideOfTheFour() ) );
                rightJamb->addFrameTo( onWhichSideOfTheFour(), new NamedPicture( rightJambImage->getWidth(), rightJambImage->getHeight() ) );
                allegro::bitBlit( rightJambImage->getAllegroPict(), rightJamb->getCurrentRawImageToChangeIt ().getAllegroPict() );
                rightJamb->getCurrentRawImageToChangeIt().setName( rightJambImage->getName() );
                rightJamb->freshBothProcessedImages ();
                rightJamb->setUniqueName( rightJamb->getKind () + " " + util::makeRandomString( 8 ) );
        }

        return this->rightJamb ;
}

const FreeItemPtr & Door::getLintel()
{
        if ( this->lintel == nilPointer )
        {
                ItemDescriptions & descriptions = ItemDescriptions::descriptions() ;
                PoolOfPictures & imagePool = PoolOfPictures::getPoolOfPictures() ;

                const DescriptionOfItem & whatIsLintel = * descriptions.getDescriptionByKind( getKind() + "~lintel" );

                const std::string & doorImageName = whatIsLintel.getNameOfFramesFile() ;
                std::string lintelName = "lintel of " + doorImageName ;

                if ( imagePool.getPicture( lintelName ) == nilPointer ) {
                        const DescriptionOfItem & whatIsLeftJamb = * descriptions.getDescriptionByKind( getKind() + "~leftjamb" );
                        const DescriptionOfItem & whatIsRightJamb = * descriptions.getDescriptionByKind( getKind() + "~rightjamb" );

                        // cut out the lintel
                        NamedPicture * lintelCut = cutOutLintel( imagePool.getPicture( doorImageName )->getAllegroPict(),
                                                whatIsLintel.getWidthX(), whatIsLintel.getWidthY(), whatIsLintel.getHeight(),
                                                whatIsLeftJamb.getWidthX(), whatIsLeftJamb.getWidthY(),
                                                whatIsRightJamb.getWidthX(), whatIsRightJamb.getWidthY(),
                                                getRoomSide() );

                        imagePool.putPicture( lintelName, NamedPicturePtr( lintelCut ) );

                # if defined( SAVE_ITEM_FRAMES ) && SAVE_ITEM_FRAMES
                        imagePool.getPicture( lintelName )->saveAsPNG( ospaths::homePath() );
                # endif
                }

                const NamedPicturePtr & lintelImage = imagePool.getOrLoadAndGet( lintelName );
                if ( lintelImage == nilPointer )
                        throw UnlikelyToHappenException( "nil image for the lintel of " + getKind() );

                int oneCell = getMediator()->getRoom().getSizeOfOneCell ();

                int x( 0 ), y( 0 );

                switch ( Way( getRoomSide() ).toInteger() )
                {
                        case Way::North:
                        case Way::Northeast:
                        case Way::Northwest:
                                x = cellX * oneCell + whatIsLintel.getWidthX() - 2 ;
                                y = ( cellY + 2 ) * oneCell - 1 ;
                                break;

                        case Way::South:
                        case Way::Southeast:
                        case Way::Southwest:
                                x = cellX * oneCell ;
                                y = ( cellY + 2 ) * oneCell - 1 ;
                                break;

                        case Way::East:
                        case Way::Eastnorth:
                        case Way::Eastsouth:
                                x = cellX * oneCell ;
                                y = ( cellY + 1 ) * oneCell - 1 ;
                                break;

                        case Way::West:
                        case Way::Westnorth:
                        case Way::Westsouth:
                                x = cellX * oneCell ;
                                y = ( cellY + 1 ) * oneCell - whatIsLintel.getWidthY() + 1 ;
                                break;

                        default:
                                ;
                }

                lintel = FreeItemPtr( new FreeItem( whatIsLintel, x, y, Room::FloorZ, onWhichSideOfTheFour() ) );
                lintel->addFrameTo( onWhichSideOfTheFour(), new NamedPicture( lintelImage->getWidth(), lintelImage->getHeight() ) );
                allegro::bitBlit( lintelImage->getAllegroPict(), lintel->getCurrentRawImageToChangeIt ().getAllegroPict() );
                lintel->getCurrentRawImageToChangeIt().setName( lintelImage->getName() );
                lintel->freshBothProcessedImages ();
                lintel->setUniqueName( lintel->getKind () + " " + util::makeRandomString( 8 ) );
        }

        return this->lintel ;
}

bool Door::isUnderDoor( int x, int y, int z ) const
{
        if ( z < 0 ) z = 0 ;

        bool under = ( leftJamb->getZ() <= z && z <= lintel->getZ() );

        const int oneCell = getMediator()->getRoom().getSizeOfOneCell ();

        switch ( Way( getRoomSide() ).toInteger() )
        {
                case Way::North:
                case Way::Northeast:
                case Way::Northwest:
                case Way::South:
                case Way::Southeast:
                case Way::Southwest:
                        under = under && ( this->rightLimit <= y && y <= this->leftLimit );
                        if ( under ) {
                                int doorFreeX = getCellX() * oneCell ;
                                under = ( doorFreeX - oneCell <= x && x <= doorFreeX + oneCell );
                        }
                        break;

                case Way::East:
                case Way::Eastnorth:
                case Way::Eastsouth:
                case Way::West:
                case Way::Westnorth:
                case Way::Westsouth:
                        under = under && ( this->leftLimit <= x && x <= this->rightLimit );
                        if ( under ) {
                                int doorFreeY = ( getCellY() + 1 ) * oneCell - 1 ;
                                under = ( doorFreeY - oneCell <= y && y <= doorFreeY + oneCell );
                        }
                        break;

                default:
                        ;
        }

        return under ;
}
