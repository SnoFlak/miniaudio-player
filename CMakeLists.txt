cmake_minimum_required(VERSION 3.10)

# 1. Project Setup
project(miniaudio-player VERSION 1.0)

# 2. Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_impl_glfw.cpp
    external/imgui/imgui_impl_opengl3.cpp
)

# --- NEW POSITION FOR ADD_EXECUTABLE ---
# 3. Add Source Files and Create Executable (MUST come before any target_... commands)
add_executable(miniaudio-player
    src/main.cpp
    src/glad.c
    src/ui.cpp
    src/visualizer_window.cpp
    src/directory_window.cpp
    src/control_window.cpp
    src/playback_manager.cpp
    ${IMGUI_SOURCES} 
)

# 4. Add Include Directories (Now it knows "miniaudio-player" exists)
target_include_directories(miniaudio-player PUBLIC
    ${CMAKE_SOURCE_DIR}/include # For GLAD, GLFW headers
    ${CMAKE_SOURCE_DIR}/external/imgui
)
# -------------------------------------

# 5. Find Dependencies (This can stay here)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 6. Link Libraries
target_link_libraries(miniaudio-player
    OpenGL::GL
    glfw
    ${GLFW_LIBRARIES}
)