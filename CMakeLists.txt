# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.19.1)
# 项目信息
project (CommonUtils 1.0)

#设置标准库语言等级
set(CMAKE_CXX_STANDARD 17)
#设置标准库依赖
set(CMAKE_CXX_STANDARD_REQUIRED True)

#设置生成debug版本后缀
set(CMAKE_DEBUG_POSTFIX d)

add_library(CommonUtils_compiler_flags INTERFACE)

#生成库文件
add_library (CommonUtils CommonUtils.cpp)
set_target_properties(CommonUtils PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# 指定 CommonUtils 库的安装路径
#include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)

install (TARGETS CommonUtils DESTINATION lib)
install (FILES CommonUtils.h DESTINATION include)