cmake_minimum_required(VERSION 3.20)
project(VulkanRT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Output directories ────────────────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# ── Custom dependency paths ───────────────────────────────────────────
set(VULKAN_SDK_ROOT "C:/VulkanSDK/1.4.321.1" CACHE PATH "Vulkan SDK root")
set(GL_LIB_ROOT    "C:/GL_LIB"              CACHE PATH "Third-party libs root")

# Tell CMake where to look for package configs
list(APPEND CMAKE_PREFIX_PATH
    "${VULKAN_SDK_ROOT}"
    "${GL_LIB_ROOT}"
)

# ── Vulkan ────────────────────────────────────────────────────────────
find_package(Vulkan REQUIRED)

# ── GLFW (manual: no CMake config in GL_LIB) ─────────────────────────
add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
    IMPORTED_LOCATION             "${GL_LIB_ROOT}/lib/glfw3.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${GL_LIB_ROOT}/include"
)

# ── GLM (header-only) ────────────────────────────────────────────────
add_library(glm_header_only INTERFACE)
target_include_directories(glm_header_only INTERFACE "${GL_LIB_ROOT}/include")

# ── SOIL2 (manual) ───────────────────────────────────────────────────
add_library(soil2 STATIC IMPORTED)
# Only debug lib available; map all configurations to it
set_target_properties(soil2 PROPERTIES
    IMPORTED_LOCATION                  "${GL_LIB_ROOT}/lib/soil2-debug.lib"
    IMPORTED_LOCATION_DEBUG            "${GL_LIB_ROOT}/lib/soil2-debug.lib"
    IMPORTED_LOCATION_RELEASE          "${GL_LIB_ROOT}/lib/soil2-debug.lib"
    IMPORTED_LOCATION_MINSIZEREL       "${GL_LIB_ROOT}/lib/soil2-debug.lib"
    IMPORTED_LOCATION_RELWITHDEBINFO   "${GL_LIB_ROOT}/lib/soil2-debug.lib"
    INTERFACE_INCLUDE_DIRECTORIES      "${GL_LIB_ROOT}/include"
)

# ── Source files ──────────────────────────────────────────────────────
set(SOURCES
    src/main.cpp
    src/Window.cpp
    src/Console.cpp
    src/StbImage.cpp
)

set(HEADERS
    src/Vulkan.hpp
    src/Exception.hpp
    src/Glm.hpp
    src/WindowConfig.hpp
    src/Window.hpp
    src/Console.hpp
    src/StbImage.hpp
)

# ── Executable ────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# ── Link libraries ────────────────────────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
    glfw3
    glm_header_only
    soil2
)

# ── Compiler warnings ─────────────────────────────────────────────────
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

# ── Windows specific settings ─────────────────────────────────────────
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        WIN32_LEAN_AND_MEAN
    )

    # Suppress LNK4098: soil2-debug.lib uses debug CRT which conflicts
    # with the Release CRT; harmless for our usage
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/NODEFAULTLIB:LIBCMT>
        $<$<CONFIG:Release>:/NODEFAULTLIB:MSVCRTD>
    )
endif()
