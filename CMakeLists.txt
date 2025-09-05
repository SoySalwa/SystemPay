cmake_minimum_required(VERSION 3.16)

project(system VERSION 0.1.0 LANGUAGES CXX)

set(VERSION_SUFFIX "Alpha")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

# Recoge automáticamente todos los .cpp/.h/.ui/.qrc bajo src/
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    src/main.cpp

    # UI
    src/ui/app/mainwindow.cc src/ui/app/mainwindow.h
    src/utils/DonutWidget.cc src/utils/DonutWidget.h
    src/ui/app/settings/Settings.cc src/ui/app/settings/Settings.h
    src/ui/app/settings/ThemeManager.h 
    # Eventos
    #src/events/eventhandlers.cpp src/events/eventhandlers.h
    #src/events/mouseevent.cpp src/events/mouseevent.h
    # Styles
    src/styles/ButtonStyle.h
    src/styles/WidgetStyle.h
    # Database
   # src/database/MongoConnection.cpp src/database/MongoConnection.h

    # Utils
    src/utils/systembuttons.cpp src/utils/systembuttons.h
  #  src/styles/systemcolors.cpp src/styles/systemcolors.h
  #  src/utils/QLMessage.h
  #  src/utils/Validated.h
   # src/utils/GenerateMatStudent.h
   # src/utils/app/Version.h
   # src/utils/app/settingsapp.cpp src/utils/app/settingsapp.h

    # Recursos
    assets/resources.qrc
)

include_directories( ${BSONCXX_INCLUDE_DIRS} ${MONGOCXX_INCLUDE_DIRS} "/usr/local/include/mongocxx/v_noabi" "/usr/local/include/bsoncxx/v_noabi" )
# Executable definition
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(system
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(system SHARED ${PROJECT_SOURCES})
    else()
        add_executable(system ${PROJECT_SOURCES})
    endif()
endif()

# Includes absolutos
target_include_directories(system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/app/settings
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/students
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/window
    ${CMAKE_CURRENT_SOURCE_DIR}/src/events
    ${CMAKE_CURRENT_SOURCE_DIR}/src/styles
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/app
    ${BSONCXX_INCLUDE_DIRS}
    ${MONGOCXX_INCLUDE_DIRS}
    /usr/local/include/mongocxx/v_noabi
    /usr/local/include/bsoncxx/v_noabi
)



# Version defines
target_compile_definitions(system PRIVATE
    APP_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    APP_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    APP_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    APP_VERSION_SUFFIX="${VERSION_SUFFIX}"
)

# Link libraries
target_link_libraries(system PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport
    "/usr/local/lib64/libmongocxx.so" "/usr/local/lib64/libbsoncxx.so"
    "/usr/local/lib64/libmongoc-1.0.so.0" "/usr/local/lib64/libbson-1.0.so.0"
)

# macOS/iOS properties
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.system)
endif()
set_target_properties(system PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install
include(GNUInstallDirs)
install(TARGETS system
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(system)
endif()
