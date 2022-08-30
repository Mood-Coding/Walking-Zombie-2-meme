#include "pch.h"

#include "Utils.h"

std::array<std::string_view, 256> key_codes
{
	"Unknown",
	"Left Mouse",
	"Right Mouse",
	"Control-break",
	"Middle Mouse",
	"X1 Mouse",
	"X2 Mouse",
	"Undefined",
	"Backspace",
	"TAB",
	"Reserved",
	"Reserved",
	"Clear",
	"Enter",
	"Reserved",
	"Reserved",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"CAPS Lock",
	"IME",
	"IME",
	"IME",
	"IME",
	"IME",
	"IME",
	"ESC",
	"IME",
	"IME",
	"IME",
	"IME",
	"Spacebar",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left Arrow",
	"Up Arrow",
	"Right Arrow",
	"Down Arrow",
	"Select",
	"Print",
	"Execute",
	"Print Screen",
	"Insert",
	"Delete",
	"Help",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Left Window",
	"Right Window",
	"Applications",
	"Reserved",
	"Sleep",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Numpad *",
	"Numpad +",
	"Numpad Separator",
	"Numpad -",
	"Numpad .",
	"Numpad /",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Numlock",
	"Scroll",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Left Shift",
	"Right Shift",
	"Left Control",
	"Right Control",
	"Left Menu",
	"Right Menu",
	"Browser back",
	"Browser forward",
	"Browser refresh",
	"Browser stop",
	"Browser search",
	"Browser favorites",
	"Browser home",
	"Volume mute",
	"Volume down",
	"Volume up",
	"Next track",
	"Previous track",
	"Stop track",
	"Play/Pause track",
	"Start mail",
	"Select media",
	"Start app1",
	"Start app2",
	"Reserved",
	"Reserved",
	";:",
	"+",
	",",
	"-",
	".",
	"/?",
	"`~",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"[{",
	"\\|",
	"]}",
	"\'\"",
	"OEM",
	"Reserved",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"IME",
	"OEM",
	"VK_PACKET",
	"Unassigned",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"Attn",
	"CrSel",
	"ExSel",
	"EOF",
	"Play",
	"Zoom",
	"Noname",
	"PA1",
	"Clear",
	"None"
};

std::vector<std::string> Utils::parse_str(std::string str, char delimiter)
{
	std::stringstream ss(str);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, delimiter);
		result.push_back(substr);
	}

	return result;
}

void Utils::write_file(const wchar_t* path, unsigned char* buffer, size_t buffer_len)
{
	FILE* file = NULL;

	_wfopen_s(&file, path, L"wb");
	if (!file)
		fatal("Cannot open file '%S'.\n", path);

	const int items_to_write = 1;
	if (fwrite(buffer, buffer_len, items_to_write, file) != items_to_write)
		fatal("Failed to write file '%S'.\n", path);

	fclose(file);
}

void Utils::write_file(const std::wstring path, unsigned char* buffer, size_t buffer_len)
{
	FILE* file = NULL;

	_wfopen_s(&file, path.c_str(), L"wb");
	if (!file)
		fatal("Cannot open file '%S'.\n", path.c_str());

	const int items_to_write = 1;
	if (fwrite(buffer, buffer_len, items_to_write, file) != items_to_write)
		fatal("Failed to write file '%S'.\n", path.c_str());

	fclose(file);
}

void Utils::write_file(const std::string path, unsigned char* buffer, size_t buffer_len)
{
	FILE* file = NULL;
	std::wstring path_new(path.begin(), path.end());

	_wfopen_s(&file, path_new.c_str(), L"wb");
	if (!file)
		fatal("Cannot open file '%S'.\n", path_new.c_str());

	const int items_to_write = 1;
	if (fwrite(buffer, buffer_len, items_to_write, file) != items_to_write)
		fatal("Failed to write file '%S'.\n", path_new.c_str());

	fclose(file);
}

char* Utils::read_file(const wchar_t* path, size_t* len)
{
	FILE* f = NULL;
	if (_wfopen_s(&f, path, L"rb") || !f) {
		fatal("Cannot open file '%S'.\n", path);
	}

	if (fseek(f, 0, SEEK_END)) {
		fatal("Cannot read file '%S'. (1)\n", path);
	}

	long llen = ftell(f);
	if (llen < 0) {
		fatal("Cannot read file '%S'. (2)\n", path);
	}

	if (fseek(f, 0, SEEK_SET)) {
		fatal("Cannot read file '%S'. (3)\n", path);
	}

	if (llen == 0) {
		*len = 0;
		return NULL;
	}

	char* buf = (char*)malloc(llen);
	if (fread(buf, llen, 1, f) != 1) {
		fatal("Cannot read file '%S'. (4)\n", path);
	}

	*len = llen;
	return buf;
}

constexpr const std::string_view& Utils::get_key_name(const std::size_t key_code)
{
	return key_codes.at(key_code < key_codes.size() ? key_code : 0);
}
//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string Utils::ErrorCodeToString(DWORD error_code)
{
	if (error_code == 0)
	{
		return "0"; //No error message has been recorded
	}

	LPSTR messageBuffer = {};

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

bool Utils::GetWndWidthHeight(const HWND& hwnd, long* wnd_width, long* wnd_height)
{
	RECT rct;
	if (!GetClientRect(hwnd, &rct))
	{
		return false;
	}

	*wnd_width = rct.right;
	*wnd_height = rct.bottom;

	return true;
}

bool Utils::GetWndScreenPos(const HWND& hwnd, POINT* wnd_topleft, POINT* wnd_bottomright)
{
	memset(wnd_topleft, 0, sizeof(POINT));
	return ClientToScreen(hwnd, wnd_topleft)
		&& (wnd_bottomright == nullptr ? true : ClientToScreen(hwnd, wnd_bottomright));
}

void Utils::ToLowerStr(std::string& str)
{
	size_t str_length = str.length();
	for (int i = 0; i < str_length; ++i)
	{
		str[i] = (char)std::tolower(str[i]);
	}
}

DWORD Utils::GetPIDByProcessName(const wchar_t* processName)
{
	DWORD PID = 0;
	HANDLE hProcessSnapshot;
	PROCESSENTRY32 PE32;

	// Take a snapshot of all processes in the system.
	hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "<CreateToolhelp32Snapshot> Invalid handle";
		return 0;
	}

	// Set the size of the structure before using it.
	PE32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieves information about the first process and exit if unsuccessful
	if (!Process32First(hProcessSnapshot, &PE32))
	{
		std::cout << "<Process32First> Error " << GetLastError() << '\n';
		CloseHandle(hProcessSnapshot);
		return 0;
	}

	// Now walk the snapshot of processes,
	// and find the right process then get its PID
	do
	{
		// Returns 0 value indicates that both wchar_t* string are equal
		if (wcscmp(processName, PE32.szExeFile) == 0)
		{
			PID = PE32.th32ProcessID;
			break;
		}
	}
	while (Process32Next(hProcessSnapshot, &PE32));

	CloseHandle(hProcessSnapshot);
	return PID;
}