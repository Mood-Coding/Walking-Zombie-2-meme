using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WalkingZombie;

namespace mrBump.Trainer.Features.Patches
{
    [HarmonyPatch(typeof(CPlayerInfo))]
    static class Economy
    {
        [HarmonyPrefix]
        [HarmonyPatch(nameof(CPlayerInfo.HasEnoughSilverCoins))]
        static bool AlwaysHasEnoughSilverCoins(ref bool __result)
        {
            if (Configuration.Patches.InfSilverGoldCoins)
            {
                __result = true;
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
        [HarmonyPatch(nameof(CPlayerInfo.HasEnoughGoldCoins))]
        static bool AlwaysHasEnoughGoldCoins(ref bool __result)
        {
            if (Configuration.Patches.InfSilverGoldCoins)
            {
                __result = true;
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
        [HarmonyPatch(nameof(CPlayerInfo.SpendCoinsSilver))]
        static bool NoSilverCoinsReduce()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.InfSilverGoldCoins;
        }

        [HarmonyPrefix]
        [HarmonyPatch(nameof(CPlayerInfo.SpendCoinsGold))]
        static bool NoGoldCoinsReduce()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.InfSilverGoldCoins;
        }
    }
}
