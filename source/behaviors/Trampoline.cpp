
#include "Trampoline.hpp"

#include "FreeItem.hpp"
#include "Displacing.hpp"
#include "Falling.hpp"
#include "Mediator.hpp"
#include "Room.hpp"
#include "SoundManager.hpp"


namespace behaviors
{

Trampoline::Trampoline( const ItemPtr & item, const std::string & behavior )
        : Behavior( item, behavior )
        , folded( false )
        , rebounding( false )
        , unstrainedFrame( 0 )
        , foldedFrame( 1 )
        , speedTimer( new Timer() )
        , fallTimer( new Timer() )
        , reboundTimer( new Timer() )
{
        speedTimer->go();
        fallTimer->go();
        reboundTimer->go();
}

Trampoline::~Trampoline()
{
}

bool Trampoline::update ()
{
        FreeItem & springItem = dynamic_cast< FreeItem & >( * this->item );

        bool present = true ;

        switch ( activity )
        {
                case activities::Activity::Waiting:
                        // is there anything above
                        if ( ! springItem.canAdvanceTo( 0, 0, 1 ) )
                        {
                                this->folded = true ;
                                this->rebounding = false ;
                                springItem.changeFrame( this->foldedFrame );
                        }
                        else
                        {
                                // the spring continues to bounce after unloading
                                if ( this->rebounding && reboundTimer->getValue() < 0.600 )
                                {
                                        springItem.animate() ;

                                        // play the sound of bouncing
                                        if ( reboundTimer->getValue() > 0.100 )
                                                SoundManager::getInstance().play( springItem.getKind(), "function" );
                                }
                                else
                                {
                                        // begin bouncing when item on top moves away
                                        if ( this->folded )
                                        {
                                                this->rebounding = true ;
                                                reboundTimer->reset();
                                        }

                                        // folded no longer
                                        this->folded = false ;

                                        springItem.changeFrame( this->unstrainedFrame );
                                }
                        }

                        // look if it falls down
                        if ( activities::Falling::getInstance().fall( this ) )
                        {
                                fallTimer->reset();
                                activity = activities::Activity::Falling;
                        }
                        break;

                case activities::Activity::PushedNorth:
                case activities::Activity::PushedSouth:
                case activities::Activity::PushedEast:
                case activities::Activity::PushedWest:
                case activities::Activity::PushedNortheast:
                case activities::Activity::PushedNorthwest:
                case activities::Activity::PushedSoutheast:
                case activities::Activity::PushedSouthwest:
                        // is it time to move
                        if ( speedTimer->getValue() > springItem.getSpeed() )
                        {
                                // play the sound of displacing
                                SoundManager::getInstance().play( springItem.getKind(), "push" );

                                activities::Displacing::getInstance().displace( this, &activity, true );

                                if ( activity != activities::Activity::Falling )
                                {
                                        activity = activities::Activity::Waiting;
                                }

                                speedTimer->reset();
                        }
                        break;

                case activities::Activity::Falling:
                        if ( springItem.getZ() == 0 && ! springItem.getMediator()->getRoom()->hasFloor() ) {
                                // disappear when reached bottom of a room without floor
                                present = false ;
                        }
                        // is it time to fall
                        else if ( fallTimer->getValue() > springItem.getWeight() )
                        {
                                if ( ! activities::Falling::getInstance().fall( this ) )
                                {
                                        // play the sound of falling
                                        SoundManager::getInstance().play( springItem.getKind (), "fall" );
                                        activity = activities::Activity::Waiting;
                                }

                                fallTimer->reset();
                        }
                        break;

                case activities::Activity::Vanishing:
                        present = false ;
                        break;

                default:
                        ;
        }

        return ! present ;
}

}
