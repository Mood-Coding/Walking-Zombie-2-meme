#include "pch.h"

#include "ConfigManager.h"

namespace fs = std::filesystem;

ConfigManager g_ConfigManager;

bool ConfigManager::Setup()
{
	PWSTR documentsDirPath{};
	if (HRESULT ret = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, 0, &documentsDirPath); ret == S_OK)
	{
		std::wcout << L"Documents folder path: " << documentsDirPath << '\n';
	}
	else
	{
		spdlog::error("[SHGetKnownFolderPath] {0}", ret);
		return false;
	}

	ConfigDirPath = documentsDirPath + ConfigDirPath;
	ConfigFilePath = ConfigDirPath + ConfigFileName;
	std::wcout << "Config file path: " << ConfigFilePath << '\n';

	if (!fs::exists(ConfigFilePath))
	{
		try
		{
			fs::create_directories(ConfigDirPath);
			std::ofstream ofs(ConfigFilePath);
			ofs.close();
		}
		catch (const std::exception& e)
		{
			spdlog::error("[fs] {0}", e.what());
			return false;
		}

		std::wcout << L"Successfully created config file at " << ConfigFilePath << '\n';
	}

	return true;
}

bool ConfigManager::Load()
{
	// Load to config map
	if (!LoadToConfigMap())
	{
		return false;
	}

	LoadToServerConfigsCache();
	LoadToClientConfigsCache();

	return true;
}

bool ConfigManager::Save(bool sortAlphabetically) const
{
	std::ofstream ofs(ConfigFilePath, std::ofstream::out | std::ofstream::trunc);
	if (!ofs)
	{
		spdlog::error("[ofstream] Can't open Config file!");
		return false;
	}

	if (sortAlphabetically)
	{

	}
	else
	{
		for (const auto& [key, value] : ConfigMap)
		{
			ofs << key << ' ' << value << '\n';
		}
	}

	ofs.close();
	return true;
}

/////////////
// PRIVATE //
/////////////

bool ConfigManager::LoadToConfigMap()
{
	std::ifstream ifs(ConfigFilePath);
	if (!ifs.is_open())
	{
		return false;
	}

	std::string key{ };
	std::string value{ };

	std::string line;
	while (std::getline(ifs, line))
	{
		Utils::ToLowerStr(line);

		size_t keyStart = line.find_first_of(CONFIG_VALID_KEY_CHARS);
		size_t keyEnd = line.find_first_not_of(CONFIG_VALID_KEY_CHARS, keyStart + 1);
		if (keyStart == std::string::npos || keyEnd == std::string::npos)
		{
			continue;
		}

		size_t valueStart = line.find_first_not_of(CONFIG_WHITESPACES, keyEnd + 1);
		if (valueStart == std::string::npos || valueStart == line.length())
		{
			continue;
		}

		key = line.substr(keyStart, keyEnd);
		value = line.substr(valueStart);

		Add(key, value);
	}

	ifs.close();

	return true;
}

// Edit me for new config key
void ConfigManager::LoadToServerConfigsCache()
{
	// Esp
	Configs::Esp::Toggle = Get("esp_toggle", true, true);
	Configs::Esp::Box = Get("esp_box", true, true);
	Configs::Esp::Bone = Get("esp_bone", false, true);
	Configs::Esp::Snapline = Get("esp_snapline", false, true);
	Configs::Esp::Health = Get("esp_health", false, true);
	Configs::Esp::Chams = Get("esp_chams", false, true);
	// Items
	Configs::Esp::Items = Get("esp_items", false, true);

	Configs::Aimbot::Toggle = Get("aimbot_toggle", false, true);

	// Player patches
	Configs::Patches::GodMode = Get("patches_god_mode", false, true);
	Configs::Patches::FastRun = Get("patches_fast_run", false, true);

	// Gun patches
	Configs::Patches::InfAmmo = Get("patches_inf_ammo", false, true);
	Configs::Patches::NoRecoilAndCameraShake = Get("patches_no_recoil_and_camera_shake", false, true);
	Configs::Patches::NoMuzzelFlash = Get("patches_no_muzzel_flash", false, true);
	Configs::Patches::NoSpread = Get("patches_no_spread", false, true);
	Configs::Patches::HighROF = Get("patches_high_rof", false, true);
	Configs::Patches::InstantKill = Get("patches_instant_kill", false, true);
	Configs::Patches::InstantReload = Get("patches_instant_reload", false, true);

	// Economy patches
	Configs::Patches::InfSilverGoldCoins = Get("patches_inf_silver_gold_coins", false, true);

	// Misc patches
	Configs::Patches::HideFloatingDamage = Get("patches_hide_floating_damage", false, true);
}

void ConfigManager::LoadToClientConfigsCache() const
{
	// Esp
	g_PipeServer.SendConfig("esp_toggle", std::to_string(Configs::Esp::Toggle).c_str());
	g_PipeServer.SendConfig("esp_box", std::to_string(Configs::Esp::Box).c_str());
	g_PipeServer.SendConfig("esp_bone", std::to_string(Configs::Esp::Bone).c_str());
	g_PipeServer.SendConfig("esp_snapline", std::to_string(Configs::Esp::Snapline).c_str());
	g_PipeServer.SendConfig("esp_health", std::to_string(Configs::Esp::Health).c_str());
	g_PipeServer.SendConfig("esp_chams", std::to_string(Configs::Esp::Chams).c_str());
	// Items
	g_PipeServer.SendConfig("esp_items", std::to_string(Configs::Esp::Items).c_str());
	
	g_PipeServer.SendConfig("aimbot_toggle", std::to_string(Configs::Aimbot::Toggle).c_str());

	// Player patches
	g_PipeServer.SendConfig("patches_god_mode", std::to_string(Configs::Patches::GodMode).c_str());
	g_PipeServer.SendConfig("patches_fast_run", std::to_string(Configs::Patches::FastRun).c_str());

	// Gun patches
	g_PipeServer.SendConfig("patches_inf_ammo", std::to_string(Configs::Patches::InfAmmo).c_str());
	g_PipeServer.SendConfig("patches_no_recoil_and_camera_shake", std::to_string(Configs::Patches::NoRecoilAndCameraShake).c_str());
	g_PipeServer.SendConfig("patches_no_muzzel_flash", std::to_string(Configs::Patches::NoMuzzelFlash).c_str());
	g_PipeServer.SendConfig("patches_no_spread", std::to_string(Configs::Patches::NoSpread).c_str());
	g_PipeServer.SendConfig("patches_high_rof", std::to_string(Configs::Patches::HighROF).c_str());
	g_PipeServer.SendConfig("patches_instant_kill", std::to_string(Configs::Patches::InstantKill).c_str());
	g_PipeServer.SendConfig("patches_instant_reload", std::to_string(Configs::Patches::InstantReload).c_str());

	// Economy patches
	g_PipeServer.SendConfig("patches_inf_silver_gold_coins", std::to_string(Configs::Patches::InfSilverGoldCoins).c_str());

	// Misc patches
	g_PipeServer.SendConfig("patches_hide_floating_damage", std::to_string(Configs::Patches::HideFloatingDamage).c_str());
}


