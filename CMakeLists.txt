cmake_minimum_required(VERSION 3.2)
project(sketch_TrafficLight)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories("./intellij_files")

set(SOURCE_FILES
    intellij_files/Arduino.cpp
    intellij_files/Arduino.h
    intellij_files/main.cpp
    Sequencer.cpp
    Sequencer.h
    Callback.h
    Constants.h
    CrosswalkController.cpp
    CrosswalkController.h
    Light.cpp
    Light.h
    PedestrianTrafficLight.cpp
    PedestrianTrafficLight.h
    Scheduler.cpp
    Scheduler.h
    TrafficLightBase.h
    VehicleTrafficLight.cpp
    VehicleTrafficLight.h)

add_executable(sketch_TrafficLight ${SOURCE_FILES})

