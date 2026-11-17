cmake_minimum_required(VERSION 3.16)

project(ImGuiCalculator LANGUAGES CXX)

# ---- Стандарт C++17 ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ---- Автоматическое скачивание GLFW ----
# Статическая линковка библиотек (нужно задать ДО добавления подпроекта)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS   OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)

# ---- Автоматическое скачивание Dear ImGui (с бэкендами GLFW + OpenGL3) ----
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.5-docking
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glfw imgui)

# ---- Явно собираем нужные файлы ImGui в статическую библиотеку ----
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# ---- Само приложение ----
add_executable(calculator main.cpp)
target_link_libraries(calculator PRIVATE imgui)

# ---- Статическая линковка рантайма GCC под Windows (MinGW / Code::Blocks) ----
# Чтобы готовый .exe запускался автономно, без поиска libgcc/libstdc++ DLL.
if(WIN32 AND MINGW)
    target_link_options(calculator PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
    )
    # GUI-приложение: при запуске не открывается консольное окно
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_options(calculator PRIVATE -mwindows)
    endif()
endif()
