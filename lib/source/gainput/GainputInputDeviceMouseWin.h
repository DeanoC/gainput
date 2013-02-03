
#ifndef GAINPUTINPUTDEVICEMOUSEWIN_H_
#define GAINPUTINPUTDEVICEMOUSEWIN_H_

namespace gainput
{
	
class InputDeviceMouseImpl
{
public:
	InputDeviceMouseImpl(InputManager& manager, DeviceId device);
	~InputDeviceMouseImpl();

	void Update(InputState& state, InputState& previousState, InputDeltaState* delta);

	void HandleMessage(const MSG& msg);

private:
	InputManager& manager_;
	DeviceId device_;
	InputState* state_;
	InputState* previousState_;
	InputDeltaState* delta_;
};

}

#endif
