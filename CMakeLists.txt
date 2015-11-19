cmake_minimum_required(VERSION 2.6)

project(YuXianLinuxStudy)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(RUN_TARGET STREQUAL arm)
set(CXX_FLAGS
#生成调试信息
 -g
 # -DVALGRIND
 #-D，定义一个宏
 -DMUDUO_STD_STRING
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -DRUN_TARGET_ARM
 #大部分警告都给出提示
 -Wall
 #给出一些额外的警告，比如没有使用的函数参数等
 #-Wextra
 #把警告当错误处理，有警告时停止编译
 #-Werror
 #一些可能改变值的隐式转换给出警告
 #-Wconversion
 #函数中出现未使用的参数时，不给出警告
 #-Wno-unused-parameter
 #c风格的强制转换给出警告,python 编译不过
 #-Wold-style-cast
 #如果函数的声明隐藏住了虚函数的声明，则给出警告，比如基类定义虚函数无参数，
 #但派生类中有同名的函数却有参数，此时就隐藏了基类的虚函数。
 -Woverloaded-virtual
 #对函数指针或者void *类型指针进行算术运算时给出警告
 -Wpointer-arith
 #当一个局部变量遮盖了另一个局部变量或全局变量时给出警告
 #-Wshadow
 #规定字符串常量的类型是const char[length]，因此将这样的地址赋值给non-const char *
 #指针时将产生警告，这些警告能够帮助在编译期发现企图写入字符串常量的代码
 -Wwrite-strings
 #指定cpu体系结构为本地平台，使用gcc提供原子操作接口时必须指定。
 -march=armv4
 # -MMD
 # -std=c++0x
 #用来通知连接器将所有符号添加到符号表中，目的是能够通过使用dlopen来实现向后的跟踪，异常打印符号表示估计会使用到。
 -rdynamic
 )
else()
set(CXX_FLAGS
#生成调试信息
 -g
 # -DVALGRIND
 #-D，定义一个宏
 -DMUDUO_STD_STRING
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -DRUN_TARGET_X86
 #大部分警告都给出提示
 -Wall
 #给出一些额外的警告，比如没有使用的函数参数等
 #-Wextra
 #把警告当错误处理，有警告时停止编译
 #-Werror
 #一些可能改变值的隐式转换给出警告
 #-Wconversion
 #函数中出现未使用的参数时，不给出警告
 -Wno-unused-parameter
 #c风格的强制转换给出警告,python 编译不过
 #-Wold-style-cast
 #如果函数的声明隐藏住了虚函数的声明，则给出警告，比如基类定义虚函数无参数，
 #但派生类中有同名的函数却有参数，此时就隐藏了基类的虚函数。
 -Woverloaded-virtual
 #对函数指针或者void *类型指针进行算术运算时给出警告
 -Wpointer-arith
 #当一个局部变量遮盖了另一个局部变量或全局变量时给出警告
 #-Wshadow
 #规定字符串常量的类型是const char[length]，因此将这样的地址赋值给non-const char *
 #指针时将产生警告，这些警告能够帮助在编译期发现企图写入字符串常量的代码
 -Wwrite-strings
 #指定cpu体系结构为本地平台，使用gcc提供原子操作接口时必须指定。
 -march=native
 # -MMD
 # -std=c++0x
 #用来通知连接器将所有符号添加到符号表中，目的是能够通过使用dlopen来实现向后的跟踪，异常打印符号表示估计会使用到。
 -rdynamic
 )
endif()
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

if(RUN_TARGET STREQUAL arm)
	set(CMAKE_CXX_COMPILER "/home/gaoyujing/项目/arm-2008q1_back/bin/arm-none-linux-gnueabi-g++")
	add_definitions(-DLUA_C89_NUMBERS)
else()
	set(CMAKE_CXX_COMPILER "g++")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#enable share library
SET(BUILD_SHARED_LIBS ON)

#find_package(Boost REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include")

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

#make install

add_subdirectory(src/linux-c)
