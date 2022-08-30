#pragma once

#include "Utils/Utils.h"

#ifndef PIPESERVERBASE_H
#define PIPESERVERBASE_H

class PipeServerBase
{
protected:
	bool SendToPipeClient(LPCVOID buffer, DWORD buffer_size);

public:
	bool Setup();
	void Cleanup();

	const char* const NAMEDPIPE_SERVER_NAME = "\\\\.\\pipe\\WalkingZombie2";
	HANDLE hPipe;

	DWORD bytesRead = 0;
	DWORD BytesWritten = 0;
};

#endif