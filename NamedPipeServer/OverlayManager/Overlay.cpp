#include "pch.h"

#include "Overlay.h"

Overlay g_Overlay;

bool Overlay::Setup()
{
	GamePID = Utils::GetPIDByProcessName(L"The Walking Zombie 2.exe");
	if (!GamePID)
	{
		spdlog::error("[GetPID] Can't find game process!");
		return false;
	}

	GameHwnd = FindWindowW(GAME_CLASS_NAME, GAME_WINDOW_NAME);
	if (!GameHwnd)
	{
		spdlog::error("[FindWindowW] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	if (!Utils::GetWndWidthHeight(GameHwnd, &GameWndWidth, &GameWndHeight))
	{
		spdlog::error("[GetWndWidthHeight] [GetClientRect] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	if (!Utils::GetWndScreenPos(GameHwnd, &GameWndTopLeft))
	{
		spdlog::error("[GetWndScreenPos] [ClientToScreen] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	wc = { sizeof(WNDCLASSEX), ACS_TRANSPARENT, WndProc, 0L, 0L, GetModuleHandleW(nullptr), nullptr, nullptr, nullptr, nullptr, GAME_WINDOW_NAME, nullptr };
	RegisterClassEx(&wc);
	OverlayHwnd = CreateWindowExW(/*WS_EX_TOPMOST |*/ WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, GAME_WINDOW_NAME, GAME_WINDOW_NAME, WS_POPUP, GameWndTopLeft.x, GameWndTopLeft.y, GameWndWidth, GameWndHeight, this->GameHwnd/*NULL*/, 0, 0, nullptr);

	if (OverlayHwnd == nullptr)
	{
		spdlog::error("[CreateWindowExW] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	SetLayeredWindowAttributes(OverlayHwnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(OverlayHwnd, &margins);

	// Hide Overlay window
	SetWindowDisplayAffinity(this->OverlayHwnd, WDA_EXCLUDEFROMCAPTURE);

	AlignWindThread = std::jthread(&Overlay::AlignWindow, &g_Overlay, &GamePID);

	return true;
}

void Overlay::Cleanup()
{
	spdlog::info("Closing AlignWndThread");
	g_Overlay.AlignWindThreadRun = false;
	this->AlignWindThread.join();
}

// Function run in thread
void Overlay::AlignWindow(DWORD* game_pid)
{
	while (*game_pid)
	{
		(*game_pid) = Utils::GetPIDByProcessName(L"The Walking Zombie 2.exe");

		this->GameHwnd = FindWindowExW(nullptr, nullptr, GAME_CLASS_NAME, GAME_WINDOW_NAME);
		if (!this->GameHwnd)
		{
			spdlog::error("[FindWindowW] {}", GetLastError());
			//PostQuitMessage(0);
			//break;
			continue;
		}

		if (!Utils::GetWndWidthHeight(GameHwnd, &GameWndWidth, &GameWndHeight))
		{
			spdlog::error("[GetWndWidthHeight] [GetClientRect] {0}", Utils::ErrorCodeToString(GetLastError()));
			break;
		}

		if (!Utils::GetWndScreenPos(GameHwnd, &GameWndTopLeft))
		{
			spdlog::error("[GetWndScreenPos] [ClientToScreen] {0}", Utils::ErrorCodeToString(GetLastError()));
			break;
		}

		MoveWindow(this->OverlayHwnd, this->GameWndTopLeft.x, this->GameWndTopLeft.y, this->GameWndWidth, this->GameWndHeight, true);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	spdlog::info("End AlignWindow loop");
}

void Overlay::ChangeClickability(bool canclick)
{
	long style = GetWindowLongW(OverlayHwnd, GWL_EXSTYLE);
	if (canclick)
	{
		style &= ~WS_EX_LAYERED;
		SetWindowLongW(OverlayHwnd, GWL_EXSTYLE, style);
		SetForegroundWindow(OverlayHwnd);
	}
	else
	{
		style |= WS_EX_LAYERED;
		SetWindowLongW(OverlayHwnd, GWL_EXSTYLE, style);
	}
}

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_SIZE:
			if (g_Render.g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
			{
				g_Render.CleanupRenderTarget();
				g_Render.g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				g_Render.CreateRenderTarget();
			}
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}