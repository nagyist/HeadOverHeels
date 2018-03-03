
#include "KindOfActivity.hpp"
#include "Behavior.hpp"
#include "Item.hpp"
#include "FreeItem.hpp"
#include "PlayerItem.hpp"
#include "Room.hpp"
#include "Mediator.hpp"
#include "GameManager.hpp"


namespace isomot
{

KindOfActivity::KindOfActivity( )
{

}

KindOfActivity::~KindOfActivity( )
{

}

void KindOfActivity::propagateActivityToAdjacentItems( Item * sender, const ActivityOfItem& activity )
{
        Mediator* mediator = sender->getMediator();

        // as long as there are items collided with sender
        while ( ! mediator->isStackOfCollisionsEmpty() )
        {
                // pop item out of stack of collisions
                int id = mediator->popCollision();

                // is it free item or grid item
                if ( ( id >= FirstFreeId && ( id & 1 ) ) || ( id >= FirstGridId && ! ( id & 1 ) ) )
                {
                        Item * itemMeetsSender = mediator->findItemById( id );

                        if ( itemMeetsSender != nilPointer )
                        {
                                // is it item with behavior
                                if ( itemMeetsSender->getBehavior() != nilPointer )
                                {
                                        // if it’s player item and sender is mortal, then player loses its life
                                        if ( dynamic_cast< PlayerItem * >( itemMeetsSender ) && sender->isMortal() &&
                                                        ! dynamic_cast< PlayerItem * >( itemMeetsSender )->hasShield() )
                                        {
                                                if ( itemMeetsSender->getBehavior()->getActivityOfItem() != MeetMortalItem &&
                                                                itemMeetsSender->getBehavior()->getActivityOfItem() != Vanish )
                                                {
                                                        if ( ! GameManager::getInstance()->isImmuneToCollisionsWithMortalItems () )
                                                        {
                                                                std::cout << "mortal item \"" << sender->getLabel() << "\" just met player" << std::endl ;

                                                                // is it direct contact
                                                                if ( mediator->depthOfStackOfCollisions() <= 1 )
                                                                {
                                                                        itemMeetsSender->getBehavior()->changeActivityOfItem( MeetMortalItem );
                                                                }
                                                        }
                                                        /* else std::cout << "right to inviolability granted when item \"" << sender->getLabel() << "\" met player" << std::endl ; */
                                                }
                                        }
                                        // if sender is player and colliding one is mortal, then player loses its life
                                        else if ( dynamic_cast< PlayerItem * >( sender ) && itemMeetsSender->isMortal() &&
                                                        ! dynamic_cast< PlayerItem * >( sender )->hasShield() )
                                        {
                                                if ( sender->getBehavior()->getActivityOfItem() != MeetMortalItem &&
                                                                itemMeetsSender->getBehavior()->getActivityOfItem() != Vanish )
                                                {
                                                        if ( ! GameManager::getInstance()->isImmuneToCollisionsWithMortalItems () )
                                                        {
                                                                std::cout << "player just met mortal item \"" << itemMeetsSender->getLabel() << "\"" << std::endl ;

                                                                sender->getBehavior()->changeActivityOfItem( MeetMortalItem );
                                                                itemMeetsSender->getBehavior()->changeActivityOfItem( activity, sender );
                                                        }
                                                        /* else std::cout << "right to inviolability granted when player met item \"" << itemMeetsSender->getLabel() << "\"" << std::endl ; */
                                                }
                                        }
                                        // if not, propagate activity to that item
                                        else
                                        {
                                                if ( itemMeetsSender->getBehavior()->getActivityOfItem() != Vanish )
                                                {
                                                        itemMeetsSender->getBehavior()->changeActivityOfItem( activity, sender );
                                                }
                                        }
                                }
                                // otherwise it is item without behavior, which may be mortal too
                                else if ( dynamic_cast< PlayerItem * >( sender ) && itemMeetsSender->isMortal() &&
                                                ! dynamic_cast< PlayerItem * >( sender )->hasShield() )
                                {
                                        if ( sender->getBehavior()->getActivityOfItem() != MeetMortalItem &&
                                                        sender->getBehavior()->getActivityOfItem() != Vanish )
                                        {
                                                if ( ! GameManager::getInstance()->isImmuneToCollisionsWithMortalItems () )
                                                {
                                                        sender->getBehavior()->changeActivityOfItem( MeetMortalItem );
                                                }
                                        }
                                }
                        }
                }
                // is it player which leaves room via some door
                else if ( dynamic_cast< PlayerItem * >( sender ) &&
                                ( ( id == NorthBorder  &&  mediator->getRoom()->hasDoorAt( North ) ) ||
                                  ( id == SouthBorder  &&  mediator->getRoom()->hasDoorAt( South ) ) ||
                                  ( id == EastBorder  &&  mediator->getRoom()->hasDoorAt( East ) ) ||
                                  ( id == WestBorder  &&  mediator->getRoom()->hasDoorAt( West ) ) ||
                                  ( id == NortheastBorder  &&  mediator->getRoom()->hasDoorAt( Northeast ) ) ||
                                  ( id == NorthwestBorder  &&  mediator->getRoom()->hasDoorAt( Northwest ) ) ||
                                  ( id == SoutheastBorder  &&  mediator->getRoom()->hasDoorAt( Southeast ) ) ||
                                  ( id == SouthwestBorder  &&  mediator->getRoom()->hasDoorAt( Southwest ) ) ||
                                  ( id == EastnorthBorder  &&  mediator->getRoom()->hasDoorAt( Eastnorth ) ) ||
                                  ( id == EastsouthBorder  &&  mediator->getRoom()->hasDoorAt( Eastsouth ) ) ||
                                  ( id == WestnorthBorder  &&  mediator->getRoom()->hasDoorAt( Westnorth ) ) ||
                                  ( id == WestsouthBorder  &&  mediator->getRoom()->hasDoorAt( Westsouth ) ) ) )
                {
                        PlayerItem * player = dynamic_cast< PlayerItem * >( sender );

                        switch ( id )
                        {
                                case NorthBorder:
                                        player->setWayOfExit( North );
                                        break;

                                case SouthBorder:
                                        player->setWayOfExit( South );
                                        break;

                                case EastBorder:
                                        player->setWayOfExit( East );
                                        break;

                                case WestBorder:
                                        player->setWayOfExit( West );
                                        break;

                                case NortheastBorder:
                                        player->setWayOfExit( Northeast );
                                        break;

                                case NorthwestBorder:
                                        player->setWayOfExit( Northwest );
                                        break;

                                case SoutheastBorder:
                                        player->setWayOfExit( Southeast );
                                        break;

                                case SouthwestBorder:
                                        player->setWayOfExit( Southwest );
                                        break;

                                case EastnorthBorder:
                                        player->setWayOfExit( Eastnorth );
                                        break;

                                case EastsouthBorder:
                                        player->setWayOfExit( Eastsouth );
                                        break;

                                case WestnorthBorder:
                                        player->setWayOfExit( Westnorth );
                                        break;

                                case WestsouthBorder:
                                        player->setWayOfExit( Westsouth );
                                        break;

                                default:
                                        ;
                        }
                }
        }
}

void KindOfActivity::propagateActivityToItemsAbove( Item * sender, const ActivityOfItem& activity )
{
        Mediator* mediator = sender->getMediator();

        // is there anything above
        if ( ! sender->checkPosition( 0, 0, 1, Add ) )
        {
                // copy stack of collisions
                std::stack< int > itemsAbove;
                while ( ! mediator->isStackOfCollisionsEmpty() )
                {
                        itemsAbove.push( mediator->popCollision() );
                }

                while ( ! itemsAbove.empty() )
                {
                        // get first item
                        int id = itemsAbove.top();
                        itemsAbove.pop();

                        // is it free item
                        if ( id >= FirstFreeId && ( id & 1 ) )
                        {
                                FreeItem* freeItemAbove = dynamic_cast< FreeItem * >( mediator->findItemById( id ) );

                                // is it item with behavior
                                if ( freeItemAbove != nilPointer && freeItemAbove->getBehavior() != nilPointer )
                                {
                                        // look for collisions of that free item with items below it
                                        if ( ! freeItemAbove->checkPosition( 0, 0, -1, Add ) )
                                        {
                                                // propagate activity when there’s no more than one item below or when sender is anchor of that item
                                                if ( mediator->depthOfStackOfCollisions() <= 1 || freeItemAbove->getAnchor() == sender )
                                                {
                                                        if ( freeItemAbove->getBehavior()->getActivityOfItem() != Vanish )
                                                        {
                                                                // if it’s player item above sender and sender is mortal, then player loses its life
                                                                if ( dynamic_cast< PlayerItem * >( freeItemAbove ) && sender->isMortal() &&
                                                                        ! dynamic_cast< PlayerItem * >( freeItemAbove )->hasShield() )
                                                                {
                                                                        if ( freeItemAbove->getBehavior()->getActivityOfItem() != MeetMortalItem )
                                                                        {
                                                                                if ( ! GameManager::getInstance()->isImmuneToCollisionsWithMortalItems () )
                                                                                {
                                                                                        std::cout << "player is above mortal item \"" << sender->getLabel() << "\"" << std::endl ;
                                                                                        freeItemAbove->getBehavior()->changeActivityOfItem( MeetMortalItem );
                                                                                }
                                                                                /* else std::cout << "right to inviolability granted when player is above item \"" << sender->getLabel() << "\"" << std::endl ; */
                                                                        }
                                                                }
                                                                // if not, propagate activity to that item above
                                                                else
                                                                {
                                                                        ActivityOfItem currentActivity = freeItemAbove->getBehavior()->getActivityOfItem();
                                                                        if ( currentActivity != DisplaceNorth && currentActivity != DisplaceSouth &&
                                                                                currentActivity != DisplaceEast && currentActivity != DisplaceWest )
                                                                        {
                                                                                freeItemAbove->getBehavior()->changeActivityOfItem( activity, freeItemAbove );
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}

}
