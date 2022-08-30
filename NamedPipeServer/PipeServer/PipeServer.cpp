#include "pch.h"

#include "PipeServer.h"

PipeServer g_PipeServer;

void PipeServer::HandleCommand(EventID& commandID)
{
	switch (commandID)
	{
		case EventID::NONE:
			break;
	}
}

void PipeServer::SendConfig(const char* config, const char* value)
{
	this->ReqCommandID = EventID::SEND_CONFIG;
	PipeServerBase::SendToPipeClient(&this->ReqCommandID, sizeof(this->ReqCommandID));

	strcpy_s(this->reqSetConfig.Config, config);
	strcpy_s(this->reqSetConfig.Value, value);
	PipeServerBase::SendToPipeClient(&this->reqSetConfig, sizeof(this->reqSetConfig));
}