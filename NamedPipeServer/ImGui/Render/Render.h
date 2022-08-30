#pragma once

#include "../../pch.h"
#include "../imgui.h"
#include "../imgui_internal.h"
#include "../backends/imgui_impl_dx11.h"
#include "../backends/imgui_impl_win32.h"
#include "OverlayManager/Overlay.h"

#ifndef RENDER_H
#define RENDER_H

class Render
{
private:
	
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();

	void SetTheme() const;

	void GetImDrawList();

public:
	ID3D11Device* g_pd3dDevice;
	ID3D11DeviceContext* g_pd3dDeviceContext;
	IDXGISwapChain* g_pSwapChain;
	ID3D11RenderTargetView* g_mainRenderTargetView;

	ImFont* m_pFont;
	ImFont* SEGOEUI_20;
	ImDrawList* DrawList;

	bool Setup(HWND& hwnd, WNDCLASSEX& wc);

	void CreateRenderTarget();
	void CleanupRenderTarget();

	bool CreateFrame() const;
	void BeginOverlayWindow();
	void EndOverlayWindow() const;
	void Rendering();

	void Rect(const ImVec2& top_left, const ImVec2& bottom_right, unsigned int color, float rounding = 0.0f, float thickness = 1.0f);
	void Rect(float x, float y, float width, float height, unsigned int color, float rounding = 0.0f, float thickness = 1.0f);
};

extern Render g_Render;

#endif // !_RENDER_H_




