cmake_minimum_required(VERSION 3.12)
project(boilerplate_imgui_app)
set(CMAKE_CXX_STANDARD 17)


##########################################################
# Prepare hello_imgui during configure time
##########################################################
# Download hello_imgui
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    hello_imgui
    GIT_REPOSITORY https://github.com/pthom/hello_imgui.git
    GIT_PROGRESS TRUE
    # Enter the desired git tag below
    # GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(hello_imgui)
# Make cmake function `hello_imgui_add_app` available
list(APPEND CMAKE_MODULE_PATH ${HELLOIMGUI_CMAKE_PATH})
include(hello_imgui_add_app)


##########################################################
# Build your app
##########################################################
# Call hello_imgui_add_app
hello_imgui_add_app(app main.cpp)