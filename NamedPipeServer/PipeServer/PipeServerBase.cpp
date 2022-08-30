#include "pch.h"

#include "PipeServerBase.h"

bool PipeServerBase::Setup()
{
	spdlog::info("Creating NamedPipe: {0}", NAMEDPIPE_SERVER_NAME);
	hPipe = CreateNamedPipeA(NAMEDPIPE_SERVER_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 1024, 1024, NULL, nullptr);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		spdlog::info("Created NamedPipe: {0}", hPipe);
	}
	else
	{
		spdlog::error("[CreateNamedPipeA] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	spdlog::info("Waiting for pipe connect");
	if (ConnectNamedPipe(hPipe, nullptr))
	{
		spdlog::info("Pipe connected");
	}
	else
	{
		spdlog::info("Pipe connect failed");
		CloseHandle(hPipe);
		return false;
	}

	/*DWORD dwMode = PIPE_NOWAIT;
	SetNamedPipeHandleState(hPipe, &dwMode, nullptr, nullptr);*/

	return true;
}

void PipeServerBase::Cleanup()
{
	spdlog::info("Cleaning up and exiting program.");

	if (DisconnectNamedPipe(hPipe))
	{
		spdlog::info("Disconnected the server end of the named pipe.");
	}
	else
	{
		spdlog::error("[DisconnectNamedPipe] {0}", Utils::ErrorCodeToString(GetLastError()));
	}

	CloseHandle(hPipe);
}

///////////////
// PROTECTED //
///////////////

bool PipeServerBase::SendToPipeClient(LPCVOID buffer, DWORD buffer_size)
{
	if (WriteFile(hPipe, buffer, buffer_size, &BytesWritten, nullptr))
	{
		if (buffer_size - BytesWritten == 0)
		{
			spdlog::info("[WriteFile] Write {0} bytes!", buffer_size);
		}
		else
		{
			spdlog::warn("[WriteFile] Missing {0} bytes!", buffer_size - BytesWritten);
		}
	}
	else
	{
		spdlog::error("[WriteFile] {0}", Utils::ErrorCodeToString(GetLastError()));
		return false;
	}

	return true;
}