cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD_MAJOR 1)
    set(VERSION_BUILD_MINOR 0)
else()
    set(VERSION_BUILD 1)
    set(VERSION_BUILD_MAJOR 1)
    set(VERSION_BUILD_MINOR 0)
endif()

project(chat_app VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
add_definitions(${Boost_INCLUDE_DIRS} ${Boost_LIBRARIES})

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)
find_package(Boost COMPONENTS stacktrace_backtrace stacktrace_basic stacktrace_basic stacktrace_addr2line REQUIRED)

qt5_add_resources(RESOURCES qml.qrc)

add_executable(chat main.cpp gui.cpp test.cpp gui.h test.h defines.h ${RESOURCES})

target_link_libraries(chat Qt5::Core Qt5::Qml Qt5::Quick)
target_link_libraries(chat -ldl -lbreakpad -lbreakpad_client -lpthread)

target_include_directories(chat PRIVATE /usr/local/include/breakpad/)

install(TARGETS chat RUNTIME DESTINATION bin COMPONENT chat_app)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
