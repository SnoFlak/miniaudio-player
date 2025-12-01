cmake_minimum_required(VERSION 3.10)

# 1. Project Setup
project(miniaudio-player VERSION 1.0)

# 2. Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- NEW POSITION FOR ADD_EXECUTABLE ---
# 3. Add Source Files and Create Executable (MUST come before any target_... commands)
add_executable(miniaudio-player
    src/main.cpp
    src/glad.c 
)

# 4. Add Include Directories (Now it knows "miniaudio-player" exists)
target_include_directories(miniaudio-player PUBLIC
    ${CMAKE_SOURCE_DIR}/include # For GLAD, GLFW headers
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