#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif // _Win32

namespace KeyboardUtils
{
#ifdef _WIN32
	class Keys
	{
	public:
		static const int ESC = VK_ESCAPE;
		static const int LEFT_ARROW = VK_LEFT;
		static const int RIGHT_ARROW = VK_RIGHT;
		static const int UP_ARROW = VK_UP;
		static const int DOWN_ARROW = VK_DOWN;
	};
#endif // _WIN32

	bool IsKeyPressed(int key);
}