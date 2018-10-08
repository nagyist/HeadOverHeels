
#include "ItemDataManager.hpp"
#include "GameManager.hpp"
#include "Color.hpp"
#include "Ism.hpp"
#include <tinyxml2.h>

#ifdef DEBUG
#  define DEBUG_ITEM_DATA         1
#endif


namespace isomot
{

ItemDataManager::ItemDataManager( const std::string& name )
        : nameOfXMLFile( name )
{
}

ItemDataManager::~ItemDataManager()
{
        freeItems() ;
}

void ItemDataManager::loadItems ()
{
        freeItems() ;

        // load items from XML file, and transfer this data to the list of items namely this->itemData

        tinyxml2::XMLDocument itemsXml;
        tinyxml2::XMLError result = itemsXml.LoadFile( ( isomot::sharePath() + nameOfXMLFile ).c_str () );
        if ( result != tinyxml2::XML_SUCCESS )
        {
                return;
        }

        tinyxml2::XMLElement* root = itemsXml.FirstChildElement( "items" );

        for ( tinyxml2::XMLElement* item = root->FirstChildElement( "item" ) ;
                        item != nilPointer ;
                        item = item->NextSiblingElement( "item" ) )
        {
                ItemData* newItem = new ItemData ();

                // label of item
                newItem->label = item->Attribute( "label" ) ;

                bool isDoor = false;
                tinyxml2::XMLElement* door = item->FirstChildElement( "door" ) ;
                if ( door != nilPointer ) isDoor = true;

                // number of frames for orientations of item
                tinyxml2::XMLElement* directionFrames = item->FirstChildElement( "directionFrames" ) ;
                newItem->orientationFrames = std::atoi( directionFrames->FirstChild()->ToText()->Value() ) ;

                // offensive or harmless
                tinyxml2::XMLElement* mortal = item->FirstChildElement( "mortal" ) ;
                newItem->mortal = ( std::string( mortal->FirstChild()->ToText()->Value() ) == "true" ) ? true : false ;

                // how long, in milliseconds, it falls
                tinyxml2::XMLElement* weight = item->FirstChildElement( "weight" ) ;
                if ( weight != nilPointer )
                        newItem->weight = static_cast< double >( std::atoi( weight->FirstChild()->ToText()->Value() ) ) / 1000.0 ;
                else
                        newItem->weight = 0.0 ;

                // delay, in milliseconds, between frames in animation sequence
                tinyxml2::XMLElement* framesDelay = item->FirstChildElement( "framesDelay" ) ;
                if ( framesDelay != nilPointer )
                        newItem->delayBetweenFrames = static_cast< double >( std::atoi( framesDelay->FirstChild()->ToText()->Value() ) ) / 1000.0 ;
                else
                        newItem->delayBetweenFrames = 0.0 ;

                // how many milliseconds this item moves one single isometric unit
                tinyxml2::XMLElement* speed = item->FirstChildElement( "speed" ) ;
                if ( speed != nilPointer )
                        newItem->speed = static_cast< double >( std::atoi( speed->FirstChild()->ToText()->Value() ) ) / 1000.0 ;
                else
                        newItem->speed = 0.0 ;

                {
                        tinyxml2::XMLElement* picture = item->FirstChildElement( "picture" ) ;

                        // name of file with item's graphics
                        newItem->setNameOfFile( picture->Attribute( "file" ) );

                        // width and height, in pixels, of single frame
                        tinyxml2::XMLElement* frameWidth = picture->FirstChildElement( "frameWidth" ) ;
                        newItem->widthOfFrame = std::atoi( frameWidth->FirstChild()->ToText()->Value() ) ;
                        tinyxml2::XMLElement* frameHeight = picture->FirstChildElement( "frameHeight" ) ;
                        newItem->heightOfFrame = std::atoi( frameHeight->FirstChild()->ToText()->Value() ) ;
                }

                // create frames of item’s animation if item isn’t door
                if ( ! isDoor )
                {
                # if  defined( DEBUG_ITEM_DATA )  &&  DEBUG_ITEM_DATA
                        std::cout << "got item \"" << newItem->getLabel() << "\"" ;
                # endif

                        createFrames( newItem, isomot::GameManager::getInstance()->getChosenGraphicSet() );
                }

                {
                        tinyxml2::XMLElement* shadow = item->FirstChildElement( "shadow" ) ;
                        if ( shadow != nilPointer ) // item may have no shadow
                        {
                                newItem->setNameOfShadowFile( shadow->Attribute( "file" ) );

                                tinyxml2::XMLElement* shadowWidth = shadow->FirstChildElement( "shadowWidth" ) ;
                                newItem->widthOfShadow = std::atoi( shadowWidth->FirstChild()->ToText()->Value() ) ;
                                tinyxml2::XMLElement* shadowHeight = shadow->FirstChildElement( "shadowHeight" ) ;
                                newItem->heightOfShadow = std::atoi( shadowHeight->FirstChild()->ToText()->Value() ) ;

                                // creates frames for item’s shadow
                                createShadowFrames( newItem, isomot::GameManager::getInstance()->getChosenGraphicSet() );
                        }
                }

                tinyxml2::XMLElement* extraFrames = item->FirstChildElement( "extraFrames" ) ;
                // only few items have extra frames
                if ( extraFrames != nilPointer )
                {
                        newItem->extraFrames = std::atoi( extraFrames->FirstChild()->ToText()->Value() ) ;
                }

                // sequence of animation
                for ( tinyxml2::XMLElement* frame = item->FirstChildElement( "frame" ) ;
                                frame != nilPointer ;
                                frame = frame->NextSiblingElement( "frame" ) )
                {
                        newItem->frames.push_back( std::atoi( frame->FirstChild()->ToText()->Value() ) );
                }

                // door has three parameters for its dimensions
                if ( isDoor )
                {
                        std::string doorAt = door->FirstChild()->ToText()->Value() ;

                # if  defined( DEBUG_ITEM_DATA )  &&  DEBUG_ITEM_DATA
                        std::cout << "got door \"" << newItem->getLabel() << "\" at \"" << doorAt << "\"" ;
                # endif

                        // door is actually three items: lintel, left jamb and right jamb
                        ItemData* lintel = ItemData::clone( newItem ) ;
                        lintel->label += "~lintel";
                        ItemData* leftJamb = ItemData::clone( newItem ) ;
                        leftJamb->label += "~leftjamb";
                        ItemData* rightJamb = ItemData::clone( newItem ) ;
                        rightJamb->label += "~rightjamb";

                        unsigned int leftJambWidthX = 0;
                        unsigned int leftJambWidthY = 0;
                        unsigned int leftJambHeight = 0;

                        unsigned int rightJambWidthX = 0;
                        unsigned int rightJambWidthY = 0;
                        unsigned int rightJambHeight = 0;

                        unsigned int lintelWidthX = 0;
                        unsigned int lintelWidthY = 0;
                        unsigned int lintelHeight = 0;

                        // width at axis X of three parts ( left jamb, right jamb and lintel ) of door
                        for ( tinyxml2::XMLElement* widthX = item->FirstChildElement( "widthX" ) ;
                                        widthX != nilPointer ;
                                        widthX = widthX->NextSiblingElement( "widthX" ) )
                        {
                                int wx = std::atoi( widthX->FirstChild()->ToText()->Value() ) ;

                                if ( leftJambWidthX == 0 )
                                        leftJamb->widthX = leftJambWidthX = wx ;
                                else if ( rightJambWidthX == 0 )
                                        rightJamb->widthX = rightJambWidthX = wx ;
                                else if ( lintelWidthX == 0 )
                                        lintel->widthX = lintelWidthX = wx ;
                        }

                        // width at axis Y of three parts ( left jamb, right jamb and lintel ) of door
                        for ( tinyxml2::XMLElement* widthY = item->FirstChildElement( "widthY" ) ;
                                        widthY != nilPointer ;
                                        widthY = widthY->NextSiblingElement( "widthY" ) )
                        {
                                int wy = std::atoi( widthY->FirstChild()->ToText()->Value() ) ;

                                if ( leftJambWidthY == 0 )
                                        leftJamb->widthY = leftJambWidthY = wy ;
                                else if ( rightJambWidthY == 0 )
                                        rightJamb->widthY = rightJambWidthY = wy ;
                                else if ( lintelWidthY == 0 )
                                        lintel->widthY = lintelWidthY = wy ;
                        }

                        // height of three parts ( left jamb, right jamb and lintel ) of door
                        for ( tinyxml2::XMLElement* height = item->FirstChildElement( "height" ) ;
                                        height != nilPointer ;
                                        height = height->NextSiblingElement( "height" ) )
                        {
                                int wz = std::atoi( height->FirstChild()->ToText()->Value() ) ;

                                if ( leftJambHeight == 0 )
                                        leftJamb->height = leftJambHeight = wz ;
                                else if ( rightJambHeight == 0 )
                                        rightJamb->height = rightJambHeight = wz ;
                                else if ( lintelHeight == 0 )
                                        lintel->height = lintelHeight = wz ;
                        }

                        // load graphics of door
                        smartptr< allegro::Pict > pictureOfDoor( allegro::loadPNG( isomot::pathToFile(
                                isomot::sharePath() + isomot::GameManager::getInstance()->getChosenGraphicSet() + pathSeparator + newItem->getNameOfFile( )
                        ) ) );
                        if ( ! pictureOfDoor->isNotNil() )
                        {
                                std::cerr <<
                                        "picture of door \"" << newItem->getNameOfFile( ) <<
                                        "\" for \"" << isomot::GameManager::getInstance()->getChosenGraphicSet() <<
                                        "\" is absent" << std::endl ;
                        }

                        // cut out left jamb
                        Picture* leftJambImage = cutOutLeftJamb( *pictureOfDoor.get(), leftJambWidthX, leftJambWidthY, leftJambHeight, lintelWidthY, lintelHeight, doorAt );
                        leftJamb->motion.push_back( leftJambImage );
                        this->itemData.push_back( leftJamb );

                        // cut out right jamb
                        Picture* rightJambImage = cutOutRightJamb( *pictureOfDoor.get(), rightJambWidthX, rightJambWidthY, rightJambHeight, lintelWidthX, lintelHeight, doorAt );
                        rightJamb->motion.push_back( rightJambImage );
                        this->itemData.push_back( rightJamb );

                        // cut out lintel
                        Picture* lintelImage = cutOutLintel( *pictureOfDoor.get(), lintelWidthX, lintelWidthY, lintelHeight, leftJambWidthX, leftJambWidthY, rightJambWidthX, rightJambWidthY, doorAt );
                        lintel->motion.push_back( lintelImage );
                        this->itemData.push_back( lintel );

                # if  defined( DEBUG_ITEM_DATA )  &&  DEBUG_ITEM_DATA
                        std::cout << ", three parts are \"" <<
                                        leftJamb->getLabel() << "\" \"" << rightJamb->getLabel() << "\" \"" << lintel->getLabel() << "\""
                                        << std::endl ;
                # endif
                }
                else
                {
                        newItem->widthX = std::atoi( item->FirstChildElement( "widthX" )->FirstChild()->ToText()->Value() ) ;
                        newItem->widthY = std::atoi( item->FirstChildElement( "widthY" )->FirstChild()->ToText()->Value() ) ;
                        newItem->height = std::atoi( item->FirstChildElement( "height" )->FirstChild()->ToText()->Value() ) ;

                        // add data to the list
                        this->itemData.push_back( newItem );
                }
        }
}

void ItemDataManager::freeItems ()
{
        for ( std::list< ItemData * >::iterator i = itemData.begin (); i != itemData.end (); ++ i )
        {
                delete ( *i );
        }
}

ItemData* ItemDataManager::findDataByLabel( const std::string& label )
{
        for ( std::list< ItemData * >::iterator i = this->itemData.begin (); i != this->itemData.end (); ++i )
        {
                if ( ( *i )->getLabel() == label )
                {
                        return *i ;
                }
        }

        std::cerr << "item with label \"" << label << "\" is absent" << std::endl;
        return nilPointer ;
}

ItemData* ItemDataManager::createFrames( ItemData * itemData, const char* gfxPrefix )
{
        try
        {
                if ( itemData->getNameOfFile( ).empty() || itemData->getWidthOfFrame() == 0 || itemData->getHeightOfFrame() == 0 )
                {
                        throw "either name of file is empty or zero width / height at ItemDataManager::createFrames";
                }

                // load graphics for item
                smartptr< allegro::Pict > picture( allegro::loadPNG (
                        isomot::pathToFile( isomot::sharePath() + gfxPrefix + pathSeparator + itemData->getNameOfFile() )
                ) );
                if ( ! picture->isNotNil() )
                {
                        std::cerr << "picture \"" << itemData->getNameOfFile( ) << "\" of set \"" << gfxPrefix << "\" is absent" << std::endl ;
                        throw "picture " + itemData->getNameOfFile( ) + " is absent" ;
                }

                // decompose image into frames and store them in vector
                for ( unsigned int y = 0; y < picture->getH() / itemData->getHeightOfFrame(); y++ )
                {
                        for ( unsigned int x = 0; x < picture->getW() / itemData->getWidthOfFrame(); x++ )
                        {
                                Picture* frame = new Picture( itemData->getWidthOfFrame(), itemData->getHeightOfFrame() );
                                allegro::bitBlit( *picture.get(), frame->getAllegroPict(), x * itemData->getWidthOfFrame(), y * itemData->getHeightOfFrame(), 0, 0, frame->getWidth(), frame->getHeight() );
                                itemData->motion.push_back( frame );
                        }
                }

                # if  defined( DEBUG_ITEM_DATA )  &&  DEBUG_ITEM_DATA
                        size_t howManyFrames = itemData->motion.size();
                        std::cout << " with " << howManyFrames << ( howManyFrames == 1 ? " frame" : " frames" ) << std::endl ;
                # endif
        }
        catch ( const std::exception& e )
        {
                std::cerr << e.what () << std::endl ;
                return nilPointer;
        }

        return itemData;
}

ItemData* ItemDataManager::createShadowFrames( ItemData * itemData, const char* gfxPrefix )
{
        try
        {
                if ( itemData->getNameOfShadowFile( ).empty() || itemData->getWidthOfShadow() == 0 || itemData->getHeightOfShadow() == 0 )
                {
                        throw "either name of file is empty or zero width / height at ItemDataManager::createShadowFrames";
                }

                // load graphics for shadow
                smartptr< allegro::Pict > picture( allegro::loadPNG (
                        isomot::pathToFile( isomot::sharePath() + gfxPrefix + pathSeparator + itemData->getNameOfShadowFile( ) )
                ) );
                if ( ! picture->isNotNil() )
                {
                        std::cerr << "file of shadows \"" << itemData->getNameOfShadowFile( ) << "\" is absent at set \"" << gfxPrefix << "\"" << std::endl ;
                        throw "file of shadows " + itemData->getNameOfShadowFile( ) + " is absent" ;
                }

                // decompose image into frames
                for ( unsigned int y = 0; y < picture->getH() / itemData->getHeightOfShadow(); y++ )
                {
                        for ( unsigned int x = 0; x < picture->getW() / itemData->getWidthOfShadow(); x++ )
                        {
                                Picture* frame = new Picture( itemData->getWidthOfShadow(), itemData->getHeightOfShadow() );
                                allegro::bitBlit( *picture.get(), frame->getAllegroPict(), x * itemData->getWidthOfShadow(), y * itemData->getHeightOfShadow(), 0, 0, frame->getWidth(), frame->getHeight() );
                                itemData->shadows.push_back( frame );
                        }
                }
        }
        catch ( const std::exception& e )
        {
                std::cerr << e.what () << std::endl ;
                return nilPointer;
        }

        return itemData;
}

Picture* ItemDataManager::cutOutLintel( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                       unsigned int leftJambWidthX, unsigned int leftJambWidthY,
                                       unsigned int rightJambWidthX, unsigned int rightJambWidthY,
                                       const std::string& at )
{
        bool ns = ( at == "north" || at == "south" );

        // top of door
        unsigned int topWidth = ( widthX << 1 ) + ( widthY << 1 );
        unsigned int topHeight = height + widthY + widthX;
        Picture* top = new Picture( topWidth, topHeight, Color::colorOfTransparency() );

        if ( ns )
        {
                allegro::bitBlit( door, top->getAllegroPict(), 0, 0, 0, 0, topWidth, height + widthX );

                unsigned int delta = topWidth;
                int noPixel = topWidth - ( ( rightJambWidthX + rightJambWidthY ) << 1 ) + 1;
                int yStart = noPixel;
                int yEnd = noPixel - 1;

                allegro::acquirePict( top->getAllegroPict() );

                for ( unsigned int yPic = height + widthX; yPic < topHeight; yPic++ )
                {
                        for ( unsigned int xPic = delta; xPic > 0; xPic-- )
                        {
                                if ( yPic != height + widthX && ( static_cast< int >( xPic ) - 1 ) == noPixel )
                                {
                                        if ( noPixel > yEnd )
                                        {
                                                noPixel--;
                                        }
                                        else
                                        {
                                                yStart += 2;
                                                noPixel = yStart;
                                        }
                                }
                                else if ( yPic < height + ( widthX << 1 ) || ( static_cast< int >( xPic ) - 1 ) < yEnd )
                                {
                                        top->getAllegroPict().setPixelAt( xPic - 1, yPic, door.getPixelAt( xPic - 1, yPic ) );
                                }
                        }

                        delta -= 2;
                }

                allegro::releasePict( top->getAllegroPict() );
        }
        else
        {
                allegro::bitBlit( door, top->getAllegroPict(), 0, 0, 0, 0, topWidth, height + widthY );

                unsigned int delta = 0;
                int noPixel = ( ( leftJambWidthX + leftJambWidthY ) << 1 ) - 2;
                int yStart = noPixel;
                int yEnd = noPixel + 1;

                allegro::acquirePict( top->getAllegroPict() );

                for ( unsigned int yPic = height + widthY; yPic < topHeight; yPic++ )
                {
                        for ( unsigned int xPic = delta; xPic < topWidth; xPic++ )
                        {
                                if ( yPic != height + widthY && static_cast< int >( xPic ) == noPixel )
                                {
                                        if ( noPixel < yEnd )
                                        {
                                                noPixel++;
                                        }
                                        else
                                        {
                                                yStart -= 2;
                                                noPixel = yStart;
                                        }
                                }
                                else if ( yPic < height + ( widthY << 1 ) || static_cast< int >( xPic ) > yEnd )
                                {
                                        top->getAllegroPict().setPixelAt( xPic, yPic, door.getPixelAt( xPic, yPic ) );
                                }
                        }

                        delta += 2;
                }

                allegro::releasePict( top->getAllegroPict() );
        }

        return top;
}

Picture* ItemDataManager::cutOutLeftJamb( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                         /* unsigned int lintelWidthX, */ unsigned int lintelWidthY, unsigned int lintelHeight,
                                         const std::string& at )
{
        bool ns = ( at == "north" || at == "south" );
        unsigned int fixWidth = ( ns ? 7 : 0 );
        int fixY = ( ns ? -1 : 0 );

        Picture* left = new Picture( ( widthX << 1 ) + fixWidth + ( widthY << 1 ) , height + widthY + widthX, Color::colorOfTransparency() ) ;

        allegro::bitBlit( door, left->getAllegroPict(), fixY, lintelHeight + lintelWidthY - widthY + fixY, 0, 0, left->getWidth(), left->getHeight() );

        return left;
}

Picture* ItemDataManager::cutOutRightJamb( const allegro::Pict& door, unsigned int widthX, unsigned int widthY, unsigned int height,
                                          unsigned int lintelWidthX, /* unsigned int lintelWidthY, */ unsigned int lintelHeight,
                                          const std::string& at )
{
        bool ns = ( at == "north" || at == "south" );
        unsigned int fixWidth = ( ns ? 0 : 7 );
        int fixY = ( ns ? 0 : -2 );

        Picture* right = new Picture( ( widthX << 1 ) + fixWidth + ( widthY << 1 ) , height + widthY + widthX, Color::colorOfTransparency() ) ;

        allegro::bitBlit( door, right->getAllegroPict(), door.getW() - right->getWidth(), lintelHeight + lintelWidthX - widthY + fixY, 0, 0, right->getWidth(), right->getHeight() );

        return right;
}

}
