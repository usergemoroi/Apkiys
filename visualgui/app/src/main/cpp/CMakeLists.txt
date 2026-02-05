cmake_minimum_required(VERSION 3.10)
project(visualgui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -fvisibility=hidden -fno-rtti")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL")

# Find libraries
find_library(log-lib log)
find_library(android-lib android)
find_library(egl-lib EGL)
find_library(glesv3-lib GLESv3)

# Source files
set(SOURCES
    main.cpp
    GUI.cpp
    ESP.cpp
    Player.cpp
    Game.cpp
    Drawing.cpp
    Config.cpp
    Aimbot.cpp
)

# ImGui sources
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp
    imgui_impl_opengl3.cpp
    imgui_impl_android.cpp
)

# Create shared library
add_library(visualgui SHARED ${SOURCES} ${IMGUI_SOURCES})

# Include directories
target_include_directories(visualgui PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link libraries
target_link_libraries(visualgui
    ${log-lib}
    ${android-lib}
    ${egl-lib}
    ${glesv3-lib}
)

# Strip symbols in release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET visualgui POST_BUILD
        COMMAND ${CMAKE_STRIP} --strip-unneeded $<TARGET_FILE:visualgui>
    )
endif()
