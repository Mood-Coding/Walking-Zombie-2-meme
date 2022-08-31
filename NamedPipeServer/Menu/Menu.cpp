#include "pch.h"
#include "Menu.h"

Menu g_Menu;

void Menu::Draw() const
{
	if (!IsShow) { return; }

	ImGui::Begin("Hello, world!");

	if (ImGui::CollapsingHeader("Esp", ImGuiTreeNodeFlags_None))
	{
		if (ImGui::Checkbox("Toggle Esp", &Configs::Esp::Toggle))
		{
			g_ConfigManager.Set("esp_toggle", Configs::Esp::Toggle, true);
			g_PipeServer.SendConfig("esp_toggle", std::to_string(Configs::Esp::Toggle).c_str());
		}

		if (ImGui::Checkbox("Box", &Configs::Esp::Box))
		{
			g_ConfigManager.Set("esp_box", Configs::Esp::Box, true);
			g_PipeServer.SendConfig("esp_box", std::to_string(Configs::Esp::Box).c_str());
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("Bone", &Configs::Esp::Bone))
		{
			g_ConfigManager.Set("esp_bone", Configs::Esp::Bone, true);
			g_PipeServer.SendConfig("esp_bone", std::to_string(Configs::Esp::Bone).c_str());
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("Snapline", &Configs::Esp::Snapline))
		{
			g_ConfigManager.Set("esp_snapline", Configs::Esp::Snapline, true);
			g_PipeServer.SendConfig("esp_snapline", std::to_string(Configs::Esp::Snapline).c_str());
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("Health", &Configs::Esp::Health))
		{
			g_ConfigManager.Set("esp_health", Configs::Esp::Health, true);
			g_PipeServer.SendConfig("esp_health", std::to_string(Configs::Esp::Health).c_str());
		}

		if (ImGui::Checkbox("Chams (Buggy)", &Configs::Esp::Chams))
		{
			g_ConfigManager.Set("esp_chams", Configs::Esp::Chams, true);
			g_PipeServer.SendConfig("esp_chams", std::to_string(Configs::Esp::Chams).c_str());
		}

		if (ImGui::Checkbox("Items", &Configs::Esp::Items))
		{
			g_ConfigManager.Set("esp_items", Configs::Esp::Items, true);
			g_PipeServer.SendConfig("esp_items", std::to_string(Configs::Esp::Items).c_str());
		}
	}

	if (ImGui::CollapsingHeader("Aimbot", ImGuiTreeNodeFlags_None))
	{
		// Aimbot
		if (ImGui::Checkbox("Toggle Aimbot", &Configs::Aimbot::Toggle))
		{
			g_ConfigManager.Set("aimbot_toggle", Configs::Aimbot::Toggle, true);
			g_PipeServer.SendConfig("aimbot_toggle", std::to_string(Configs::Aimbot::Toggle).c_str());
		}
	}

	if (ImGui::CollapsingHeader("Patches", ImGuiTreeNodeFlags_None))
	{
		ImGui::Text("Player patches");
		if (ImGui::Checkbox("God Mode", &Configs::Patches::GodMode))
		{
			g_ConfigManager.Set("patches_god_mode", Configs::Patches::GodMode, true);
			g_PipeServer.SendConfig("patches_god_mode", std::to_string(Configs::Patches::GodMode).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Fast run", &Configs::Patches::FastRun))
		{
			g_ConfigManager.Set("patches_fast_run", Configs::Patches::FastRun, true);
			g_PipeServer.SendConfig("patches_fast_run", std::to_string(Configs::Patches::FastRun).c_str());
		}

		ImGui::Text("Gun patches");
		if (ImGui::Checkbox("No Recoil and Camera shake", &Configs::Patches::NoRecoilAndCameraShake))
		{
			g_ConfigManager.Set("patches_no_recoil_and_camera_shake", Configs::Patches::NoRecoilAndCameraShake, true);
			g_PipeServer.SendConfig("patches_no_recoil_and_camera_shake", std::to_string(Configs::Patches::NoRecoilAndCameraShake).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Inf ammo", &Configs::Patches::InfAmmo))
		{
			g_ConfigManager.Set("patches_inf_ammo", Configs::Patches::InfAmmo, true);
			g_PipeServer.SendConfig("patches_inf_ammo", std::to_string(Configs::Patches::InfAmmo).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("No muzzel flash", &Configs::Patches::NoMuzzelFlash))
		{
			g_ConfigManager.Set("patches_no_muzzel_flash", Configs::Patches::NoMuzzelFlash, true);
			g_PipeServer.SendConfig("patches_no_muzzel_flash", std::to_string(Configs::Patches::NoMuzzelFlash).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("No spread", &Configs::Patches::NoSpread))
		{
			g_ConfigManager.Set("patches_no_spread", Configs::Patches::NoSpread, true);
			g_PipeServer.SendConfig("patches_no_spread", std::to_string(Configs::Patches::NoSpread).c_str());
		}

		if (ImGui::Checkbox("High ROF", &Configs::Patches::HighROF))
		{
			g_ConfigManager.Set("patches_high_rof", Configs::Patches::HighROF, true);
			g_PipeServer.SendConfig("patches_high_rof", std::to_string(Configs::Patches::HighROF).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Instatn kill", &Configs::Patches::InstantKill))
		{
			g_ConfigManager.Set("patches_instant_kill", Configs::Patches::InstantKill, true);
			g_PipeServer.SendConfig("patches_instant_kill", std::to_string(Configs::Patches::InstantKill).c_str());
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Instant Reload", &Configs::Patches::InstantReload))
		{
			g_ConfigManager.Set("patches_instant_reload", Configs::Patches::InstantReload, true);
			g_PipeServer.SendConfig("patches_instant_reload", std::to_string(Configs::Patches::InstantReload).c_str());
		}

		ImGui::Text("Economy patches");
		if (ImGui::Checkbox("Inf Silver/Gold coins", &Configs::Patches::InfSilverGoldCoins))
		{
			g_ConfigManager.Set("patches_inf_silver_gold_coins", Configs::Patches::InfSilverGoldCoins, true);
			g_PipeServer.SendConfig("patches_inf_silver_gold_coins", std::to_string(Configs::Patches::InfSilverGoldCoins).c_str());
		}

		ImGui::Text("Misc patches");
		if (ImGui::Checkbox("Hide floating damage", &Configs::Patches::HideFloatingDamage))
		{
			g_ConfigManager.Set("patches_hide_floating_damage", Configs::Patches::HideFloatingDamage, true);
			g_PipeServer.SendConfig("patches_hide_floating_damage", std::to_string(Configs::Patches::HideFloatingDamage).c_str());
		}
	}

	

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}