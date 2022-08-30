using HarmonyLib;
using System.Reflection;
using UnityEngine;
using WalkingZombie;

namespace mrBump.Trainer.Features.Patches
{
    public static class PatchManager
    {
        public static void DoPatch()
        {
            var harmony = new Harmony("walking.zombie.2");
            harmony.PatchAll(Assembly.GetExecutingAssembly());

            Debug.Log("[PatchManager.DoPatch] Successed!");
        }
    }
}
