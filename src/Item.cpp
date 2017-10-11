
#include "Item.hpp"
#include "ItemData.hpp"
#include "Mediator.hpp"
#include "Behavior.hpp"

#include <iostream>


namespace isomot
{

Item::Item( ItemData* data, int z, const Direction& direction )
      : Mediated(),
        id( 0 ),
        label( data->getLabel() ),
        dataOfItem( data ),
        x( 0 ),
        y( 0 ),
        z( z ),
        direction( direction ),
        myShady( WantShadow ),
        rawImage( 0 ),
        shadow( 0 ),
        processedImage( 0 ),
        behavior( 0 ),
        frameIndex( 0 ),
        backwardMotion( false )
{
        this->offset.first = this->offset.second = 0;

        // item with more than one frame per direction has animation
        if ( ( data->howManyMotions() - data->howManyExtraFrames() ) / data->howManyDirectionFrames() > 1 )
        {
                motionTimer.start();
        }
}

Item::Item( const Item& item )
: Mediated( item ),
        id( item.id ),
        label( item.label ),
        dataOfItem( item.dataOfItem ),
        x( item.x ),
        y( item.y ),
        z( item.z ),
        direction( item.direction ),
        myShady( item.myShady ),
        rawImage( item.rawImage ),
        shadow( item.shadow ),
        processedImage( 0 ),
        offset( item.offset ),
        motionTimer( item.motionTimer ),
        behavior( 0 ),
        frameIndex( item.frameIndex ),
        backwardMotion( item.backwardMotion )
{
        if ( item.processedImage != 0 )
        {
                this->processedImage = create_bitmap_ex( 32, item.processedImage->w, item.processedImage->h );
                blit( item.processedImage, this->processedImage, 0, 0, 0, 0, this->processedImage->w, this->processedImage->h );
        }
}

Item::~Item( )
{
        if ( this->behavior != 0 )
                delete this->behavior;

        if ( this->processedImage != 0 )
                destroy_bitmap( this->processedImage );
}

bool Item::update()
{
        bool isGone = false;

        if ( behavior != 0 )
                isGone = behavior->update();

        return isGone;
}

bool Item::animate()
{
        bool cycle = false;

        // item with more than one frame per direction has animation
        if ( ( dataOfItem->howManyMotions() - dataOfItem->howManyExtraFrames() ) / dataOfItem->howManyDirectionFrames() > 1 )
        {
                // is it time to change frames
                if ( motionTimer.getValue() > dataOfItem->getDelayBetweenFrames() )
                {
                        // forward motion
                        if ( ! backwardMotion )
                        {
                                if ( ++frameIndex >= dataOfItem->howManyFrames() )
                                {
                                        frameIndex = 0;
                                        cycle = true;
                                }
                        }
                        // backward motion
                        else
                        {
                                if ( frameIndex-- <= 0 )
                                {
                                        frameIndex = dataOfItem->howManyFrames() - 1;
                                        cycle = true;
                                }
                        }

                        // which frame to show yet
                        int framesNumber = ( dataOfItem->howManyMotions() - dataOfItem->howManyExtraFrames() ) / dataOfItem->howManyDirectionFrames();
                        int currentFrame = dataOfItem->getFrameAt( frameIndex ) + ( dataOfItem->howManyDirectionFrames() > 1 ? framesNumber * direction : 0 );

                        // change frame of animation
                        if ( this->rawImage != 0 && this->rawImage != dataOfItem->getMotionAt( currentFrame ) )
                        {
                                changeImage( dataOfItem->getMotionAt( currentFrame ) );

                                if ( this->shadow != 0 )
                                {
                                        changeShadow( dataOfItem->getShadowAt( currentFrame ) );
                                }
                        }

                        motionTimer.reset();
                }
        }

        return cycle;
}

void Item::changeItemData( ItemData* itemData, const std::string& initiatedBy )
{
        std::cout << "metamorphosis of data for item with label \"" << getLabel()
                        << "\" to data of \"" << itemData->getLabel()
                        << "\" initiated by \"" << initiatedBy << "\"" << std::endl ;

        this->dataOfItem = itemData;
        this->frameIndex = 0;
        this->backwardMotion = false;
}

void Item::changeDirection( const Direction& direction )
{
        // direction is changed only when item has different frames for different directions
        if ( dataOfItem->howManyDirectionFrames() > 1 )
        {
                // get frame for new direction
                unsigned int currentFrame = ( ( dataOfItem->howManyMotions() - dataOfItem->howManyExtraFrames() ) / dataOfItem->howManyDirectionFrames() ) * direction;

                if ( this->rawImage != 0 && currentFrame < dataOfItem->howManyMotions() && this->rawImage != dataOfItem->getMotionAt( currentFrame ) )
                {
                        this->direction = direction;

                        changeImage( dataOfItem->getMotionAt( currentFrame ) );

                        if ( this->shadow != 0 )
                                changeShadow( dataOfItem->getShadowAt( currentFrame ) );
                }
        }
}

void Item::changeFrame( const unsigned int frameIndex )
{
        // if index of frame is within bounds of vector with sequence of animation
        if ( dataOfItem->howManyMotions() > frameIndex )
        {
                this->frameIndex = frameIndex;

                // change frame
                if ( this->rawImage != 0 && this->rawImage != dataOfItem->getMotionAt( frameIndex ) )
                {
                        changeImage( dataOfItem->getMotionAt( frameIndex ) );

                        // update shadow too
                        if ( this->shadow != 0 )
                                changeShadow( dataOfItem->getShadowAt( frameIndex ) );
                }
        }
}

bool Item::checkPosition( int x, int y, int z, const ChangeOrAdd& what )
{
        // coordinates before change
        int px = this->x;
        int py = this->y;
        int pz = this->z;

        mediator->clearStackOfCollisions( );

        bool collisionFound = false;

        // new coordinates
        this->x = x + this->x * what;
        this->y = y + this->y * what;
        this->z = z + this->z * what;

        // look for collision with wall
        if ( this->x < mediator->getBound( North ) )
        {
                mediator->pushCollision( NorthWall );
        }
        else if ( this->x + this->dataOfItem->getWidthX() > mediator->getBound( South ) )
        {
                mediator->pushCollision( SouthWall );
        }
        if ( this->y >= mediator->getBound( West ) )
        {
                mediator->pushCollision( WestWall );
        }
        else if ( this->y - this->dataOfItem->getWidthY() + 1 < mediator->getBound( East ) )
        {
                mediator->pushCollision( EastWall );
        }

        // look for collision with floor
        if ( this->z < 0 )
        {
                mediator->pushCollision( Floor );
        }

        collisionFound = ! mediator->isStackOfCollisionsEmpty ();
        if ( ! collisionFound )
        {
                // look for collisions with other items in room
                collisionFound = mediator->findCollisionWithItem( this );
        }

        // restore original coordinates
        this->x = px;
        this->y = py;
        this->z = pz;

        return ! collisionFound;
}

void Item::assignBehavior( const std::string& behavior, void* extraData )
{
        this->behavior = Behavior::createBehaviorByName( this, behavior, extraData );
}

void Item::setForthMotion ()
{
        this->backwardMotion = false;
        this->frameIndex = 0;
}

void Item::setReverseMotion ()
{
        this->backwardMotion = true;
        this->frameIndex = dataOfItem->howManyFrames() - 1;
}

unsigned int Item::getWidthX() const
{
        return dataOfItem->getWidthX() ;
}

unsigned int Item::getWidthY() const
{
        return dataOfItem->getWidthY() ;
}

unsigned int Item::getHeight() const
{
        return dataOfItem->getHeight() ;
}

void Item::setHeight( int height )
{
        dataOfItem->setHeight( height );
}

bool Item::isMortal() const
{
        return dataOfItem->isMortal() ;
}

unsigned char Item::countDirectionFrames() const
{
        return dataOfItem->howManyDirectionFrames() ;
}

double Item::getSpeed() const
{
        return dataOfItem->getSpeed() ;
}

double Item::getWeight() const
{
        return dataOfItem->getWeight() ;
}

double Item::getDelayBetweenFrames() const
{
        return dataOfItem->getDelayBetweenFrames() ;
}

unsigned int Item::countFrames() const
{
        return dataOfItem->howManyMotions();
}

void Item::setAnchor( Item* item )
{
        this->anchor = item;
}

}
