cmake_minimum_required(VERSION 3.5)

project(Cart3DDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Cart3D_DIR "${CMAKE_SOURCE_DIR}/lib/Cart3D/bin")
set(OpenMesh_DIR "${CMAKE_SOURCE_DIR}/lib/OpenMesh/share/OpenMesh/cmake")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
message(" Cart3D_DIR: ${Cart3D_DIR}")
message("CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(OpenGL)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Cart3D )
find_package(OpenMesh)



set(PROJECT_SOURCES
        "main.cpp"
        "mainwindow.cpp"
        "mainwindow.h"
        "mainwindow.ui"

        "view/foxopenGLwidget.h"
        "view/foxopenGLwidget.cpp"

        "model/foxmeshmodel.h"
        "model/foxmeshmodel.cpp"
	    "model/foxmesh.h"	
	    "model/foxmesh.cpp"

        "rendering/foxcamera.h"
        "rendering/foxcamera.cpp"
        "rendering/foxlighting.h"
        "rendering/foxlighting.cpp"
        "rendering/foxshaderprogram.h" 
        "rendering/foxshaderprogram.cpp"

        "geometry/foxspheresource.h"
        "geometry/foxspheresource.cpp"
)



add_executable(Cart3DDemo ${PROJECT_SOURCES})


target_link_libraries(Cart3DDemo PRIVATE ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(Cart3DDemo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Cart3DDemo PRIVATE ${CART3D_MODELS_DLL})
target_link_libraries(Cart3DDemo PRIVATE Qt5::OpenGL)
target_link_libraries(Cart3DDemo PRIVATE OpenMeshCore OpenMeshTools)

if(MSVC)
    file(GLOB CAR3D_DLL ${Cart3D_DIR}/*.dll)

    add_custom_command(TARGET Cart3DDemo
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CAR3D_DLL}
            $<TARGET_FILE_DIR:Cart3DDemo>)
       
    # copy res to release folder
    add_custom_command(TARGET Cart3DDemo
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E  copy_directory  
            "${CMAKE_CURRENT_SOURCE_DIR}/res" 
		    $<TARGET_FILE_DIR:Cart3DDemo>/res)

    # copy res to build folder
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory 
  			    ${CMAKE_CURRENT_SOURCE_DIR}/res 
			    ${CMAKE_CURRENT_SOURCE_DIR}/build/res)

    # copy caseData folder to release folder
    add_custom_command(TARGET Cart3DDemo
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E  copy_directory  
            "${CMAKE_CURRENT_SOURCE_DIR}/caseData" 
		    $<TARGET_FILE_DIR:Cart3DDemo>/caseData)

    # copy caseData folder to build folder
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory 
  			    ${CMAKE_CURRENT_SOURCE_DIR}/caseData 
			    ${CMAKE_CURRENT_SOURCE_DIR}/build/caseData)

endif()

