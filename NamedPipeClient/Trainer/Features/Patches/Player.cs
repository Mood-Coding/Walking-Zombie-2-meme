using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WalkingZombie;

namespace mrBump.Trainer.Features.Patches
{
    [HarmonyPatch]
    static class Player
    {
        [HarmonyPrefix]
        [HarmonyPatch(typeof(CPlayerDamageHandler), nameof(CPlayerDamageHandler.DamageCallback))]
        static bool GodMode(ref bool __result)
        {
            if (Configuration.Patches.GodMode)
            {
                __result = false;
                // Skip execution of AddText method
                return false;
            }
            else
            {
                // Allow execution of AddText method 
                return true;
            }
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CFpsController), nameof(CFpsController.SpeedModificator), MethodType.Getter)]
        static bool FastRun(ref float __result)
        {
            if (Configuration.Patches.FastRun)
            {
                __result = 3.0f;
                // Skip execution of AddText method
                return false;
            }
            else
            {
                // Allow execution of AddText method 
                return true;
            }
        }
    }
}
