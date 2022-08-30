#pragma once

#ifndef CONFIGS_H
#define CONFIGS_H

namespace Configs
{
	namespace Esp
	{
		// Enemy
		extern bool Toggle;
		extern bool Box;
		extern bool Bone;
		extern bool Snapline;
		extern bool Health;
		extern bool Chams;
		// Items
		extern bool Items;
	}

	namespace Aimbot
	{
		extern bool Toggle;
	}

	namespace Patches
	{
		// Player patches
		extern bool GodMode;
		extern bool FastRun;

		// Gun patches
		extern bool InfAmmo;
		extern bool NoRecoilAndCameraShake;
		extern bool NoMuzzelFlash;
		extern bool NoSpread;
		extern bool HighROF;
		extern bool InstantKill;
		extern bool InstantReload;
		
		// Economy patches
		extern bool InfSilverGoldCoins;

		// Misc patches
		extern bool HideFloatingDamage;
	}
}

#endif