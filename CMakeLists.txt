cmake_minimum_required(VERSION 3.16)

project(Ponder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# qt6 configs
set(CMAKE_PREFIX_PATH "C:/QtNew/6.12.0/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

# SQLite library
add_library(sqlite3 STATIC
    external/sqlite/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
    ${PROJECT_SOURCE_DIR}/external/sqlite
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/ui/mainwindow.ui
    src/db/database.cpp
    src/db/cardrepository.cpp
    src/services/cardservices.cpp
)

qt_add_executable(Ponder
    ${SOURCES}
)

target_include_directories(Ponder PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Ponder PRIVATE
    Qt6::Widgets
    sqlite3
)

set_target_properties(Ponder PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
