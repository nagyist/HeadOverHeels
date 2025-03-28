
#include "LoadGame.hpp"

#include "ospaths.hpp"

#include "GameManager.hpp"
#include "SoundManager.hpp"
#include "ShowSlideWithPlanets.hpp"
#include "PresentTheMainMenu.hpp"


void gui::LoadGame::act ()
{
        GameManager & gameManager = GameManager::getInstance () ;
        gameManager.resetPlanets() ;

        bool loaded = gameManager.loadGame( ospaths::pathToFile( ospaths::homePath() + "savegame", "saved." + util::number2string( slot ) ) );

        if ( ! loaded ) {
                SoundManager::getInstance().stopEverySound ();
                SoundManager::getInstance().play( "menus", "mistake", /* loop */ false );

                ( new PresentTheMainMenu() )->doIt () ;
                return ;
        }

        ( new ShowSlideWithPlanets() )->doIt ();
}
