// The free and open source remake of Head over Heels
//
// Copyright © 2017 Douglas Mencken dougmencken@gmail.com
// Copyright © 2008 Jorge Rodríguez Santos
// Original game copyright © 1987 Ocean Software Ltd.
//
// This program is free software
// You may redistribute it and~or modify it under the terms of the GNU General Public License
// either version 3 of the License or at your option any later version

#ifndef Gui_hpp_
#define Gui_hpp_

#include <string>
#include <allegro.h>
#ifdef __WIN32
  #include <winalleg.h>
#endif


namespace gui
{

/**
 * Detiene un subproceso durante un periodo de tiempo
 * @param miliseconds Número de milisegundos que será detenido el subproceso
 */
void sleep ( unsigned long miliseconds ) ;

/**
 * Object-function for destruction of objects of Standard Template Library container
 */
struct DeleteObject
{
        template < typename T >
        void operator() ( const T * ptr ) const
        {
                if ( ptr != 0 )
                {
                        delete ptr;
                }
        }
};

/**
 * Maximum number of letters
 */
const int HowManyLetters = 336;

/**
 * Table of letters in UTF-8
 */
const std::string letters[ HowManyLetters ] =
{
        " ",        "!",        "\"",       "",         "$",        "",         "&",        "'",
        "(",        ")",        "",         "+",        ",",        "-",        ".",        "/",
        "0",        "1",        "2",        "3",        "4",        "5",        "6",        "7",
        "8",        "9",        ":",        ";",        "",         "",         "",         "?",
        "",         "A",        "B",        "C",        "D",        "E",        "F",        "G",
        "H",        "I",        "J",        "K",        "L",        "M",        "N",        "O",
        "P",        "Q",        "R",        "S",        "T",        "U",        "V",        "W",
        "X",        "Y",        "Z",        "",         "",         "",         "",         "_",
        "",         "a",        "b",        "c",        "d",        "e",        "f",        "g",
        "h",        "i",        "j",        "k",        "l",        "m",        "n",        "o",
        "p",        "q",        "r",        "s",        "t",        "u",        "v",        "w",
        "x",        "y",        "z",        "{",        "",         "}",        "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "\305\240", "",         "\305\222", "",         "",         "",
        "",         "",         "",         "",         "\302\267", "",         "",         "",
        "",         "",         "\305\241", "",         "\305\223", "",         "",         "\305\270",
        "",         "\302\241", "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "\302\277",
        "\303\200", "\303\201", "\303\203", "\303\204", "\303\205", "\303\206", "\303\207", "\303\210",
        "\303\211", "\303\212", "\303\213", "\303\214", "\303\215", "\303\216", "\303\217", "\303\220",
        "\303\221", "\303\222", "\303\223", "\303\224", "\303\225", "\303\226", "",         "\303\230",
        "\303\231", "\303\232", "\303\233", "\303\234", "\303\235", "\303\236", "\303\237", "\303\240",
        "\303\241", "\303\242", "\303\243", "\303\244", "\303\245", "\303\246", "\303\247", "\303\250",
        "\303\251", "\303\252", "\303\253", "\303\254", "\303\255", "\303\256", "\303\257", "\303\260",
        "\303\261", "\303\262", "\303\263", "\303\264", "\303\265", "\303\266", "",         "\303\270",
        "\303\271", "\303\272", "\303\273", "\303\274", "\303\275", "\303\276", "\303\277", "",
        "\304\204", "\304\205", "\304\206", "\304\207", "\304\230", "\304\231", "\305\201", "\305\202",
        "\305\203", "\305\204", "\305\232", "\305\233", "\305\273", "\305\274", "\305\271", "\305\272",
        "\305\275", "\305\276", "\304\214", "\304\215", "\304\216", "\304\217", "\304\275", "\304\276",
        "\305\244", "\305\245", "\304\220", "\304\221", "\305\207", "\305\210", "",         "",
        "\320\220", "\320\221", "\320\222", "\320\223", "\320\224", "\320\225", "\320\226", "\320\227",
        "\320\230", "\320\231", "\320\232", "\320\233", "\320\234", "\320\235", "\320\236", "\320\237",
        "\320\240", "\320\241", "\320\242", "\320\243", "\320\244", "\320\245", "\320\246", "\320\247",
        "\320\250", "\320\251", "\320\252", "\320\253", "\320\254", "\320\255", "\320\256", "\320\257",
        "\320\260", "\320\261", "\320\262", "\320\263", "\320\264", "\320\265", "\320\266", "\320\267",
        "\320\270", "\320\271", "\320\272", "\320\273", "\320\274", "\320\275", "\320\276", "\320\277",
        "\321\200", "\321\201", "\321\202", "\321\203", "\321\204", "\321\205", "\321\206", "\321\207",
        "\321\210", "\321\211", "\321\212", "\321\213", "\321\214", "\321\215", "\321\216", "\321\217",
        "\320\202", "\320\210", "\320\211", "\320\212", "\320\213", "\320\217", "\321\222", "\321\230",
        "\321\231", "\321\232", "\321\233", "\321\237", "",         "",         "",         ""
};

/*
 * moves the iterator to next unicode character in the string, returns number of bytes skipped
 * from code by Albert Zeyer and Dark Charlie licensed under LGPL https://sourceforge.net/p/openlierox/code/ci/master/tree/include/Unicode.h
 */
template < typename _Iterator1, typename _Iterator2 >
inline size_t incUtf8StringIterator( _Iterator1 & it, const _Iterator2 & last )
{
        if ( it == last ) return 0;
        unsigned char c;
        it ++;
        size_t inc = 1;
        for ( ; last != it; ++inc ) {
                c = *it;
                if ( ! ( c & 0x80 ) || ( ( c & 0xC0 ) == 0xC0 ) ) break;
                it++ ;
        }

        return inc;
}

/*
 * gives the real length of UTF-8 encoded std::string
 * from code by Albert Zeyer and Dark Charlie licensed under LGPL https://sourceforge.net/p/openlierox/code/ci/master/tree/include/Unicode.h
 */
inline size_t utf8StringLength( const std::string& str )
{
        size_t len = 0;
        std::string::const_iterator it = str.begin ();
        for ( ; it != str.end (); incUtf8StringIterator ( it, str.end () ) )
                len ++;

        return len ;
}

}

#endif
