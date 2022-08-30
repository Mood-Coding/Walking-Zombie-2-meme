using System;
using UnityEngine;

namespace mrBump
{
    public class Configuration
    {
        // Edit me for new config key
        public static void SetConfigValue(string config, string value)
        {
            // config is not null-terminated string I so use contains.

            // Player Esp
            if (config.Contains("esp_toggle"))
            {
                Esp.Toggle = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("esp_bone"))
            {
                Esp.Bone = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("esp_box"))
            {
                Esp.Box = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("esp_snapline"))
            {
                Esp.Snapline = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("esp_health"))
            {
                Esp.Health = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("esp_chams"))
            {
                Esp.Chams = Convert.ToBoolean(Convert.ToInt32(value));
            }
            // Items Esp
            else if (config.Contains("esp_items"))
            {
                Esp.Items = Convert.ToBoolean(Convert.ToInt32(value));
            }

            // Aimbot
            else if (config.Contains("aimbot_toggle"))
            {
                Aimbot.Toggle = Convert.ToBoolean(Convert.ToInt32(value));
            }

            // Player patches
            else if (config.Contains("patches_god_mode"))
            {
                Patches.GodMode = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_fast_run"))
            {
                Patches.FastRun = Convert.ToBoolean(Convert.ToInt32(value));
            }
            // Gun patches
            else if (config.Contains("patches_inf_ammo"))
            {
                Patches.InfAmmo = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_no_recoil_and_camera_shake"))
            {
                Patches.NoRecoilAndCameraShake = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_no_muzzel_flash"))
            {
                Patches.NoMuzzelFlash = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_no_spread"))
            {
                Patches.NoSpread = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_high_rof"))
            {
                Patches.HighROF = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_instant_kill"))
            {
                Patches.InstantKill = Convert.ToBoolean(Convert.ToInt32(value));
            }
            else if (config.Contains("patches_instant_reload"))
            {
                Patches.InstantReload = Convert.ToBoolean(Convert.ToInt32(value));
            }
            // Economy patches
            else if (config.Contains("patches_inf_silver_gold_coins"))
            {
                Patches.InfSilverGoldCoins = Convert.ToBoolean(Convert.ToInt32(value));
            }
            // Miscs patches
            else if (config.Contains("patches_hide_floating_damage"))
            {
                Patches.HideFloatingDamage = Convert.ToBoolean(Convert.ToInt32(value));
            }
        }

        public static class Esp
        {
            public static bool Toggle { get; set; } = false;
            public static bool Box { get; set; } = false;
            public static bool Bone { get; set; } = false;
            public static bool Snapline { get; set; } = false;
            public static bool Health { get; set; } = false;
            public static bool Chams { get; set; } = false;

            public static bool Items { get; set; } = false;
        }

        public static class Aimbot
        {
            public static bool Toggle { get; set; } = false;
        }

        public static class Patches
        {
            // Player
            public static bool GodMode { get; set; } = false;
            public static bool FastRun { get; set; } = false;

            // Gun
            public static bool InfAmmo { get; set; } = false;
            public static bool NoRecoilAndCameraShake { get; set; } = false;
            public static bool NoMuzzelFlash { get; set; } = false;
            public static bool NoSpread { get; set; } = false;
            public static bool HighROF { get; set; } = false;
            public static bool InstantKill { get; set; } = false;
            public static bool InstantReload { get; set; } = false;

            // Economy
            public static bool InfSilverGoldCoins { get; set; } = false;

            // Misc
            public static bool HideFloatingDamage { get; set; } = false;
        }
    }
}
