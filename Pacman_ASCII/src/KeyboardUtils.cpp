#include "KeyboardUtils.h"

namespace KeyboardUtils
{
#ifdef _WIN32
	bool IsKeyPressed(int key)
	{
		return GetKeyState(key) < 0;
	}
#endif // _WIN32
}