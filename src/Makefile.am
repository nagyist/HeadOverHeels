AUTOMAKE_OPTIONS = -Wno-override
AM_CCFLAGS = -Wall -O2
AM_CXXFLAGS = $(CXXFLAGS)
headoverheels_CXXFLAGS = -Wall -Wno-deprecated -O2 -I. -Iloadpng -Iactions -Ibehaviors -Igui -Istates
AM_LDFLAGS = `allegro-config --libs release` -lvorbisfile -lvorbisenc -lvorbis -logg -lxerces-c -lpthread -lz -lpng

bin_PROGRAMS = headoverheels
headoverheels_SOURCES = loadpng/loadpng.c \
			loadpng/savepng.c \
			loadpng/regpng.c \
			main.cpp \
			BonusManager.cpp \
			BonusManager.hpp \
			Camera.cpp \
			Camera.hpp \
			Door.cpp \
			Door.hpp \
			Exception.cpp \
			Exception.hpp \
			FloorTile.cpp \
			FloorTile.hpp \
			FreeItem.cpp \
			FreeItem.hpp \
			GameFileManager.cpp \
			GameFileManager.hpp \
			GameManager.cpp \
			GameManager.hpp \
			GridItem.cpp \
			GridItem.hpp \
			HPC.hpp \
			InputManager.cpp \
			InputManager.hpp \
			Ism.cpp \
			Ism.hpp \
			Isomot.cpp \
			Isomot.hpp \
			Item.cpp \
			ItemData.cpp \
			ItemData.hpp \
			ItemDataManager.cpp \
			ItemDataManager.hpp \
			Item.hpp \
			LinuxHPC.cpp \
			LinuxHPC.hpp \
			MapManager.cpp \
			MapManager.hpp \
			MapRoomData.cpp \
			MapRoomData.hpp \
			Mediator.cpp \
			Mediator.hpp \
			PlayerItem.cpp \
			PlayerItem.hpp \
			RoomBuilder.cpp \
			RoomBuilder.hpp \
			Drawable.hpp \
			Mediated.hpp \
			Room.cpp \
			Room.hpp \
			SoundManager.cpp \
			SoundManager.hpp \
			TransparencyManager.cpp \
			TransparencyManager.hpp \
			Wall.cpp \
			Wall.hpp \
			Win32HPC.cpp \
			Win32HPC.hpp \
			actions/Action.hpp \
			actions/PlaySound.hpp \
			actions/ContinueGame.cpp \
			actions/ContinueGame.hpp \
			actions/CreateAudioMenu.cpp \
			actions/CreateAudioMenu.hpp \
			actions/CreateVideoMenu.hpp \
			actions/CreateVideoMenu.cpp \
			actions/CreateMenuOfGraphicSets.hpp \
			actions/CreateMenuOfGraphicSets.cpp \
			actions/CreateCongratulationsScreen.cpp \
			actions/CreateCongratulationsScreen.hpp \
			actions/CreateEndScreen.cpp \
			actions/CreateEndScreen.hpp \
			actions/CreateListOfSavedGames.cpp \
			actions/CreateListOfSavedGames.hpp \
			actions/CreateKeyboardMenu.cpp \
			actions/CreateKeyboardMenu.hpp \
			actions/CreateLanguageMenu.cpp \
			actions/CreateLanguageMenu.hpp \
			actions/CreateMainMenu.cpp \
			actions/CreateMainMenu.hpp \
			actions/CreatePlanetsScreen.cpp \
			actions/CreatePlanetsScreen.hpp \
			actions/ExitApplication.cpp \
			actions/ExitApplication.hpp \
			actions/LoadGame.cpp \
			actions/LoadGame.hpp \
			actions/RedefineKey.cpp \
			actions/RedefineKey.hpp \
			actions/SaveGame.cpp \
			actions/SaveGame.hpp \
			actions/SelectLanguage.cpp \
			actions/SelectLanguage.hpp \
			actions/ShowAuthors.cpp \
			actions/ShowAuthors.hpp \
			alogg/alogg.c \
			alogg/aloggcfg.h \
			alogg/alogg.h \
			alogg/aloggint.h \
			alogg/aloggpth.c \
			alogg/aloggpth.h \
			behaviors/Behavior.cpp \
			behaviors/Behavior.hpp \
			behaviors/CannonBall.cpp \
			behaviors/CannonBall.hpp \
			behaviors/ConveyorBelt.cpp \
			behaviors/ConveyorBelt.hpp \
			behaviors/Detector.cpp \
			behaviors/Detector.hpp \
			behaviors/Drive.cpp \
			behaviors/Drive.hpp \
			behaviors/Elevator.cpp \
			behaviors/Elevator.hpp \
			behaviors/Hunter.cpp \
			behaviors/Hunter.hpp \
			behaviors/Impel.cpp \
			behaviors/Impel.hpp \
			behaviors/Mobile.cpp \
			behaviors/Mobile.hpp \
			behaviors/OneWay.cpp \
			behaviors/OneWay.hpp \
			behaviors/Patrol.cpp \
			behaviors/Patrol.hpp \
			behaviors/PlayerHeadAndHeels.cpp \
			behaviors/PlayerHeadAndHeels.hpp \
			behaviors/PlayerHead.cpp \
			behaviors/PlayerHead.hpp \
			behaviors/PlayerHeels.cpp \
			behaviors/PlayerHeels.hpp \
			behaviors/RemoteControl.cpp \
			behaviors/RemoteControl.hpp \
			behaviors/Shot.cpp \
			behaviors/Shot.hpp \
			behaviors/Sink.cpp \
			behaviors/Sink.hpp \
			behaviors/Special.cpp \
			behaviors/Special.hpp \
			behaviors/Switch.cpp \
			behaviors/Switch.hpp \
			behaviors/Teleport.cpp \
			behaviors/Teleport.hpp \
			behaviors/Trampoline.cpp \
			behaviors/Trampoline.hpp \
			behaviors/Turn.cpp \
			behaviors/Turn.hpp \
			behaviors/UserControlled.cpp \
			behaviors/UserControlled.hpp \
			behaviors/Volatile.cpp \
			behaviors/Volatile.hpp \
			csxml/ConfigurationXML.cpp \
			csxml/ConfigurationXML.hpp \
			csxml/ItemsXML.cpp \
			csxml/ItemsXML.hpp \
			csxml/LanguageXML.cpp \
			csxml/LanguageXML.hpp \
			csxml/MapXML.cpp \
			csxml/MapXML.hpp \
			csxml/RoomXML.cpp \
			csxml/RoomXML.hpp \
			csxml/SaveGameXML.cpp \
			csxml/SaveGameXML.hpp \
			csxml/SoundsXML.cpp \
			csxml/SoundsXML.hpp \
			gui/ConfigurationManager.cpp \
			gui/ConfigurationManager.hpp \
			gui/Font.cpp \
			gui/Font.hpp \
			gui/FontManager.cpp \
			gui/FontManager.hpp \
			gui/Gui.cpp \
			gui/Gui.hpp \
			gui/GuiManager.cpp \
			gui/GuiManager.hpp \
			gui/Icon.cpp \
			gui/Icon.hpp \
			gui/Label.cpp \
			gui/Label.hpp \
			gui/LanguageManager.cpp \
			gui/LanguageManager.hpp \
			gui/Menu.cpp \
			gui/Menu.hpp \
			gui/MenuWithMultipleColumns.cpp \
			gui/MenuWithMultipleColumns.hpp \
			gui/Screen.cpp \
			gui/Screen.hpp \
			gui/TextField.cpp \
			gui/TextField.hpp \
			gui/Widget.cpp \
			gui/Widget.hpp \
			states/BehaviorState.cpp \
			states/BehaviorState.hpp \
			states/DisplaceState.cpp \
			states/DisplaceState.hpp \
			states/FallState.cpp \
			states/FallState.hpp \
			states/JumpState.cpp \
			states/JumpState.hpp \
			states/MoveState.cpp \
			states/MoveState.hpp
