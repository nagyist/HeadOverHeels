// The free and open source remake of Head over Heels
//
// Copyright © 2018 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef FreeItem_hpp_
#define FreeItem_hpp_

#include <utility>
#include <cmath>
#include <allegro.h>

#include "Ism.hpp"

#include "Item.hpp"
#include "Drawable.hpp"


namespace isomot
{

class ItemData;

/**
 * Free elements are those that can be anywhere and move freely around the room
 * such as players, enemies, or something which widths differ from widths of grid cells
 */

class FreeItem : public Drawable, public Item
{

public:

       /**
        * Constructor
        * @param itemData data about this item
        * @param x Posición espacial X
        * @param y Posición espacial Y
        * @param z Posición espacial Z o a qué distancia está el elemento del suelo
        * @param direction Dirección inicial del elemento
        */
        FreeItem( ItemData* itemData, int x, int y, int z, const Way& way ) ;

       /**
        * Constructor copia. No copia los atributos que son punteros
        * @param freeItem Un objeto de esta clase
        */
        FreeItem( const FreeItem& freeItem ) ;

        virtual ~FreeItem( ) ;

        virtual std::string whichKindOfItem () const {  return "free item" ;  }

        /**
         * Dibuja el elemento libre
         */
        void draw ( BITMAP* where ) ;

        void binProcessedImages () ;

        /**
         * Cambia la presentación gráfica del elemento, destruyendo la imagen procesada y señalando qué elementos
         * hay que volver a enmascarar
         * @param image Un fotograma del elemento
         */
        void changeImage ( BITMAP* image ) ;

        /**
         * Cambia la sombra de la presentación gráfica del elemento, destruyendo la imagen procesada y señalando
         * qué elementos hay que volver a sombrear
         * @param image Una sombra de un fotograma del elemento
         */
        void changeShadow ( BITMAP* shadow ) ;

        /**
         * Solicita el sombreado del elemento
         */
        void requestCastShadow () ;

        /**
         * Sombrea la imagen del elemento con la sombra de otro elemento
         * @param x Coordenada X de pantalla donde está situada la base del elemento que sombrea
         * @param y Coordenada Y de pantalla donde está situada la base del elemento que sombrea
         * @param shadow La sombra que se proyecta sobre el elemento
         * @param shadingScale Grado de opacidad de las sombras desde 0, sin sombras, hasta 256,
         *                     sombras totalmente opacas
         * @param transparency Grado de transparencia del elemento que sombrea
         */
        void castShadowImage ( int x, int y, BITMAP* shadow, short shadingScale, unsigned char transparency = 0 ) ;

        /**
         * Solicita enmascarar el elemento
         */
        void requestMask () ;

        /**
         * Enmascara la imagen del elemento con la imagen de otro elemento
         * @param x Coordenada X de pantalla donde está situada la imagen del elemento que servirá de máscara
         * @param y Coordenada Y de pantalla donde está situada la imagen del elemento que servirá de máscara
         */
        void maskImage ( int x, int y, BITMAP* image ) ;

        /**
         * Cambia el valor de la coordenada X
         * @param value Valor que se sumará a la coordenada X actual
         * @return true si se pudo cambiar el dato o false si hubo colisión y no hubo cambio
         */
        virtual bool addToX ( int value ) ;

        /**
         * Cambia el valor de la coordenada Y
         * @param value Valor que se sumará a la coordenada Y actual
         * @return true si se pudo cambiar el dato o false si hubo colisión y no hubo cambio
         */
        virtual bool addToY ( int value ) ;

        /**
         * Cambia el valor de la coordenada Z
         * @param value Valor que se sumará a la coordenada Z actual
         * @return true si se pudo cambiar el dato o false si hubo colisión y no hubo cambio
         */
        virtual bool addToZ ( int value ) ;

        /**
         * Cambia la posición del elemento
         * @param x Valor que se sumará a la coordenada X actual
         * @param y Valor que se sumará a la coordenada Y actual
         * @param z Valor que se sumará a la coordenada Z actual
         * @return true si se pudo cambiar el dato o false si hubo colisión y no hubo cambio
         */
        virtual bool addToPosition ( int x, int y, int z ) ;

        /**
         * Cambia el grado de transparencia del elemento
         * @param value Valor de transparencia en un porcentaje de 0 a 100
         * @param mode Modo para interpretar el nuevo valor. Puede usarse Change para cambiarlo o Add para sumarlo
         * @return true si el cambio de transparencia tuvo efecto o false en caso contrario
         */
        bool changeTransparency ( unsigned char value, const ChangeOrAdd& changeOrAdd ) ;

protected:

        virtual bool updatePosition ( int newX, int newY, int newZ, const Coordinate& whatToChange, const ChangeOrAdd& addOrChange ) ;

protected:

        /**
         * Estado del proceso de enmascarado
         */
        WhichMask myMask ;

        /**
         * Grado de transparencia del elemento en un porcentaje de 0 a 100
         */
        unsigned char transparency ;

        /**
         * Whether this item detects collisions
         */
        bool collisionDetector ;

        /**
         * Indica si el elemento está inactivo
         */
        bool frozen ;

        /**
         * Current frame of this item shaded but not masked
         */
        BITMAP * shadyImage ;

public:

        /**
         * Establece el estado del proceso de enmascarado
         */
        void setWhichMask ( const WhichMask& mask ) {  myMask = mask ;  }

        /**
         * Devuelve el estado del proceso de enmascarado
         */
        WhichMask whichMask () const {  return myMask ;  }

        /**
         * Grado de transparencia del elemento
         * @return Un número entre 0 y 100, inclusive
         */
        unsigned char getTransparency () const {  return transparency ;  }

        /**
         * Establece la capacidad del elemento para detectar colisiones
         * @param collisionDetector true si detecta colisiones, valor por defecto al crear el elemento, o false caso contrario
         */
        void setCollisionDetector ( bool collisionDetector ) {  this->collisionDetector = collisionDetector ;  }

        /**
         * Indica si el elemento detecta colisiones
         * @return true si detecta colisiones o false caso contrario
         */
        bool isCollisionDetector () const {  return collisionDetector ;  }

        /**
         * Establece si el elemento está inactivo
         * @param frozen true si está detenido o false en caso contrario
         */
        void setFrozen ( bool frozen ) {  this->frozen = frozen ;  }

        /**
         * Indica si el elemento está inactivo
         * @return true si está detenido o false en caso contrario
         */
        bool isFrozen () const {  return frozen ;  }

};

}

#endif
