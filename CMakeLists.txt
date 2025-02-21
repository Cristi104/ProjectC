cmake_minimum_required(VERSION 3.27)
project(ProjectC)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib 5.0 QUIET)

add_library(gamelib
        src/Resources.cpp
        src/Button.cpp
        src/Slider.cpp
        src/TextBox.cpp
        src/CheckBox.cpp
        src/Panel.cpp
        src/Settings.cpp
        src/Text.cpp
        src/Tile.cpp
        src/Map.cpp
        src/Camera.cpp
        include/Button.h
        include/UIComponent.h
        include/Resources.h
        include/Slider.h
        include/TextBox.h
        include/CheckBox.h
        include/Panel.h
        include/Text.h
        include/Map.h
        include/Tile.h
        src/PerlinNoiseGenerator.cpp
        include/PerlinNoiseGenerator.h
        include/Settings.h
        src/Floor.cpp
        include/Floor.h
        src/Serialiazation.cpp
        include/Serialiazation.h
)

add_executable(ProjectC main.cpp)

if (NOT raylib_FOUND)

    include(FetchContent)

    set(BUILD_SHARED_LIBS ON)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip
    )

    FetchContent_MakeAvailable(raylib)

    # TODO: fix copying here
    #    if (WIN32)
    #        add_custom_command(TARGET ProjectC POST_BUILD
    #                COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #                "${CMAKE_CURRENT_BINARY_DIR}/_deps/raylib-build/raylib/raylib.dll"
    #                $<TARGET_FILE_DIR:ProjectC>)
    #    elseif (APPLE)
    #        add_custom_command(TARGET ProjectC POST_BUILD
    #                COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #                "${CMAKE_CURRENT_BINARY_DIR}/_deps/raylib-build/raylib/librarylib.dylib"
    #                $<TARGET_FILE_DIR:ProjectC>)
    #    elseif (UNIX AND NOT APPLE)
    #        add_custom_command(TARGET ProjectC POST_BUILD
    #                COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #                "${CMAKE_CURRENT_BINARY_DIR}/_deps/raylib-build/raylib/librarylib.so"
    #                $<TARGET_FILE_DIR:ProjectC>)
    #    endif ()

endif ()

target_include_directories(gamelib
        PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}"
)
target_link_libraries(gamelib
        PUBLIC
        raylib
)

include(GenerateExportHeader)
GENERATE_EXPORT_HEADER(gamelib
        BASE_NAME gamelib
        EXPORT_MACRO_NAME GAME_EXPORTS
        EXPORT_FILE_NAME Game_exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)

target_link_libraries(ProjectC
        PUBLIC
        raylib
        gamelib
)
