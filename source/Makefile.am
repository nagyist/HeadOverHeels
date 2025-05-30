AUTOMAKE_OPTIONS = -Wno-override

if DEBUG
    AM_CFLAGS = -g -O0 -DDEBUG=1
    AM_CXXFLAGS = -g -O0 -DDEBUG=1
else
    AM_CFLAGS = -O3
    AM_CXXFLAGS = -O3
endif

if HAVE_EXECINFO_H
    AM_CFLAGS += -DHAVE_EXECINFO_H=1
    AM_CXXFLAGS += -DHAVE_EXECINFO_H=1
endif

if IN_GIT
    AM_CFLAGS += -DGIT_HEAD_HASH=\"$(git_HEAD_hash)\"
    AM_CXXFLAGS += -DGIT_HEAD_HASH=\"$(git_HEAD_hash)\"
endif

if USE_ALLEGRO5
    AM_CFLAGS += -DUSE_ALLEGRO5=1
    AM_CXXFLAGS += -DUSE_ALLEGRO5=1
else
if USE_ALLEGRO4
    AM_CFLAGS += -DUSE_ALLEGRO4=1
    AM_CXXFLAGS += -DUSE_ALLEGRO4=1
endif
endif

if DARWIN
    AM_CFLAGS += -DDARWIN=1
    AM_CXXFLAGS += -DDARWIN=1
endif

headoverheels_CPPFLAGS =  -Iactivities -Ibehaviors -Igui -Iguiactions
headoverheels_CPPFLAGS += -DBinDirFromConfigure=\"$(bindir)\" -DDataDirFromConfigure=\"$(datadir)\"
headoverheels_CPPFLAGS += $(libpng_HEADERS) $(ogg_HEADERS) $(vorbis_HEADERS) $(tinyxml2_HEADERS) $(allegro_HEADERS)
headoverheels_CPPFLAGS += $(AM_CPPFLAGS)

headoverheels_CFLAGS = -Wall $(AM_CFLAGS)
headoverheels_CXXFLAGS = -Wall $(AM_CXXFLAGS)

AM_LDFLAGS = -lpthread $(libpng_LIBS) $(ogg_LIBS) $(vorbis_LIBS) $(tinyxml2_LIBS) $(allegro_LIBS)

bin_PROGRAMS = headoverheels

headoverheels_SOURCES = main.cpp \
			tribool.hpp \
			sleep.cpp \
			sleep.hpp \
			util.hpp \
			pointers.cpp \
			pointers.hpp \
			ospaths.cpp \
			ospaths.hpp \
			version.hpp \
			MayNotBePossible.hpp \
			NoSuchThingException.hpp \
			NoSuchPictureException.hpp \
			NoSuchSlideException.hpp \
			UnicodeUtilities.hpp \
			WrappersAllegro.cpp \
			WrappersAllegro.hpp \
			Way.cpp \
			Way.hpp \
			Motion2D.hpp \
			Motion3D.hpp \
			Color.cpp \
			Color.hpp \
			FlickeringColor.cpp \
			FlickeringColor.hpp \
			Picture.cpp \
			Picture.hpp \
			NamedPicture.hpp \
			PoolOfPictures.cpp \
			PoolOfPictures.hpp \
			Drawable.hpp \
			Mediated.hpp \
			Shady.hpp \
			Camera.cpp \
			Camera.hpp \
			FloorTile.cpp \
			FloorTile.hpp \
			WallPiece.cpp \
			WallPiece.hpp \
			Door.cpp \
			Door.hpp \
			AbstractItem.cpp \
			AbstractItem.hpp \
			DescribedItem.cpp \
			DescribedItem.hpp \
			GridItem.cpp \
			GridItem.hpp \
			FreeItem.cpp \
			FreeItem.hpp \
			AvatarItem.cpp \
			AvatarItem.hpp \
			ShadowCaster.cpp \
			ShadowCaster.hpp \
			Masker.cpp \
			Masker.hpp \
			Mediator.cpp \
			Mediator.hpp \
			Room.cpp \
			Room.hpp \
			RoomMaker.cpp \
			RoomMaker.hpp \
			GameManager.cpp \
			GameManager.hpp \
			GameSaverAndLoader.cpp \
			GameSaverAndLoader.hpp \
			GameInfo.cpp \
			GameInfo.hpp \
			GamePreferences.cpp \
			GamePreferences.hpp \
			InputManager.cpp \
			InputManager.hpp \
			Miniature.cpp \
			Miniature.hpp \
			NamedMiniatures.hpp \
			Isomot.cpp \
			Isomot.hpp \
			DescriptionOfItem.cpp \
			DescriptionOfItem.hpp \
			DescriptionOfDoor.cpp \
			DescriptionOfDoor.hpp \
			ItemDescriptions.cpp \
			ItemDescriptions.hpp \
			GameMap.cpp \
			GameMap.hpp \
			ConnectedRooms.cpp \
			ConnectedRooms.hpp \
			BonusManager.cpp \
			BonusManager.hpp \
			SoundManager.cpp \
			SoundManager.hpp \
			Timer.hpp \
			Timer.cpp \
			TheKeyMoments.hpp \
			activities/Activity.hpp \
			activities/ActivityToString.hpp \
			activities/PropagateActivity.cpp \
			activities/PropagateActivity.hpp \
			activities/Displacing.cpp \
			activities/Displacing.hpp \
			activities/Falling.cpp \
			activities/Falling.hpp \
			activities/Jumping.cpp \
			activities/Jumping.hpp \
			activities/Moving.cpp \
			activities/Moving.hpp \
			behaviors/Behavior.hpp \
			behaviors/CreatorOfBehaviors.cpp \
			behaviors/CreatorOfBehaviors.hpp \
			behaviors/Bonus.cpp \
			behaviors/Bonus.hpp \
			behaviors/Conveyor.cpp \
			behaviors/Conveyor.hpp \
			behaviors/Detector.cpp \
			behaviors/Detector.hpp \
			behaviors/Doughnut.cpp \
			behaviors/Doughnut.hpp \
			behaviors/Driven.cpp \
			behaviors/Driven.hpp \
			behaviors/Elevator.cpp \
			behaviors/Elevator.hpp \
			behaviors/FinalBall.cpp \
			behaviors/FinalBall.hpp \
			behaviors/Hunter.cpp \
			behaviors/Hunter.hpp \
			behaviors/Impel.cpp \
			behaviors/Impel.hpp \
			behaviors/Mobile.cpp \
			behaviors/Mobile.hpp \
			behaviors/Patrol.cpp \
			behaviors/Patrol.hpp \
			behaviors/RemoteControl.cpp \
			behaviors/RemoteControl.hpp \
			behaviors/Sink.cpp \
			behaviors/Sink.hpp \
			behaviors/SpringStool.cpp \
			behaviors/SpringStool.hpp \
			behaviors/Switch.cpp \
			behaviors/Switch.hpp \
			behaviors/Teleport.cpp \
			behaviors/Teleport.hpp \
			behaviors/ThereAndBack.cpp \
			behaviors/ThereAndBack.hpp \
			behaviors/Turn.cpp \
			behaviors/Turn.hpp \
			behaviors/Volatile.cpp \
			behaviors/Volatile.hpp \
			behaviors/PlayerControlled.cpp \
			behaviors/PlayerControlled.hpp \
			behaviors/CharacterHead.cpp \
			behaviors/CharacterHead.hpp \
			behaviors/CharacterHeels.cpp \
			behaviors/CharacterHeels.hpp \
			behaviors/CharacterHeadAndHeels.cpp \
			behaviors/CharacterHeadAndHeels.hpp \
			gui/Font.cpp \
			gui/Font.hpp \
			gui/GuiManager.cpp \
			gui/GuiManager.hpp \
			gui/KeyHandler.hpp \
			gui/Widget.hpp \
			gui/PictureWidget.hpp \
			gui/AnimatedPictureWidget.cpp \
			gui/AnimatedPictureWidget.hpp \
			gui/Label.cpp \
			gui/Label.hpp \
			gui/ColorCyclingLabel.cpp \
			gui/ColorCyclingLabel.hpp \
			gui/LanguageText.hpp \
			gui/LanguageStrings.cpp \
			gui/LanguageStrings.hpp \
			gui/Menu.cpp \
			gui/Menu.hpp \
			gui/MenuWithValues.cpp \
			gui/MenuWithValues.hpp \
			gui/MenuWithTwoColumns.cpp \
			gui/MenuWithTwoColumns.hpp \
			gui/TheMainMenu.cpp \
			gui/TheMainMenu.hpp \
			gui/TheListOfSavedGames.cpp \
			gui/TheListOfSavedGames.hpp \
			gui/Slide.cpp \
			gui/Slide.hpp \
			gui/SlideWithHeadAndHeels.cpp \
			gui/SlideWithHeadAndHeels.hpp \
			gui/TheMainMenuSlide.hpp \
			gui/TheListOfSavedGamesSlide.hpp \
			gui/TextField.cpp \
			gui/TextField.hpp \
			guiactions/Action.hpp \
			guiactions/ActionWithHandlingKeys.hpp \
			guiactions/AllCreatedActions.cpp \
			guiactions/AllCreatedActions.hpp \
			guiactions/PlaySound.hpp \
			guiactions/ChooseLanguage.cpp \
			guiactions/ChooseLanguage.hpp \
			guiactions/ContinueGame.cpp \
			guiactions/ContinueGame.hpp \
			guiactions/LoadGame.cpp \
			guiactions/LoadGame.hpp \
			guiactions/SaveGame.cpp \
			guiactions/SaveGame.hpp \
			guiactions/CreateAudioMenu.cpp \
			guiactions/CreateAudioMenu.hpp \
			guiactions/CreateVideoMenu.hpp \
			guiactions/CreateVideoMenu.cpp \
			guiactions/CreateGraphicsAreaSizeMenu.hpp \
			guiactions/CreateGraphicsAreaSizeMenu.cpp \
			guiactions/CreateMenuOfGraphicsSets.hpp \
			guiactions/CreateMenuOfGraphicsSets.cpp \
			guiactions/CreateGameOverSlide.cpp \
			guiactions/CreateGameOverSlide.hpp \
			guiactions/PresentTheListOfSavedGames.cpp \
			guiactions/PresentTheListOfSavedGames.hpp \
			guiactions/CreateKeysMenu.cpp \
			guiactions/CreateKeysMenu.hpp \
			guiactions/RedefineKey.cpp \
			guiactions/RedefineKey.hpp \
			guiactions/CreateLanguageMenu.cpp \
			guiactions/CreateLanguageMenu.hpp \
			guiactions/PresentTheMainMenu.cpp \
			guiactions/PresentTheMainMenu.hpp \
			guiactions/CreateOptionsMenu.cpp \
			guiactions/CreateOptionsMenu.hpp \
			guiactions/ShowSlideWithPlanets.cpp \
			guiactions/ShowSlideWithPlanets.hpp \
			guiactions/ShowCongratulations.cpp \
			guiactions/ShowCongratulations.hpp \
			guiactions/ShowAuthors.cpp \
			guiactions/ShowAuthors.hpp \
			guiactions/Quit.cpp \
			guiactions/Quit.hpp

if USE_ALLEGRO5
headoverheels_SOURCES += algif5/algif.c \
			algif5/gif.c \
			algif5/lzw.c \
			algif5/bitmap.c
else
if USE_ALLEGRO4
headoverheels_SOURCES += loadpng/loadpng.c \
			loadpng/savepng.c \
			loadpng/regpng.c \
			alogg/alogg.c \
			alogg/aloggcfg.h \
			alogg/alogg.h \
			alogg/aloggint.h \
			alogg/aloggpth.c \
			alogg/aloggpth.h \
			algif/algif.c \
			algif/gif.c \
			algif/lzw.c
endif
endif
