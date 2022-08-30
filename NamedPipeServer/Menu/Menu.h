#pragma once

#include "ImGui/imgui.h"
#include "Configuration/ConfigManager.h"
#include "PipeServer/PipeServer.h"

#ifndef MENU_H
#define MENU_H

class Menu
{
public:
	bool IsShow = true;

	void Draw() const;
};

extern Menu g_Menu;

#endif

