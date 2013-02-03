
#ifndef GAINPUTINPUTDEVICEKEYBOARDWIN_H_
#define GAINPUTINPUTDEVICEKEYBOARDWIN_H_


namespace gainput
{
	
class InputDeviceKeyboardImpl
{
public:
	InputDeviceKeyboardImpl(InputManager& manager, DeviceId device);
	~InputDeviceKeyboardImpl();

	void Update(InputState& state, InputState& previousState, InputDeltaState* delta);

	bool IsTextInputEnabled() const { return textInputEnabled_; }

	void SetTextInputEnabled(bool enabled) { textInputEnabled_ = enabled; }

	char GetNextCharacter()
	{
		if (!textBuffer_.CanGet())
		{
			return 0;
		}
		return textBuffer_.Get();
	}

	void HandleMessage(const MSG& msg);

private:
	InputManager& manager_;
	DeviceId device_;
	bool textInputEnabled_;
	RingBuffer<GAINPUT_TEXT_INPUT_QUEUE_LENGTH, char> textBuffer_;
	DialectTable<unsigned> dialect_;
	InputState* state_;
	InputState* previousState_;
	InputDeltaState* delta_;
};


}

#endif /* GAINPUTINPUTDEVICEKEYBOARDWIN_H_ */