// The free and open source remake of Head over Heels
//
// Copyright © 2017 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef ItemData_hpp_
#define ItemData_hpp_

#include <vector>
#include <string>
#include <cassert>
#include <allegro.h>


namespace isomot
{

/**
 * Container for definition of an item read from file
 */

class ItemData
{

friend class ItemDataManager ;

public:

        ItemData( ) ;

        virtual ~ItemData( ) ;

        static ItemData * clone ( ItemData * data ) ;

public:

        std::string getNameOfFile () {  return this->nameOfFile;  }

        void setNameOfFile ( std::string newName ) {  this->nameOfFile = newName ;  }

        void clearNameOfFile () {  this->nameOfFile.clear() ;  }

        std::string getNameOfShadowFile () {  return this->nameOfShadowFile;  }

        void setNameOfShadowFile ( std::string newNameOfShadow ) {  this->nameOfShadowFile = newNameOfShadow ;  }

        void clearNameOfShadowFile () {  this->nameOfShadowFile.clear() ;  }

        std::string getLabel () const {  return label ;  }

        unsigned int getWidthX () const {  return widthX ;  }

        void setWidthX ( unsigned int newWidthX ) {  widthX = newWidthX ;  }

        unsigned int getWidthY () const {  return widthY ;  }

        void setWidthY ( unsigned int newWidthY ) {  widthY = newWidthY ;  }

        unsigned int getHeight () const {  return height ;  }

        void setHeight ( unsigned int newHeight ) {  height = newHeight ;  }

        double getWeight() const {  return weight ;  }

        double getSpeed() const {  return speed ;  }

        double getDelayBetweenFrames () const {  return delayBetweenFrames ;  }

        unsigned int getWidthOfFrame () const {  return widthOfFrame ;  }

        unsigned int getHeightOfFrame () const {  return heightOfFrame ;  }

        unsigned int getWidthOfShadow () const {  return widthOfShadow ;  }

        unsigned int getHeightOfShadow () const {  return heightOfShadow ;  }

        bool isMortal() const {  return mortal ;  }

        unsigned short howManyFramesForOrientations () const {  return orientationFrames ;  }

        unsigned int howManyExtraFrames () const {  return extraFrames ;  }

        unsigned int howManyMotions () const {  return motion.size () ;  }

        BITMAP * getMotionAt( size_t at ) const
        {
                assert( at < motion.size () );
                return motion[ at ] ;
                /// return ( at < motion.size() ? motion[ at ] : 0 ) ;
        }

        unsigned int howManyShadows () const {  return shadows.size () ;  }

        BITMAP * getShadowAt( size_t at ) const
        {
                assert( at < shadows.size () );
                return shadows[ at ] ;
                /// return ( at < shadows.size() ? shadows[ at ] : 0 ) ;
        }

        int getFrameAt( size_t at ) const
        {
                return ( at < frames.size () ? frames[ at ] : 0 ) ;
        }

        unsigned int howManyFrames () const {  return frames.size() ;  }

private:

       /**
        * Label names item uniquely, there’s no two different items with one label
        */
        std::string label ;

       /**
        * Spatial width of item along X axis
        */
        unsigned int widthX ;

       /**
        * Spatial width of item along Y axis
        */
        unsigned int widthY ;

       /**
        * Spatial height of item
        */
        unsigned int height ;

       /**
        * Weight of item in milliseconds, higher for bigger speed of falling, 0 for don’t fall
        */
        double weight ;

       /**
        * Time in milliseconds needed for item to move
        */
        double speed ;

       /**
        * How many frames for orientations
        */
        unsigned short orientationFrames ;

       /**
        * Time in milliseconds to show each frame of animation
        */
        double delayBetweenFrames ;

       /**
        * Width in pixels of each frame for item
        */
        unsigned int widthOfFrame ;

       /**
        * Height in pixels of each frame for item
        */
        unsigned int heightOfFrame ;

       /**
        * Width in pixels of each frame for item’s shadow
        */
        unsigned int widthOfShadow ;

       /**
        * Height in pixels of each frame for item’s shadow
        */
        unsigned int heightOfShadow ;

        bool mortal ;

       /**
        * Extra frames are those that don’t relate to regular motion, such as frames of jump
        */
        unsigned int extraFrames ;

       /**
        * Frames that define sequence of animation
        */
        std::vector< int > frames ;

       /**
        * Pictures of item
        */
        std::vector< BITMAP * > motion ;

       /**
        * Pictures of item’s shadow
        */
        std::vector< BITMAP * > shadows ;

       /**
        * Name of the file that contains the frames of this item
        */
        std::string nameOfFile ;

       /**
        * Name of the file that contains the shadows for this item
        */
        std::string nameOfShadowFile ;

};

}

#endif
