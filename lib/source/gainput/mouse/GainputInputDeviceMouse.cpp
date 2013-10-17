
#include <gainput/gainput.h>

#include "GainputInputDeviceMouseImpl.h"
#include "GainputInputDeviceMouseNull.h"
#include "GainputMouseInfo.h"
#include "../GainputInputDeltaState.h"
#include "../GainputHelpers.h"

#if defined(GAINPUT_PLATFORM_LINUX)
	#include "GainputInputDeviceMouseLinux.h"
	#include "GainputInputDeviceMouseEvdev.h"
#elif defined(GAINPUT_PLATFORM_WIN)
	#include "GainputInputDeviceMouseWin.h"
	#include "GainputInputDeviceMouseWinRaw.h"
#endif

namespace gainput
{

InputDeviceMouse::InputDeviceMouse(InputManager& manager, DeviceId device, DeviceVariant variant) :
	InputDevice(manager, device, manager.GetDeviceCountByType(DT_MOUSE)),
	impl_(0)
{
#if defined(GAINPUT_PLATFORM_LINUX)
	if (variant == DV_STANDARD)
	{
		impl_ = manager.GetAllocator().New<InputDeviceMouseImplLinux>(manager, device);
	}
	else if (variant == DV_RAW)
	{
		impl_ = manager.GetAllocator().New<InputDeviceMouseImplEvdev>(manager, device);
	}
#elif defined(GAINPUT_PLATFORM_WIN)
	if (variant == DV_STANDARD)
	{
		impl_ = manager.GetAllocator().New<InputDeviceMouseImplWin>(manager, device);
	}
	else if (variant == DV_RAW)
	{
		impl_ = manager.GetAllocator().New<InputDeviceMouseImplWinRaw>(manager, device);
	}
#endif

	if (!impl_)
	{
		impl_ = manager.GetAllocator().New<InputDeviceMouseImplNull>(manager, device);
	}
	GAINPUT_ASSERT(impl_);

	state_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), MouseButtonCount + MouseAxisCount);
	GAINPUT_ASSERT(state_);
	previousState_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), MouseButtonCount + MouseAxisCount);
	GAINPUT_ASSERT(previousState_);
}

InputDeviceMouse::~InputDeviceMouse()
{
	manager_.GetAllocator().Delete(state_);
	manager_.GetAllocator().Delete(previousState_);
	manager_.GetAllocator().Delete(impl_);
}

void
InputDeviceMouse::InternalUpdate(InputDeltaState* delta)
{
	impl_->Update(*state_, *previousState_, delta);
}

InputDevice::DeviceState
InputDeviceMouse::InternalGetState() const
{
	return impl_->GetState();
}

InputDevice::DeviceVariant
InputDeviceMouse::GetVariant() const
{
	return impl_->GetVariant();
}

size_t
InputDeviceMouse::GetAnyButtonDown(DeviceButtonSpec* outButtons, size_t maxButtonCount) const
{
	GAINPUT_ASSERT(outButtons);
	GAINPUT_ASSERT(maxButtonCount > 0);
	return CheckAllButtonsDown(outButtons, maxButtonCount, MouseButton0, MouseButtonCount_);
}

size_t
InputDeviceMouse::GetButtonName(DeviceButtonId deviceButton, char* buffer, size_t bufferLength) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	GAINPUT_ASSERT(buffer);
	GAINPUT_ASSERT(bufferLength > 0);
	strncpy(buffer, deviceButtonInfos[deviceButton].name, bufferLength);
	buffer[bufferLength-1] = 0;
	const size_t nameLen = strlen(deviceButtonInfos[deviceButton].name);
	return nameLen >= bufferLength ? bufferLength : nameLen+1;
}

ButtonType
InputDeviceMouse::GetButtonType(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	return deviceButtonInfos[deviceButton].type;
}

DeviceButtonId
InputDeviceMouse::GetButtonByName(const char* name) const
{
	GAINPUT_ASSERT(name);
	for (unsigned i = 0; i < MouseButtonCount + MouseAxisCount; ++i)
	{
		if (strcmp(name, deviceButtonInfos[i].name) == 0)
		{
			return DeviceButtonId(i);
		}
	}
	return InvalidDeviceButtonId;
}

}
