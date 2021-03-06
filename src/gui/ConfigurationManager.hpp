// The free and open source remake of Head over Heels
//
// Copyright © 2017 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef ConfigurationManager_hpp_
#define ConfigurationManager_hpp_

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <allegro.h>
#include "csxml/ConfigurationXML.hpp"
#include "Ism.hpp"

namespace gui
{

/**
 * Almacena la configuración del juego que puede cambiar el usuario:
 * el idioma, las teclas y el nivel de volumen de los efectos sonoros
 * y la música
 */
class ConfigurationManager
{

public:

        /**
         * Constructor
         * @param fileName Archivo XML con la configuración del juego
         */
        ConfigurationManager( const std::string& fileName ) ;

        /**
         * Lee los datos de configuración y los almacena en los atributos para que
         * posteriormente puedan leerlos otros objetos de la interfaz de usuario
         */
        void read () ;

        /**
         * Guarda los datos de configuración almacenados en los atributos que han
         * podido modificar otros objetos de la interfaz de usuario
         */
        void write () ;

private:

        /**
         * Archivo XML con la configuración del juego
         */
        std::string fileName ;

        /**
         * Idioma empleado en la interfaz de usuario
         */
        std::string language ;

public: // Operaciones de consulta y actualización

        /**
         * Asigna el idioma empleado en la interfaz de usuario
         * @param language una cadena de caracteres con el formato LLL_CC donde LLL es un código de
         * idioma según la norma ISO 639-2 y CC es un código de país según la norma ISO 3166
         */
        void setLanguage ( const std::string& language ) {  this->language = language ;  }

        /**
         * Idioma empleado en la interfaz de usuario
         * @return Una cadena de caracteres con el formato LLL_CC donde LLL es un código de
         * idioma según la norma ISO 639 y CC es un código de país según la norma ISO 3166
         */
        std::string getLanguage () {  return this->language ;  }

        /**
         * Asigna una tecla a una acción del juego
         * @param nameOfKey Una acción del juego
         * @param keyCode Una tecla según la codificación de Allegro: KEY_LEFT, KEY_A, etc
         */
        void setKey ( const std::string& nameOfKey, int keyCode ) ;

        /**
         * Tecla ligada a una acción del juego
         * @param nameOfKey Una acción del juego
         * @return Una tecla según la codificación de Allegro: KEY_LEFT, KEY_A, etc
         */
        int getKey ( const std::string& nameOfKey ) ;

        /**
         * Asigna el volumen de los efectos de sonido
         * @param volume Un valor entre 0 y 99, ambos inclusive
         */
        void setVolumeOfSoundEffects ( int volume ) const ;

        /**
         * Volumen de los efectos de sonido
         * @return Un valor entre 0 y 99, ambos inclusive
         */
        int getVolumeOfSoundEffects () const ;

        /**
         * Asigna el volumen de la música
         * @param volume Un valor entre 0 y 99, ambos inclusive
         */
        void setVolumeOfMusic ( int volume ) const ;

        /**
         * Volumen de la música
         * @return Un valor entre 0 y 99, ambos inclusive
         */
        int getVolumeOfMusic () const ;

};

}

#endif
