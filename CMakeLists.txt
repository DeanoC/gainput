cmake_minimum_required(VERSION 3.12.4)
get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
	option(unittests "unittests" OFF)
	get_filename_component(_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
	set_property(GLOBAL PROPERTY GLOBAL_FETCHDEPS_BASE ${_PARENT_DIR}/al2o3 )
	include(FetchContent)
	FetchContent_Declare( al2o3 GIT_REPOSITORY https://github.com/DeanoC/al2o3 GIT_TAG master )
	FetchContent_GetProperties(al2o3)
	if(NOT al2o3_POPULATED)
		FetchContent_Populate(al2o3)
		add_subdirectory(${al2o3_SOURCE_DIR} ${al2o3_BINARY_DIR})
	endif()
	INIT_AL2O3(${CMAKE_CURRENT_SOURCE_DIR})
endif ()

SET_MIN_VERSIONS()
set(LibName input_gainput)

project(${LibName})
set(Interface

		)
set(Src
		../lib/source/gainput/builtin/GainputInputDeviceBuiltIn.cpp
		../lib/source/gainput/builtin/GainputInputDeviceBuiltInAndroid.h
		../lib/source/gainput/builtin/GainputInputDeviceBuiltInImpl.h
		../lib/source/gainput/builtin/GainputInputDeviceBuiltInIos.h
		../lib/source/gainput/builtin/GainputInputDeviceBuiltInIos.mm
		../lib/source/gainput/builtin/GainputInputDeviceBuiltInNull.h

		../lib/source/gainput/dev/GainputDev.cpp
		../lib/source/gainput/dev/GainputDev.h
		../lib/source/gainput/dev/GainputDevProtocol.h
		../lib/source/gainput/dev/GainputMemoryStream.cpp
		../lib/source/gainput/dev/GainputMemoryStream.h
		../lib/source/gainput/dev/GainputNetAddress.cpp
		../lib/source/gainput/dev/GainputNetAddress.h
		../lib/source/gainput/dev/GainputNetConnection.cpp
		../lib/source/gainput/dev/GainputNetConnection.h
		../lib/source/gainput/dev/GainputNetListener.cpp
		../lib/source/gainput/dev/GainputNetListener.h
		../lib/source/gainput/dev/GainputStream.h

		../lib/source/gainput/gestures/GainputButtonStickGesture.cpp
		../lib/source/gainput/gestures/GainputDoubleClickGesture.cpp
		../lib/source/gainput/gestures/GainputHoldGesture.cpp
		../lib/source/gainput/gestures/GainputPinchGesture.cpp
		../lib/source/gainput/gestures/GainputRotateGesture.cpp
		../lib/source/gainput/gestures/GainputSimultaneouslyDownGesture.cpp
		../lib/source/gainput/gestures/GainputTapGesture.cpp

		../lib/source/gainput/keyboard/GainputInputDeviceKeyboard.cpp
		../lib/source/gainput/keyboard/GainputInputDeviceKeyboardEvdev.h
		../lib/source/gainput/keyboard/GainputInputDeviceKeyboardImpl.h
		../lib/source/gainput/keyboard/GainputInputDeviceKeyboardNull.h
		../lib/source/gainput/keyboard/GainputKeyboardKeyNames.h

		../lib/source/gainput/mouse/GainputInputDeviceMouse.cpp
		../lib/source/gainput/mouse/GainputInputDeviceMouseEvdev.h
		../lib/source/gainput/mouse/GainputInputDeviceMouseImpl.h
		../lib/source/gainput/mouse/GainputInputDeviceMouseNull.h
		../lib/source/gainput/mouse/GainputMouseInfo.h

		../lib/source/gainput/pad/GainputInputDevicePad.cpp
		../lib/source/gainput/pad/GainputInputDevicePadImpl.h
		../lib/source/gainput/pad/GainputInputDevicePadNull.h

		../lib/source/gainput/recorder/GainputInputPlayer.cpp
		../lib/source/gainput/recorder/GainputInputRecorder.cpp
		../lib/source/gainput/recorder/GainputInputRecording.cpp

		../lib/source/gainput/touch/GainputInputDeviceTouch.cpp
		../lib/source/gainput/touch/GainputInputDeviceTouchImpl.h
		../lib/source/gainput/touch/GainputInputDeviceTouchNull.h
		../lib/source/gainput/touch/GainputTouchInfo.h

		../lib/source/gainput/gainput.cpp
		../lib/source/gainput/GainputAllocator.cpp
		../lib/source/gainput/GainputHelpersEvdev.h
		../lib/source/gainput/GainputInputDeltaState.cpp
		../lib/source/gainput/GainputInputDevice.cpp
		../lib/source/gainput/GainputInputManager.cpp
		../lib/source/gainput/GainputInputMap.cpp
		../lib/source/gainput/GainputInputState.cpp
		../lib/source/gainput/GainputMapFilters.cpp
		)
if(APPLE)
	list(APPEND Src
			../lib/source/gainput/pad/GainputInputDevicePadMac.cpp
			../lib/source/gainput/pad/GainputInputDevicePadMac.h
			../lib/source/gainput/GainputMac.mm
			../lib/source/gainput/mouse/GainputInputDeviceMouseMac.h
			../lib/source/gainput/mouse/GainputInputDeviceMouseMac.mm
			../lib/source/gainput/keyboard/GainputInputDeviceKeyboardMac.cpp
			../lib/source/gainput/keyboard/GainputInputDeviceKeyboardMac.h
			)
endif()
if(WIN32)
	list(APPEND Src
			../lib/source/gainput/GainputWindows.h
			../lib/source/gainput/pad/GainputInputDevicePadWin.h
			../lib/source/gainput/mouse/GainputInputDeviceMouseWin.h
			../lib/source/gainput/mouse/GainputInputDeviceMouseWinRaw.h
			../lib/source/gainput/keyboard/GainputInputDeviceKeyboardWin.h
			../lib/source/gainput/keyboard/GainputInputDeviceKeyboardWinRaw.h

			)
endif()
if(UNIX)
	list(APPEND Src
			../lib/source/gainput/pad/GainputInputDevicePadLinux.h
			../lib/source/gainput/mouse/GainputInputDeviceMouseLinux.h
			../lib/source/gainput/keyboard/GainputInputDeviceKeyboardLinux.h

			)
endif()
set(Deps
		)

ADD_LIB(${LibName} "${Interface}" "${Src}" "${Deps}")
target_include_directories(${LibName} PUBLIC lib/include)
if(WIN32)
	target_link_libraries(${LibName} PUBLIC Xinput.lib )
endif()
