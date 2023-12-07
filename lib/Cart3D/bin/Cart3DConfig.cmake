# ����Cart3D�������ļ�
# ʵ����find_package�Ĺ���
# ʹ��ʱֻ��Ҫ��CMakeLists.txt�����:
#     find_package(Cart3D)
#     .....
#     target_link_libraries(MY_TARGET_NAME PRIVATE ${CART3D_MODELS_DLL})
#     

cmake_minimum_required(VERSION 3.5)

set(CART3D_PATHS 
    "${CMAKE_SOURCE_DIR}/3rdlib/Cart3D"
    "${CMAKE_SOURCE_DIR}/../Cart3D"
)

# ����ͷ�ļ�·��
find_path(CART3D_CORE_INCLUDE_DIR include/Cart3DCore PATHS ${CART3D_PATHS}/include)

# ������̬���ļ�
find_library(CART3D_CORE_LIB NAMES common.lib PATHS ${CART3D_CORE_INCLUDE_DIR} PATH_SUFFIXES lib)
# ��ȡ�����̬��ĸ�Ŀ¼·��
get_filename_component(_CART3D_LIB_PATH_ ${CART3D_CORE_LIB} PATH)

# ������·�� Cart3D/lib
set(CART3D_LIB_PATH  ${_CART3D_LIB_PATH_} CACHE PATH "This is the Cart3D library path")
#message(${CART3D_LIB_PATH})
# ��ȡ��̬��
file(GLOB MODEL_LIST "${CART3D_LIB_PATH}/*.lib")
set(CART3D_MODELS_LIB)
foreach(module_file ${MODEL_LIST})
    get_filename_component(module_name ${module_file} NAME_WE)
    list(APPEND CART3D_MODELS_LIB ${module_name})
endforeach(module_file ${MODEL_LIST})

# ������̬��ģ���б�
#set(CART3D_MODELS_LIB ${CART3D_MODELS_LIB} CACHE PATH "This is th Cart3d library list")
link_directories(${CART3D_LIB_PATH})
get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(CART3D_CONFIG_PATH "${CMAKE_CURRENT_LIST_DIR}" REALPATH)
get_filename_component(CART3D_INSTALL_PATH "${CART3D_CONFIG_PATH}/../" REALPATH)

#message("CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")
#message("CART3D_CONFIG_PATH:${CART3D_CONFIG_PATH}")
#message("CART3D_INSTALL_PATH:${CART3D_INSTALL_PATH}")

# ����ͷ�ļ����б�
set(CART3D_INCLUDE_DIRS " ")
set(CART3DCORE_INCLUDE_DIRS " ")
set(__CART3D_INCLUDE_DIRS "${CART3D_INSTALL_PATH}/include")
set(__CART3DCORE_INCLUDE_DIRS "${CART3D_INSTALL_PATH}/include/Cart3DCore")

#message("__CART3D_INCLUDE_DIRS:${__CART3D_INCLUDE_DIRS}")
#message("__CART3DCORE_INCLUDE_DIRS:${__CART3DCORE_INCLUDE_DIRS}")
# ��ȡinclude�µ��������ļ���
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

# �ϲ���������ͷ�ļ�Ŀ¼
# spdlog\include
set(SPDLOG_INCLUDE ${__CART3D_INCLUDE_DIRS}/spdlog/include)
list(APPEND CART3D_INCLUDE_DIRS ${SPDLOG_INCLUDE})
list(APPEND CART3D_INCLUDE_DIRS ${__CART3D_INCLUDE_DIRS})
list(APPEND CART3D_INCLUDE_DIRS ${CART3DCORE_INCLUDE_DIRS})
set(CART3D_INCLUDE_DIRS ${CART3D_INCLUDE_DIRS} CACHE PATH "This is th Cart3d haeder folder list")

# ����ͷ�ļ�
include_directories(${CART3D_INCLUDE_DIRS})

# ��ȡ��̬���б�
file(GLOB MODEL_DLL_LIST "${CART3D_INSTALL_PATH}/bin/*.dll")
set(model_dll_list)
foreach(module_file ${MODEL_DLL_LIST})
    #message(${module_file})
    get_filename_component(module_name ${module_file} NAME_WE)
    list(APPEND model_dll_list ${module_name})
endforeach(module_file ${MODEL_DLL_LIST})

list(APPEND CART3D_MODELS_DLL ${CART3D_MODELS_LIB})

# ������ģ���б�
set(CART3D_MODELS_DLL ${model_dll_list} CACHE PATH "This is th Cart3d library list")
