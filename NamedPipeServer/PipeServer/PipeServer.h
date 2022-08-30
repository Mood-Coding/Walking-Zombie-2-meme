#pragma once

#include "PipeServerBase.h"
#include "ImGui/Render/Render.h"
#include "OverlayManager/Overlay.h"
#include "Utils/Utils.h"

#ifndef NAMEDPIPE_H
#define NAMEDPIPE_H

enum class EventID
{
	NONE = 0x1,

	SEND_CONFIG,
};

#pragma pack(1)
struct RequestSetConfig
{
	char Config[128];
	char Value[64];
};
#pragma pack()

class PipeServer : public PipeServerBase
{
private:
	void ResetCommandID() { CommandID = EventID::NONE; }

public:
	EventID CommandID = EventID::NONE;

	EventID ReqCommandID = EventID::NONE;
	RequestSetConfig reqSetConfig{};

	void HandleCommand(EventID& commandID);
	void SendConfig(const char* config, const char* value);
};

extern PipeServer g_PipeServer;
#endif