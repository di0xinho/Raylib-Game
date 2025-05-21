cmake_minimum_required(VERSION 3.24...3.30)
project(raylib-game-template)

include(FetchContent)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

add_executable(main src/main.cpp "src/StateMachine.cpp"  "src/MenuState.cpp" "src/GameState.cpp" "src/PauseState.cpp" "src/AssetManager.cpp" "src/InputManager.cpp"  "src/Player.cpp" "src/Enemy.cpp"  "src/Coin.cpp" "src/GameOverState.cpp" "src/HUD.cpp" "src/Animation.cpp"   "src/Trophy.cpp"  "src/MoveLeftCommand.cpp" "src/MoveRightCommand.cpp" "src/JumpCommand.cpp" "src/Weapon.cpp" "src/AttackCommand.cpp" "src/StopMovingCommand.cpp" "src/SoundManager.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE raylib)
target_include_directories(main PRIVATE include)


