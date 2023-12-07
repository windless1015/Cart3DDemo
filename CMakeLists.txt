cmake_minimum_required(VERSION 3.5)

project(Cart3DDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Cart3D_DIR "${CMAKE_SOURCE_DIR}/lib/Cart3D/bin")
set(OpenMesh_DIR "${CMAKE_SOURCE_DIR}/lib/OpenMesh/share/OpenMesh/cmake")

message(${Cart3D_DIR})

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(OpenGL)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Cart3D REQUIRED)
find_package(OpenMesh)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        foxopenGLwidget.h
        foxopenGLwidget.cpp

        foxmeshmodel.h
        foxmeshmodel.cpp
)



add_executable(Cart3DDemo ${PROJECT_SOURCES})


target_link_libraries(Cart3DDemo PRIVATE ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(Cart3DDemo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Cart3DDemo PRIVATE ${CART3D_MODELS_DLL})
target_link_libraries(Cart3DDemo PRIVATE Qt5::OpenGL)
target_link_libraries(Cart3DDemo PRIVATE OpenMeshCore OpenMeshTools)




