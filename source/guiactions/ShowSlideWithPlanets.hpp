// The free and open source remake of Head over Heels
//
// Copyright © 2025 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game by Jon Ritman and Bernie Drummond
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef ShowSlideWithPlanets_hpp_
#define ShowSlideWithPlanets_hpp_

#include "Action.hpp"


namespace gui
{

class ShowSlideWithPlanets : public Action
{

public :

        ShowSlideWithPlanets( )
                : Action( )
        {}

        virtual ~ShowSlideWithPlanets( ) {}

protected :

        virtual void act () ;

} ;

}

#endif
