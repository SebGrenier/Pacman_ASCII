#include "ConsoleUtils.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

using namespace std;

namespace ConsoleUtils
{
#ifdef _WIN32
	void ClearConsole(void)
	{
		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X *csbi.dwSize.Y;

		/* Fill the entire buffer with spaces */
		if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Move the cursor home */
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}
#endif // _WIN32

#ifdef _WIN32
	void SetCursorPosition(int x, int y)
	{
		HANDLE hStdOut;
		COORD  coords = { x, y };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		// Move the cursor
		SetConsoleCursorPosition(hStdOut, coords);
	}
#endif // _WIN32
}
