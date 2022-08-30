#pragma once

#include "ImGui/imgui.h"
#include "ImGui/Render/Render.h"

#include "Utils/Utils.h"

#ifndef OVERLAY_H
#define OVERLAY_H

constexpr auto GAME_CLASS_NAME = L"UnityWndClass";
constexpr auto GAME_WINDOW_NAME = L"The Walking Zombie 2";

class Overlay
{
public:
	HWND OverlayHwnd{};

	DWORD GamePID = 0;
	HWND GameHwnd{};
	POINT GameWndTopLeft{};
	POINT GameWndBottomRight{};
	long GameWndWidth = 0;
	long GameWndHeight = 0;

	WNDCLASSEX wc{};



	std::atomic_bool AlignWindThreadRun = true;
	std::jthread AlignWindThread;

	bool Setup();
	void Cleanup();
	void AlignWindow(DWORD* game_pid);

	void ChangeClickability(bool canclick);
};

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern Overlay g_Overlay;

#endif // !OVERLAY_H
