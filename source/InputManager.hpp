// The free and open source remake of Head over Heels
//
// Copyright © 2025 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game by Jon Ritman and Bernie Drummond
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef InputManager_hpp_
#define InputManager_hpp_

#include <string>
#include <map>
#include <vector>

#include "WrappersAllegro.hpp"


class InputManager
{

private:

        InputManager( ) ;

        static InputManager * instance ;

        std::map < /* action */ std::string, /* key */ std::string > userKeys ;

public:

        ~InputManager( ) { }

        static InputManager & getInstance () ;

        void getAllActions ( std::vector< std::string > & listOfActions ) const ;

        /**
         * Returns the user-defined key for the given action, or "none"
         */
        std::string getUserKeyFor ( const std::string & action ) const ;

        void changeUserKey ( const std::string & action, const std::string & key ) ;

        bool movenorthTyped () const ;

        bool movesouthTyped () const ;

        bool moveeastTyped () const ;

        bool movewestTyped () const ;

        /**
         * Take an object below or drop what’s already taken
         */
        bool takeTyped () const ;

        /**
         * Character jumps
         */
        bool jumpTyped () const ;

        bool takeAndJumpTyped () const ;

        /**
         * Release a doughnut
         */
        bool doughnutTyped () const ;

        /**
         * Swap the characters
         */
        bool swapTyped () const ;

        /**
         * Pause the game
         */
        bool pauseTyped () const ;

        /**
         * Show the automap
         */
        bool automapTyped () const ;

        /**
         * Is any of the custom keys typed or not
         */
        bool userKeyTyped () const ;

        bool isOneOfTheUserKeys ( const std::string & key ) const ;

        void releaseKeyFor ( const std::string & action ) const ;

} ;

#endif
