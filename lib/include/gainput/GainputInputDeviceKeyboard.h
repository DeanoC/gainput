
#ifndef GAINPUTINPUTDEVICEKEYBOARD_H_
#define GAINPUTINPUTDEVICEKEYBOARD_H_

namespace gainput
{

/// All valid device buttons for the keyboard device.
enum Key
{
	KEY_ESCAPE,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_PRINT,
	KEY_SCROLL_LOCK,
	KEY_BREAK,

	KEY_SPACE = 0x0020,

	KEY_APOSTROPHE = 0x0027,
	KEY_COMMA = 0x002c,
	KEY_MINUS = 0x002d,
	KEY_PERIOD = 0x002e,
	KEY_SLASH = 0x002f,

	KEY_0 = 0x0030,
	KEY_1 = 0x0031,
	KEY_2 = 0x0032,
	KEY_3 = 0x0033,
	KEY_4 = 0x0034,
	KEY_5 = 0x0035,
	KEY_6 = 0x0036,
	KEY_7 = 0x0037,
	KEY_8 = 0x0038,
	KEY_9 = 0x0039,

	KEY_SEMICOLON = 0x003b,
	KEY_LESS = 0x003c,
	KEY_EQUAL = 0x003d,

	KEY_A = 0x0041,
	KEY_B = 0x0042,
	KEY_C = 0x0043,
	KEY_D = 0x0044,
	KEY_E = 0x0045,
	KEY_F = 0x0046,
	KEY_G = 0x0047,
	KEY_H = 0x0048,
	KEY_I = 0x0049,
	KEY_J = 0x004a,
	KEY_K = 0x004b,
	KEY_L = 0x004c,
	KEY_M = 0x004d,
	KEY_N = 0x004e,
	KEY_O = 0x004f,
	KEY_P = 0x0050,
	KEY_Q = 0x0051,
	KEY_R = 0x0052,
	KEY_S = 0x0053,
	KEY_T = 0x0054,
	KEY_U = 0x0055,
	KEY_V = 0x0056,
	KEY_W = 0x0057,
	KEY_X = 0x0058,
	KEY_Y = 0x0059,
	KEY_Z = 0x005a,

	KEY_BRACKET_LEFT = 0x005b,
	KEY_BACKSLASH = 0x005c,
	KEY_BRACKET_RIGHT = 0x005d,

	KEY_GRAVE = 0x0060,

	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_INSERT,
	KEY_HOME,
	KEY_DELETE,
	KEY_END,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,

	KEY_NUM_LOCK,
	KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT,
	KEY_KP_ADD,
	KEY_KP_ENTER,
	KEY_KP_INSERT, // 0
	KEY_KP_END, // 1
	KEY_KP_DOWN, // 2
	KEY_KP_PAGE_DOWN, // 3
	KEY_KP_LEFT, // 4
	KEY_KP_BEGIN, // 5
	KEY_KP_RIGHT, // 6
	KEY_KP_HOME, // 7
	KEY_KP_UP, // 8
	KEY_KP_PAGE_UP, // 9
	KEY_KP_DELETE, // ,

	KEY_BACK_SPACE,
	KEY_TAB,
	KEY_RETURN,
	KEY_CAPS_LOCK,
	KEY_SHIFT_L,
	KEY_CTRL_L,
	KEY_SUPER_L,
	KEY_ALT_L,
	KEY_ALT_R,
	KEY_SUPER_R,
	KEY_MENU,
	KEY_CTRL_R,
	KEY_SHIFT_R,

	KEY_COUNT_
};


class InputDeviceKeyboardImpl;

/// A keyboard input device.
class GAINPUT_LIBEXPORT InputDeviceKeyboard : public InputDevice
{
public:
	/// Initializes the device.
	/**
	 * \param manager The input manager this device is managed by.
	 * \param device The ID of this device.
	 */
	InputDeviceKeyboard(InputManager& manager, DeviceId device);
	/// Shuts down the device.
	~InputDeviceKeyboard();

	void Update(InputDeltaState* delta);

	/// Returns DT_KEYBOARD.
	DeviceType GetType() const { return DT_KEYBOARD; }
	DeviceState GetState() const { return DS_OK; }
	bool IsValidButtonId(DeviceButtonId deviceButton) const { return deviceButton >= 0 && deviceButton < KEY_COUNT_; }

	bool GetAnyButtonDown(DeviceButtonId& outButtonId) const;

	void GetButtonName(DeviceButtonId deviceButton, char* buffer, size_t bufferLength) const;
	ButtonType GetButtonType(DeviceButtonId deviceButton) const;

	/// Returns if text input is enabled.
	bool IsTextInputEnabled() const;
	/// Sets if text input is enabled and therefore if calling GetNextCharacter() make sense.
	void SetTextInputEnabled(bool enabled);
	/// Returns the next pending input character if text input is enabled.
	char GetNextCharacter();

	/// Returns the platform-specific implementation of this device.
	InputDeviceKeyboardImpl* GetPimpl() { return impl_; }

private:
	InputDeviceKeyboardImpl* impl_;
};

}

#endif
