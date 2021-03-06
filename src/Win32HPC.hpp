// The free and open source remake of Head over Heels
//
// Copyright © 2017 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef Win32HPC_hpp_
#define Win32HPC_hpp_

#include <allegro.h>
#include <winalleg.h>

/**
 * Cronómetro de alta precisión para sistemas Windows
 */
class HPC
{
public:

        HPC();

        /**
         * Pone en marcha el cronómetro
         * @return true si el sistema dispone de un cronómetro de alta precisión
         */
        bool start();

        /**
         * Devuelve el número de segundos transcurridos desde que el cronómetro se puso en marcha
         */
        double getValue();

        /**
         * Pone a cero el cronómetro
         */
        void reset();

        /**
         * Detiene el cronómetro
         */
        void stop();

        /**
         * Reinicia el cronómetro
         * @preconditions El cronómetro debe estar detenido
         */
        void restart();

protected:

        /**
         * Frecuencia
         */
        LARGE_INTEGER frequency;

        /**
         * Instante en el que se puso en marcha el cronómetro
         */
        LARGE_INTEGER startTime;

        /**
         * Instante en el que se detiene el cronómetro
         */
        LARGE_INTEGER stopTime;

        /**
         * Periodo de tiempo transcurrido entre que el cronómetro se paró y se volvió a poner en marcha
         */
        LARGE_INTEGER period;
};

#endif
