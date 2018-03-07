
#include "CreateLanguageMenu.hpp"
#include "Ism.hpp"
#include "GuiManager.hpp"
#include "LanguageManager.hpp"
#include "ConfigurationManager.hpp"
#include "Font.hpp"
#include "LanguageText.hpp"
#include "Screen.hpp"
#include "MenuWithTwoColumns.hpp"
#include "Label.hpp"
#include "SelectLanguage.hpp"
#include "CreateMainMenu.hpp"

using gui::CreateLanguageMenu;
using gui::GuiManager;
using gui::LanguageManager;
using gui::LanguageText;
using gui::SelectLanguage;


CreateLanguageMenu::CreateLanguageMenu( BITMAP* picture )
        : Action( picture )
{
        // read list of languages available for this game
        this->parse( isomot::sharePath() + "text" + pathSeparator + "language.xml" );
}

CreateLanguageMenu::~CreateLanguageMenu( )
{
        this->texts.clear();
}

void CreateLanguageMenu::doAction ()
{
        Screen* screen = GuiManager::getInstance()->findOrCreateScreenForAction( this );
        if ( screen->countWidgets() > 0 )
        {
                screen->freeWidgets();
        }

        screen->setEscapeAction( new gui::CreateMainMenu( getWhereToDraw() ) );

        Label* label = nilPointer;

        label = new Label( "Head", "big", "yellow" );
        label->moveTo( 200, 24 );
        screen->addWidget( label );

        label = new Label( "over", "regular", "multicolor" );
        label->moveTo( 280, 45 );
        screen->addWidget( label );

        label = new Label( "Heels", "big", "yellow" );
        label->moveTo( 360, 24 );
        screen->addWidget( label );

        screen->addPictureOfHeadAt( 66, 24 );
        screen->addPictureOfHeelsAt( 518, 24 );

        // presenta los idiomas disponibles

        std::string language = GuiManager::getInstance()->getLanguage();

        MenuWithTwoColumns * menu = new MenuWithTwoColumns( /* space between columns */ 60 );
        menu->setVerticalOffset( 50 ); // adjust for header over heelser

        for ( std::list< LanguageText * >::iterator i = this->texts.begin (); i != this->texts.end (); ++i )
        {
                label = new Label( ( *i )->getText() );
                label->setAction( new SelectLanguage( getWhereToDraw(), ( *i )->getId() ) );

                menu->addOption( label );

                if ( ( language.empty() && i == this->texts.begin() ) || language == ( *i )->getId() )
                {
                        menu->setActiveOption( label );
                }
        }

        screen->addWidget( menu );
        screen->setKeyHandler( menu );

        Screen::randomPixelFadeIn( Color::blackColor(), screen );
        GuiManager::getInstance()->changeScreen( screen, true );
}

void CreateLanguageMenu::parse( const std::string& fileName )
{
        // Carga el archivo XML especificado y almacena los datos XML en la lista
        try
        {
                std::auto_ptr< lxml::LanguageXML > languageXML( lxml::language( fileName.c_str() ) );

                // Almacena todos los registros del archivo en la lista
                for ( lxml::LanguageXML::text_const_iterator t = languageXML->text().begin (); t != languageXML->text().end (); ++t )
                {
                        LanguageText* lang = new LanguageText( ( *t ).id () );

                        for ( lxml::text::properties_const_iterator p = ( *t ).properties().begin (); p != ( *t ).properties().end (); ++p )
                        {
                                for ( lxml::properties::ustring_const_iterator u = ( *p ).ustring().begin (); u != ( *p ).ustring().end (); ++u )
                                {
                                        lang->addLine( *u, std::string(), std::string() );
                                }
                        }

                        this->texts.push_back( lang );
                }
        }
        catch ( const xml_schema::exception& e )
        {
                std::cerr << e << std::endl ;
        }
}
