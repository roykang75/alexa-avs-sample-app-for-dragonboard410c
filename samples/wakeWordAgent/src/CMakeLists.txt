﻿cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

project(WakeWordAgent)

set( WAKE_WORD_AGENT_SOURCE
        main.cpp
        WakeWordAgent.cpp
        WakeWordEngineFactory.cpp
        WakeWordEngine.cpp
        WakeWordIPCFactory.cpp
        WakeWordIPC.cpp
        WakeWordIPCSocket.cpp
        IPCInterface.cpp
        Logger.cpp
        WakeWordException.cpp
	#KittAiSnowboyWakeWordEngine.cpp
	#PortAudioWrapper.cpp
	#SensoryWakeWordEngine.cpp
        GPIOWakeWordEngine.cpp 
	gpio.c )

set( WAKE_WORD_AGENT_LIBS
	#        snowboy-detect
	#blas
	#portaudio
	#asound
	#sensory
	#wiringPi 
	libsoc
	#lib96BoardsGPIO
	)

find_package( Threads )
set( CMAKE_THREAD_PREFER_PTHREAD TRUE )

add_executable( wakeWordAgent ${WAKE_WORD_AGENT_SOURCE} )

# Set D_GLIBCXX_USE_CXX11_ABI to 0 to avoid undefined reference 
# to libsnowboy-detect.a that built with c++ regular string.
#set_target_properties( wakeWordAgent PROPERTIES COMPILE_FLAGS "-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -lsoc -l96BoardsGPIO" )
set_target_properties( wakeWordAgent PROPERTIES COMPILE_FLAGS "-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0" )
set_target_properties( wakeWordAgent PROPERTIES LINKER_FLAGS "-lsoc -l96BoardsGPIO" )
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed -lsoc -l96BoardsGPIO")


#target_include_directories( wakeWordAgent PRIVATE ${CMAKE_SOURCE_DIR}/../ext/include )

target_link_libraries( wakeWordAgent ${WAKE_WORD_AGENT_LIBS} )
target_link_libraries( wakeWordAgent ${CMAKE_THREAD_LIBS_INIT} )

add_library( libsoc STATIC IMPORTED )
set_target_properties( libsoc PROPERTIES IMPORTED_LOCATION
	${CMAKE_SOURCE_DIR}/../ext/lib/libsoc.a )

#add_library( lib96BoardsGPIO STATIC IMPORTED )
#set_target_properties( lib96BoardsGPIO PROPERTIES IMPORTED_LOCATION
#	${CMAKE_SOURCE_DIR}/../ext/lib/lib96BoardsGPIO.a )

#add_library( snowboy-detect STATIC IMPORTED )
#set_target_properties( snowboy-detect PROPERTIES IMPORTED_LOCATION
#  ${CMAKE_SOURCE_DIR}/../ext/lib/libsnowboy-detect.a )

#add_library( portaudio STATIC IMPORTED )
#set_target_properties( portaudio PROPERTIES IMPORTED_LOCATION
#  ${CMAKE_SOURCE_DIR}/../ext/lib/libportaudio.a )

#add_library( sensory STATIC IMPORTED )
#set_target_properties( sensory PROPERTIES IMPORTED_LOCATION
#  ${CMAKE_SOURCE_DIR}/../ext/lib/libsnsr.a )

#add_library( blas SHARED IMPORTED )
#set_target_properties( blas PROPERTIES IMPORTED_LOCATION
	#  ${CMAKE_SOURCE_DIR}/../ext/lib/libblas.so.3 )
