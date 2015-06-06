cmake_minimum_required(VERSION 3.2)
project(sketch_TrafficLight)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories("./external_src")
include_directories("./sketch_TrafficLight")


set(EXT_SOURCE_FILES
    external_src/Arduino.cpp
    external_src/Arduino.h
    external_src/main.cpp)

set(SOURCE_FILES
    sketch_TrafficLight/Sequencer.cpp
    sketch_TrafficLight/Sequencer.h
    sketch_TrafficLight/Callback.h
    sketch_TrafficLight/Constants.h
    sketch_TrafficLight/CrosswalkController.cpp
    sketch_TrafficLight/CrosswalkController.h
    sketch_TrafficLight/Light.cpp
    sketch_TrafficLight/Light.h
    sketch_TrafficLight/PedestrianTrafficLight.cpp
    sketch_TrafficLight/PedestrianTrafficLight.h
    sketch_TrafficLight/Scheduler.cpp
    sketch_TrafficLight/Scheduler.h
    sketch_TrafficLight/TrafficLightBase.h
    sketch_TrafficLight/VehicleTrafficLight.cpp
    sketch_TrafficLight/VehicleTrafficLight.h)

add_executable(sketch_TrafficLight ${EXT_SOURCE_FILES} ${SOURCE_FILES})

