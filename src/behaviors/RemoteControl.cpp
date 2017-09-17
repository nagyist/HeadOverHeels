
#include "RemoteControl.hpp"
#include "Item.hpp"
#include "FreeItem.hpp"
#include "DisplaceKindOfActivity.hpp"
#include "FallKindOfActivity.hpp"
#include "Mediator.hpp"
#include "Room.hpp"
#include "SoundManager.hpp"


namespace isomot
{

RemoteControl::RemoteControl( Item * item, const std::string & behavior ) :
        Behavior( item, behavior )
{
        activity = Wait;
        controlledItem = 0;

        // move only controlled one but not controller
        if ( theBehavior == "behavior of remotely controlled one" )
        {
                speedTimer = new HPC();
                fallTimer = new HPC();
                speedTimer->start();
                fallTimer->start();
        }
}

RemoteControl::~RemoteControl()
{
        if ( theBehavior == "behavior of remotely controlled one" )
        {
                delete speedTimer;
                delete fallTimer;
        }
}

bool RemoteControl::update ()
{
        FreeItem* freeItem = dynamic_cast< FreeItem * >( this->item );
        bool destroy = false;

        // get controlled item
        if ( theBehavior == "behavior of remote control" && controlledItem == 0 )
        {
                controlledItem = static_cast< FreeItem * >( freeItem->getMediator()->findItemByBehavior( "behavior of remotely controlled one" ) );
        }

        switch ( activity )
        {
                case Wait:
                        break;

                case MoveNorth:
                case MoveSouth:
                case MoveEast:
                case MoveWest:
                        if ( theBehavior == "behavior of remotely controlled one" )
                        {
                                if ( speedTimer->getValue() > freeItem->getSpeed() )
                                {
                                        // move item
                                        whatToDo->move( this, &activity, true );

                                        if ( activity != Fall )
                                        {
                                                activity = Wait;
                                        }

                                        speedTimer->reset();
                                }

                                freeItem->animate();
                        }
                        break;

                case DisplaceNorth:
                case DisplaceSouth:
                case DisplaceEast:
                case DisplaceWest:
                case DisplaceNortheast:
                case DisplaceNorthwest:
                case DisplaceSoutheast:
                case DisplaceSouthwest:
                        if ( theBehavior == "behavior of remotely controlled one" )
                        {
                                if ( speedTimer->getValue() > freeItem->getSpeed() )
                                {
                                        // Emite el sonido de de desplazamiento si está siendo empujado, no desplazado
                                        // por un elemento que haya debajo
                                        if ( this->sender == 0 || ( this->sender != 0 && this->sender != this->item ) )
                                        {
                                                SoundManager::getInstance()->play( freeItem->getLabel(), activity );
                                        }

                                        // Desplaza el elemento una unidad
                                        whatToDo->displace( this, &activity, true );
                                        if ( activity != Fall )
                                        {
                                                activity = Wait;
                                        }

                                        speedTimer->reset();
                                }

                                freeItem->animate();
                        }

                        // Para los cuatro puntos cardinales básicos el elemento controlador debe cambiar el estado
                        // del elemento controlado
                        if ( activity == DisplaceNorth || activity == DisplaceSouth || activity == DisplaceEast || activity == DisplaceWest )
                        {
                                if ( theBehavior == "behavior of remote control" )
                                {
                                        ActivityOfItem motionActivity = Wait;

                                        switch ( activity )
                                        {
                                                case DisplaceNorth:
                                                        motionActivity = MoveNorth;
                                                        break;

                                                case DisplaceSouth:
                                                        motionActivity = MoveSouth;
                                                        break;

                                                case DisplaceEast:
                                                        motionActivity = MoveEast;
                                                        break;

                                                case DisplaceWest:
                                                        motionActivity = MoveWest;
                                                        break;

                                                default:
                                                        ;
                                        }

                                        dynamic_cast< RemoteControl * >( controlledItem->getBehavior() )->changeActivityOfItem( motionActivity );
                                        activity = Wait;
                                }
                        }
                        break;

                case Fall:
                        // Se comprueba si ha topado con el suelo en una sala sin suelo
                        if ( freeItem->getZ() == 0 && freeItem->getMediator()->getRoom()->getFloorType() == NoFloor )
                        {
                                // El elemento desaparece
                                destroy = true;
                        }
                        // Si este es el elemento controlado y ha llegado el momento de caer entonces
                        // el elemento desciende una unidad
                        else if ( theBehavior == "behavior of remotely controlled one" && fallTimer->getValue() > freeItem->getWeight() )
                        {
                                if ( ! whatToDo->fall( this ) )
                                {
                                        // Emite el sonido de caída
                                        SoundManager::getInstance()->play( freeItem->getLabel(), activity );
                                        activity = Wait;
                                }

                                // Se pone a cero el cronómetro para el siguiente ciclo
                                fallTimer->reset();
                        }
                        break;

                default:
                        ;
        }

        return destroy;
}

}
