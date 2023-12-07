# 这是Cart3D的配置文件
# 实现了find_package的功能
# 使用时只需要在CMakeLists.txt中添加:
#     find_package(Cart3D)
#     .....
#     target_link_libraries(MY_TARGET_NAME PRIVATE ${CART3D_MODELS_DLL})
#     

cmake_minimum_required(VERSION 3.5)

set(CART3D_PATHS 
    "${CMAKE_SOURCE_DIR}/3rdlib/Cart3D"
    "${CMAKE_SOURCE_DIR}/../Cart3D"
)

# 查找头文件路径
find_path(CART3D_CORE_INCLUDE_DIR include/Cart3DCore PATHS ${CART3D_PATHS}/include)

# 搜索动态库文件
find_library(CART3D_CORE_LIB NAMES common.lib PATHS ${CART3D_CORE_INCLUDE_DIR} PATH_SUFFIXES lib)
# 获取这个动态库的父目录路径
get_filename_component(_CART3D_LIB_PATH_ ${CART3D_CORE_LIB} PATH)

# 导出该路径 Cart3D/lib
set(CART3D_LIB_PATH  ${_CART3D_LIB_PATH_} CACHE PATH "This is the Cart3D library path")
#message(${CART3D_LIB_PATH})
# 获取静态库
file(GLOB MODEL_LIST "${CART3D_LIB_PATH}/*.lib")
set(CART3D_MODELS_LIB)
foreach(module_file ${MODEL_LIST})
    get_filename_component(module_name ${module_file} NAME_WE)
    list(APPEND CART3D_MODELS_LIB ${module_name})
endforeach(module_file ${MODEL_LIST})

# 导出静态库模块列表
#set(CART3D_MODELS_LIB ${CART3D_MODELS_LIB} CACHE PATH "This is th Cart3d library list")
link_directories(${CART3D_LIB_PATH})
get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(CART3D_CONFIG_PATH "${CMAKE_CURRENT_LIST_DIR}" REALPATH)
get_filename_component(CART3D_INSTALL_PATH "${CART3D_CONFIG_PATH}/../" REALPATH)

#message("CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")
#message("CART3D_CONFIG_PATH:${CART3D_CONFIG_PATH}")
#message("CART3D_INSTALL_PATH:${CART3D_INSTALL_PATH}")

# 设置头文件夹列表
set(CART3D_INCLUDE_DIRS " ")
set(CART3DCORE_INCLUDE_DIRS " ")
set(__CART3D_INCLUDE_DIRS "${CART3D_INSTALL_PATH}/include")
set(__CART3DCORE_INCLUDE_DIRS "${CART3D_INSTALL_PATH}/include/Cart3DCore")

#message("__CART3D_INCLUDE_DIRS:${__CART3D_INCLUDE_DIRS}")
#message("__CART3DCORE_INCLUDE_DIRS:${__CART3DCORE_INCLUDE_DIRS}")
# 获取include下的所有子文件夹
file(GLOB INCLUDE_DIRS "${__CART3D_INCLUDE_DIRS}/*/")
file(GLOB INCLUDE_CORE_DIRS "${__CART3DCORE_INCLUDE_DIRS}/*/")

foreach(dir IN LISTS INCLUDE_DIRS)
  if(IS_DIRECTORY ${dir})
    #message(\"INCLUDE_DIRS Directory: ${dir}\")
    list(APPEND CART3D_INCLUDE_DIRS ${dir})
  endif()
endforeach()

foreach(dir IN LISTS INCLUDE_CORE_DIRS)
  if(IS_DIRECTORY ${dir})
    #message(\"INCLUDE_CORE_DIRS Directory: ${dir}\")
    list(APPEND CART3DCORE_INCLUDE_DIRS ${dir})
  endif()
endforeach()

# 合并链表并导出头文件目录
# spdlog\include
set(SPDLOG_INCLUDE ${__CART3D_INCLUDE_DIRS}/spdlog/include)
list(APPEND CART3D_INCLUDE_DIRS ${SPDLOG_INCLUDE})
list(APPEND CART3D_INCLUDE_DIRS ${__CART3D_INCLUDE_DIRS})
list(APPEND CART3D_INCLUDE_DIRS ${CART3DCORE_INCLUDE_DIRS})
set(CART3D_INCLUDE_DIRS ${CART3D_INCLUDE_DIRS} CACHE PATH "This is th Cart3d haeder folder list")

# 加载头文件
include_directories(${CART3D_INCLUDE_DIRS})

# 获取动态库列表
file(GLOB MODEL_DLL_LIST "${CART3D_INSTALL_PATH}/bin/*.dll")
set(model_dll_list)
foreach(module_file ${MODEL_DLL_LIST})
    #message(${module_file})
    get_filename_component(module_name ${module_file} NAME_WE)
    list(APPEND model_dll_list ${module_name})
endforeach(module_file ${MODEL_DLL_LIST})

list(APPEND CART3D_MODELS_DLL ${CART3D_MODELS_LIB})

# 导出库模块列表
set(CART3D_MODELS_DLL ${model_dll_list} CACHE PATH "This is th Cart3d library list")
