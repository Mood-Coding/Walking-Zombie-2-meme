#include "pch.h"

#define ENABLE_PIPE_SERVER

#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui_internal.h"
#include "ImGui/Render/Render.h"
#include "PipeServer/PipeServer.h"
#include "Configuration/ConfigManager.h"
#include "Configuration/Configs.h"
#include "OverlayManager/Overlay.h"
#include "Menu/Input.h"

int main()
{
	spdlog::set_pattern("%^[%l]%$ %v");

#ifdef ENABLE_PIPE_SERVER
	// Create NamedPipe server
	if (!g_PipeServer.Setup())
	{
		return 1;
	}
#endif // ENABLE_PIPE_SERVER

	if (!g_ConfigManager.Setup())
	{
		return 1;
	}
	if (!g_ConfigManager.Load())
	{
		return 1;
	}

	if (!g_Overlay.Setup())
	{
		return 1;
	}

	if (!g_Render.Setup(g_Overlay.OverlayHwnd, g_Overlay.wc))
	{
		return 1;
	}

	while (g_Overlay.GamePID)
	{
#ifdef ENABLE_PIPE_SERVER
		g_PipeServer.HandleCommand(g_PipeServer.CommandID);
#endif

		KeyboardInput();

		if (!g_Render.CreateFrame()) { break; }

		g_Menu.Draw();

		g_Render.Rendering();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	g_ConfigManager.Save();
	g_Overlay.Cleanup();
	g_PipeServer.Cleanup();
	return 0;
}