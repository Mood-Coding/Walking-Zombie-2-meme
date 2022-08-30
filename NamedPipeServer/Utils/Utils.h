#pragma once

#include "pch.h"

#define IS_EMPTY_STR(X) ( (1 / (sizeof(X[0]) == 1))/*type check*/ &`& !(X[0])/*content check*/)

#define fatal(format, ...) do { \
	fprintf(stderr, format, ##__VA_ARGS__); \
	exit(1); \
} while (0)

namespace fs = std::filesystem;

extern std::array<std::string_view, 256> key_codes;

namespace Utils
{
	std::vector<std::string> parse_str(std::string str, char delimiter);

	void write_file(const wchar_t* path, unsigned char* buf, size_t len);
	void write_file(const std::wstring path, unsigned char* buffer, size_t buffer_len);
	void write_file(const std::string path, unsigned char* buffer, size_t buffer_len);
	char* read_file(const wchar_t* path, size_t* len);

	template<typename T>
	std::string hash(T data)
	{
		std::hash<T> T_hash;
		return std::to_string(T_hash(data));
	}

	constexpr const std::string_view& get_key_name(const std::size_t key_code);

	std::string ErrorCodeToString(DWORD error_code);

	bool GetWndWidthHeight(const HWND& hwnd, long* wnd_width, long* wnd_height);
	bool GetWndScreenPos(const HWND& hwnd, POINT* wnd_topleft, POINT* wnd_bottomright = nullptr);

	void ToLowerStr(std::string& str);

	DWORD GetPIDByProcessName(const wchar_t* processName);
};