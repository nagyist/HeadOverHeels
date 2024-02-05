
#include "SoundManager.hpp"

#include "util.hpp"
#include "ospaths.hpp"

#include <iostream>

#include <tinyxml2.h>

#ifdef DEBUG
#  define DEBUG_SOUNDS  0
#endif


/* static */ SoundManager * SoundManager::instance = nilPointer ;

/* static */ std::string SoundManager::audioInterface = "auto" ;


SoundManager::SoundManager( const std::string & audioInterface )
        : audioInitialized( false )
        , effectsVolume( 80 )
        , musicVolume( 75 )
{
        audioInitialized = allegro::initAudio( audioInterface ) ;
}

SoundManager::~SoundManager( )
{
        for ( std::map< std::string, allegro::Sample* >::iterator i = samples.begin (); i != samples.end (); ++ i )
                delete i->second ;
}

SoundManager& SoundManager::getInstance()
{
        if ( instance == nilPointer )
                instance = new SoundManager( SoundManager::audioInterface ) ;

        return *instance ;
}

void SoundManager::readSounds( const std::string& xmlFile )
{
        // read the list of sounds from an XML file
        tinyxml2::XMLDocument sounds;
        tinyxml2::XMLError result = sounds.LoadFile( ( ospaths::sharePath() + xmlFile ).c_str () );
        if ( result != tinyxml2::XML_SUCCESS )
        {
                std::cerr << "can’t read the list of sounds from \"" << xmlFile << "\"" << std::endl ;
                return;
        }

        tinyxml2::XMLElement* root = sounds.FirstChildElement( "sounds" );

        for ( tinyxml2::XMLElement* forItem = root->FirstChildElement( "for" ) ;
                        forItem != nilPointer ;
                        forItem = forItem->NextSiblingElement( "for" ) )
        {
                std::string kindOfItem = forItem->Attribute( "item" );

                for ( tinyxml2::XMLElement* sound = forItem->FirstChildElement( "sound" ) ;
                                sound != nilPointer ;
                                sound = sound->NextSiblingElement( "sound" ) )
                {
                        std::string event = sound->Attribute( "on" );
                        std::string sample = sound->Attribute( "play" );

                        addSound( kindOfItem, event, sample );
                }
        }

        std::cout << "read list of sounds from " << xmlFile << std::endl ;
}

void SoundManager::addSound( const std::string & item, const std::string & event, const std::string & sampleFile )
{
        this->sounds[ item ][ event ] = sampleFile ;

#if defined( DEBUG_SOUNDS ) && DEBUG_SOUNDS
        std::cout << "sound \"" << sampleFile << "\" on \"" << event << "\" for \"" << item << "\"" << std::endl ;
#endif

        if ( this->samples.find( sampleFile ) != this->samples.end () ) // it's already here
                return ;

        std::string pathToSample = ospaths::pathToFile( ospaths::sharePath() + "sound", sampleFile ) ;
        allegro::Sample* sample = allegro::Sample::loadFromFile( pathToSample );

        if ( sample != nilPointer && sample->isNotNil() )
        {
#if defined( DEBUG_SOUNDS ) && DEBUG_SOUNDS
                std::cout << "+ sample is read from file \"" << sampleFile << "\"" << std::endl ;
#endif
                this->samples[ sampleFile ] = sample;
        }
        else
        {
                std::cerr << "can’t read sound \"" << sampleFile << "\" (" << pathToSample << ")" << std::endl ;
        }
}

void SoundManager::play( const std::string & item, const std::string & event, bool loop )
{
        allegro::Sample* sample = getSampleFor( item, event );

        if ( sample != nilPointer && sample->isNotNil() && sample->getVoice() < 0 )
        {
                sample->setVolume( ( this->effectsVolume * 255 ) / 99 );

                if ( ! loop )
                        sample->play();
                else
                        sample->loop();

#if defined( DEBUG_SOUNDS ) && DEBUG_SOUNDS
                std::cout << ( loop ? "looping" : "playing" ) << " sound on \"" << event
                                << "\" for \"" << item << "\"" << std::endl ;
#endif
        }

        for ( std::map< std::string, allegro::Sample* >::const_iterator j = samples.begin (); j != samples.end (); ++ j )
                        if ( j->second != nilPointer ) j->second->neatenIfNotPlaying() ;
}

void SoundManager::stop( const std::string & item, const std::string & event )
{
        allegro::Sample* sample = getSampleFor( item, event );

        if ( sample != nilPointer && sample->isNotNil() )
        {
#if defined( DEBUG_SOUNDS ) && DEBUG_SOUNDS
                std::cout << "stopping sound on \"" << event << "\" for \"" << item << "\"" << std::endl ;
#endif
                sample->stop();
        }
}

void SoundManager::stopEverySound ()
{
        for ( std::map< std::string, allegro::Sample* >::const_iterator j = samples.begin (); j != samples.end (); ++ j )
        {
                if ( j->second != nilPointer ) j->second->stop();
        }
}

void SoundManager::playOgg ( const std::string & oggFile, bool loop )
{
        std::string fullName = ospaths::pathToFile( ospaths::sharePath(), oggFile );

         // to play the same again? yep, when it’s finished playing
        if ( oggPlayer.getFilePlaying() != fullName || ! oggPlayer.isPlaying() )
        {
                // it is playback of just single Ogg yet
                oggPlayer.stop();

                allegro::setDigitalVolume( ( this->musicVolume * 255 ) / 99 );

                oggPlayer.play( fullName, loop );

                if ( ! oggPlayer.getFilePlaying().empty() )
                        std::cout << ( loop ? "looping" : "playing" ) << " Ogg " << oggPlayer.getFilePlaying() << std::endl ;
        }
}

void SoundManager::setVolumeOfMusic( unsigned int volume )
{
          this->musicVolume = ( volume <= 99 ) ? volume : 99 ;
          allegro::setDigitalVolume( ( this->musicVolume * 255 ) / 99 );
}

allegro::Sample* SoundManager::getSampleFor( const std::string & item, const std::string & event )
{
        for ( std::map< std::string, std::map< std::string, std::string > >::const_iterator i = sounds.begin (); i != sounds.end (); ++ i )
                if ( item == i->first )
                        for ( std::map< std::string, std::string >::const_iterator j = i->second.begin (); j != i->second.end (); ++ j )
                                if ( event == j->first )
                                        if ( samples.find( j->second ) != samples.end () )
                                                return samples[ j->second ] ;

        return allegro::Sample::nilSample() ;
}

/* static */
std::string SoundManager::activityToString ( const activities::ActivityOfItem & activity )
{
        switch ( activity )
        {
                case activities::Activity::Wait : return "wait" ;

                case activities::Activity::Blink : return "blink" ;

                case activities::Activity::MoveNorth :
                case activities::Activity::MoveSouth :
                case activities::Activity::MoveEast :
                case activities::Activity::MoveWest :
                case activities::Activity::MoveNortheast :
                case activities::Activity::MoveSoutheast :
                case activities::Activity::MoveSouthwest :
                case activities::Activity::MoveNorthwest :
                case activities::Activity::MoveUp :
                case activities::Activity::MoveDown :
                case activities::Activity::AutoMoveNorth :
                case activities::Activity::AutoMoveSouth :
                case activities::Activity::AutoMoveEast :
                case activities::Activity::AutoMoveWest :
                        return "move" ;

                case activities::Activity::Jump : return "jump" ;

                case activities::Activity::Fall : return "fall" ;
                case activities::Activity::Glide : return "fall" ;

                case activities::Activity::TakeItem : case activities::Activity::TakeAndJump : return "take" ;
                case activities::Activity::ItemTaken : return "taken" ;
                case activities::Activity::DropItem : case activities::Activity::DropAndJump : return "drop" ;

                case activities::Activity::PushedNorth : case activities::Activity::PushedSouth :
                case activities::Activity::PushedEast : case activities::Activity::PushedWest :
                case activities::Activity::PushedNortheast : case activities::Activity::PushedSoutheast :
                case activities::Activity::PushedSouthwest : case activities::Activity::PushedNorthwest :
                case activities::Activity::PushedUp : /* case activities::Activity::PushedDown : */
                        return "push" ;

                case activities::Activity::DraggedNorth : case activities::Activity::DraggedSouth :
                case activities::Activity::DraggedEast : case activities::Activity::DraggedWest : return "dragged" ;

                case activities::Activity::CancelDragNorth : case activities::Activity::CancelDragSouth :
                case activities::Activity::CancelDragEast : case activities::Activity::CancelDragWest : return "move" ;

                case activities::Activity::BeginTeletransportation : return "teleport-out" ;
                case activities::Activity::EndTeletransportation : return "teleport-in" ;

                case activities::Activity::MeetMortalItem : return "lose-life" ;
                case activities::Activity::Vanish : return "vanish" ;
                case activities::Activity::Collision : return "collision" ;
                case activities::Activity::Function : return "function" ;
                case activities::Activity::Mistake : return "mistake" ;
        }

        return "other" ;
}
