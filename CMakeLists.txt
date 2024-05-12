cmake_minimum_required(VERSION 3.26)
project(TreeManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(TreeManager main.cpp
        App.cpp
        App.h
        header.h
        Label.h
        GraphWidget.cpp
        GraphWidget.h
        Trees/AVL.cpp
        Trees/AVL.h
        Trees/Treap.cpp
        Trees/Treap.h
        Trees/Splay.cpp
        Trees/Splay.h
        Trees/RBTree.cpp
        Trees/RBTree.h)
target_link_libraries(TreeManager
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

