// The free and open source remake of Head over Heels
//
// Copyright © 2025 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game by Jon Ritman and Bernie Drummond
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef FloorTile_hpp_
#define FloorTile_hpp_

#include "Drawable.hpp"
#include "Mediated.hpp"
#include "Shady.hpp"
#include "Picture.hpp"


/**
 * A set of such tiles forms the floor of the room
 */

class FloorTile : public Drawable, public Mediated, public Shady
{

public:

        FloorTile( int cellX, int cellY, const Picture & graphicsOfTile ) ;

        virtual ~FloorTile( ) { }

        virtual void draw () ;

        virtual void setMediator ( Mediator* mediator )
                {   Mediated::setMediator( mediator ); calculateOffset ();   }

private:

        // calculates the offset of this tile’s graphics in the room
        void calculateOffset () ;

        std::string uniqueName;

        /**
         * X and Y coordinates on grid
         */
        std::pair < int, int > coordinates ;

        /**
         * Offset ( X, Y ) of tile’s graphics
         */
        std::pair < int, int > offset ;

        /**
         * Picture of the tile
         */
        autouniqueptr< Picture > rawImage ;

        /**
         * Picture of the shaded tile
         */
        autouniqueptr< Picture > shadyImage ;

public:

        /**
         * The number of room’s column where this tile is located
         */
        unsigned int getIndexOfColumn () const ;

        std::string getUniqueName () const {  return uniqueName ;  }

        int getCellX () const {  return coordinates.first ;  }

        int getCellY () const {  return coordinates.second ;  }

        int getOffsetX () const {  return offset.first ;  }

        int getOffsetY () const {  return offset.second ;  }

        const Picture & getRawImage () const {  return * this->rawImage ;  }

        const Picture & getShadyImage () const {  return * this->shadyImage ;  }

        void setAsShadyImage ( const Picture & toCopy ) ;

        void freshShadyImage () ;

        static PicturePtr fullTileToPartialTile ( const Picture & fullTile, const std::string & whichPart, bool darkenPlane = true ) ;

};

typedef multiptr < FloorTile > FloorTilePtr ;

#endif
