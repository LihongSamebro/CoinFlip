cmake_minimum_required(VERSION 3.16)

project(CoinFlip2)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#音乐播放包
 find_package(Qt6 REQUIRED COMPONENTS Multimedia)




set(PROJECT_SOURCES
        chooselevelscene.h chooselevelscene.cpp
        dataconfig.h dataconfig.cpp
        mainscene.h mainscene.cpp
        mycoin.h mycoin.cpp
        mypushbutton.h mypushbutton.cpp
        playscene.h playscene.cpp
        main.cpp
        mainscene.ui
        res.qrc
)


add_executable(CoinFlip2 ${PROJECT_SOURCES})

target_link_libraries(CoinFlip2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Multimedia)




