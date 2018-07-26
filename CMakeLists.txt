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

project(hello_world VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

add_executable(hello_world ${PROJECT_SOURCE_DIR}/hello_world/main.c)

set_target_properties(hello_world PROPERTIES
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

install(TARGETS hello_world RUNTIME DESTINATION bin COMPONENT dns_proxy)
