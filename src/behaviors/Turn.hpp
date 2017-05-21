// The free and open source remake of Head over Heels
//
// Copyright © 2017 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef Turn_hpp_
#define Turn_hpp_

#include "Behavior.hpp"
#include "HPC.hpp"


namespace isomot
{

class Item ;

/**
 * Moves item in only one direction. When it collides with something,
 * it turns 90° left or right and continues to move
 */

class Turn : public Behavior
{

public:

       /**
        * Constructor
        * @param item Elemento que tiene este comportamiento
        * @param id Identificador del comportamiento: LeftTurnBehavior o RightTurnBehavior
        */
        Turn( Item * item, const BehaviorOfItem & id ) ;

        virtual ~Turn( ) ;

       /**
        * Actualiza el comportamiento del elemento en cada ciclo
        * @return false si la actualización implica la destrucción del elemento o true en caso contrario
        */
        virtual bool update () ;

protected:

       /**
        * Acciones a realizar cuando el elemento está en un estado ajeno a los estados propios de su
        * comportamiento
        */
        void start () ;

       /**
        * El elemento da media vuelta
        */
        void turn () ;

private:

       /**
        * Cronómetro que controla la velocidad de movimiento del elemento
        */
        HPC * speedTimer ;

       /**
        * Cronómetro que controla la velocidad de caída del elemento
        */
        HPC * fallTimer ;

};

}

#endif
