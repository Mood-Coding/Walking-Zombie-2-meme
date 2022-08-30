#include "pch.h"

#include "Input.h"

void KeyboardInput()
{
	if (GetAsyncKeyState(VK_HOME) & 0x01)
	{
		g_Menu.IsShow = !g_Menu.IsShow;
		g_Overlay.ChangeClickability(g_Menu.IsShow);

		if (g_Menu.IsShow)
		{
			SetForegroundWindow(g_Overlay.OverlayHwnd);
			SetCapture(g_Overlay.OverlayHwnd);
			SetFocus(g_Overlay.OverlayHwnd);
			SetActiveWindow(g_Overlay.OverlayHwnd);
			ShowWindow(g_Overlay.OverlayHwnd, SW_NORMAL);
			EnableWindow(g_Overlay.OverlayHwnd, TRUE);
		}
		else
		{
			SetForegroundWindow(g_Overlay.GameHwnd);
			SetCapture(g_Overlay.GameHwnd);
			SetFocus(g_Overlay.GameHwnd);
			SetActiveWindow(g_Overlay.GameHwnd);
			ShowWindow(g_Overlay.GameHwnd, SW_NORMAL);
			EnableWindow(g_Overlay.GameHwnd, TRUE);
		}
	}
}