using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using WalkingZombie;

namespace mrBump.Trainer.Features.Patches
{
    [HarmonyPatch]
    static class Misc
    {
        [HarmonyPrefix]
        [HarmonyPatch(typeof(CFloatingTextController), nameof(CFloatingTextController.AddText))]
        static bool HideFloatingDamagePrefix()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.HideFloatingDamage;
        }
    }
}
