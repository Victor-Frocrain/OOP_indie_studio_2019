cmake_minimum_required(VERSION 3.11)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
project(OOP_indie_studio_2019)

set(CMAKE_MODULE_PATH modules)

include(${CMAKE_MODULE_PATH}/FindIrrlicht.cmake)

#include(WINDOWS/SFML/cmake/Modules/FindEGL.cmake)
#include(WINDOWS/SFML/cmake/Modules/FindFLAC.cmake)
#include(WINDOWS/SFML/cmake/Modules/FindFreetype.cmake)
#include(WINDOWS/SFML/cmake/Modules/FindGLES.cmake)
#include(WINDOWS/SFML/cmake/Modules/FindUDev.cmake)
#include(WINDOWS/SFML/cmake/Modules/FindVorbis.cmake)

include_directories(${CMAKE_MODULE_PATH}/)
include_directories(include/)

set(SRC
  src/core/main.cpp
  src/scenes/AScene.cpp
  src/scenes/AScenePlayerControls.cpp
  src/scenes/Menu.cpp
  src/scenes/MainMenu.cpp
  src/scenes/Scenes.cpp
  src/scenes/Game.cpp
  src/scenes/Options.cpp
  src/scenes/Pause.cpp
  src/scenes/MenuPlayer.cpp
  src/scenes/ControlMenu.cpp
  src/finder/AFinder.cpp
  src/finder/Finder.cpp
  src/tools/Tools.cpp
  src/entity/character/player/APlayerController.cpp
  src/utils/FileReader.cpp
  src/scenes/EventListener.cpp
  src/entity/AEntity.cpp
  src/entity/character/ACharacter.cpp
  src/entity/character/player/Player.cpp
  src/entity/power_up/APowerUp.cpp
  src/entity/power_up/PowerUp.cpp
  src/entity/wall/AWall.cpp
  src/entity/wall/Wall.cpp
  src/entity/bomb/Bomb.cpp
  src/map/MapGenerator.cpp
  src/utils/IndieStudio.cpp
  src/map/Entities.cpp
  src/entity/character/AI/AI.cpp
  src/map/Logger.cpp
  src/entity/character/player/Control.cpp
  src/entity/fire/Fire.cpp
  src/scenes/WinMenu.cpp
  src/scenes/GameOver.cpp
  )

if (MSVC)
    include_directories(irrlicht)
else (MSVC)
    set(CMAKE_CXX_FLAGS "-lIrrlicht -lGL -lGLU -lsfml-audio")
endif (MSVC)

add_executable(bomberman ${SRC})

if (MSVC)
    target_link_libraries(bomberman "modules/Irrlicht" "WINDOWS/SFML/sfml-audio-d")
    add_custom_command(TARGET bomberman POST_BUILD COMMAND cmd /c "start ${CMAKE_SOURCE_DIR}/binConfiguration.bat")
else (MSVC)
endif (MSVC)
