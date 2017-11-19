cmake_minimum_required(VERSION 3.6)
project(EntityxBox2D)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(SOURCE_COMPONENTS
        src/components/body.h
        src/components/body.cpp
        src/components/collideable.h
        src/components/collideable.cpp
        src/components/renderable.h
        src/components/renderable.cpp
        src/components/shapes.h
        src/components/shapes.cpp
        src/components/mass.cpp src/components/mass.h)
set(SOURCE_EVENTS
        src/events/collision_event.h
        src/events/collision_event.cpp
        src/events/EntitySpawnedEvent.h
        src/events/EntitySpawnedEvent.cpp
)
set(SOURCE_SYSTEMS
        src/systems/opacity_system.h
        src/systems/opacity_system.cpp
        src/systems/render_system.h
        src/systems/render_system.cpp
        src/systems/spawn_system.h
        src/systems/spawn_system.cpp
        src/systems/physics_system.h
        src/systems/physics_system.cpp
        src/systems/random_motion_system.h
        src/systems/random_motion_system.cpp
        src/systems/info_draw_system.h
        src/systems/info_draw_system.cpp
        src/systems/gravity_system.h src/systems/gravity_system.cpp)

add_executable(EntityxExample
        ${SOURCE_COMPONENTS}
        ${SOURCE_EVENTS}
        ${SOURCE_SYSTEMS}
        src/util.h
        src/util.cpp
        src/common.h
        src/main.cpp)


# чтобы писать инклуды относительно папки src
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# где лежат модули поиска
set(ENTITYX_CMAKE_MODULE_LOCATION "/home/meloman/bin/entityx/cmake")
set(SFML_CMAKE_MODULE_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

list(APPEND CMAKE_MODULE_PATH ${ENTITYX_CMAKE_MODULE_LOCATION})
list(APPEND CMAKE_MODULE_PATH ${SFML_CMAKE_MODULE_LOCATION})

find_package(EntityX REQUIRED)
find_package(Box2D REQUIRED)
find_package(SFML 2 REQUIRED system window graphics)


include_directories(
        ${ENTITYX_INCLUDE_DIRS}
        ${Box2D_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIR}
)

target_link_libraries(EntityxExample
        ${ENTITYX_LIBRARIES}
        ${BOX2D_LIBRARY}
        ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
)
