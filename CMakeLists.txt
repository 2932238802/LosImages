cmake_minimum_required(VERSION 3.21)

project(LosImages VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(LosImages
    src/main.cpp

    src/core/LosRouter/LosRouter.h
    src/core/LosRouter/LosRouter.cc
    src/core/LosMoveWorker/LosMoveWorker.h
    src/core/LosMoveWorker/LosMoveWorker.cc

    src/common/str/LosMoveWorker_str.h
    src/common/num/LosMainWindow_num.h
    src/common/enum/LosMoveWorker_enum.h

    src/common/util/LosPathUtil/LosPathUtil.h

    src/view/LosMainWindow/LosMainWindow.h
    src/view/LosMainWindow/LosMainWindow.cc
    src/view/LosMainWindow/LosMainWindow.ui
    src/view/style/LosMainWindow_style.h
)

target_include_directories(LosImages PRIVATE src)

target_link_libraries(LosImages PRIVATE Qt6::Widgets)

set_target_properties(LosImages PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build/bin"
)

if(WIN32)
    set_target_properties(LosImages PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
