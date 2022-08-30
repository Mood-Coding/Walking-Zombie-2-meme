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
    static class Gun
    {
        [HarmonyPrefix]
        [HarmonyPatch(typeof(CArmory), nameof(CArmory.Fire))]
        static bool InfAmmo()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.InfAmmo;
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CArmory), nameof(CArmory.CanStartFire))]
        static bool InfAmmo2(ref bool __result)
        {
            if (Configuration.Patches.InfAmmo)
            {
                __result = true;
                // Skip execution of get_IsInfinityAmmoStock method
                return false;
            }
            else
            {
                // Allow execution of get_IsInfinityAmmoStock method 
                return true;
            }
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CConfigWeaponItem), nameof(CConfigWeaponItem.IsInfinityAmmoStock), MethodType.Getter)]
        static bool InfAmmo3(ref bool __result)
        {
            if (Configuration.Patches.InfAmmo)
            {
                __result = true;
                // Skip execution of get_IsInfinityAmmoStock method
                return false;
            }
            else
            {
                // Allow execution of get_IsInfinityAmmoStock method 
                return true;
            }
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CFpsWeaponFireEffects), nameof(CFpsWeaponFireEffects.DoFireCameraEffects))]
        static bool NoRecoilAndCameraShake()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.NoRecoilAndCameraShake;
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CFpsWeaponFireEffects), nameof(CFpsWeaponFireEffects.CreateMuzzle))]
        static bool NoMuzzelFlash()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.NoMuzzelFlash;
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CFpsWeaponSpreadModificator), nameof(CFpsWeaponSpreadModificator.OnAttack))]
        static bool NoSpread()
        {
            // return true = Allow execution of AddText method 
            // return false = Skip execution of AddText method
            return !Configuration.Patches.NoSpread;
        }

        [HarmonyPrefix]
        [HarmonyPatch(typeof(CPlayerCombatValues), nameof(CPlayerCombatValues.GetWeaponAttackRate))]
        static bool HighRof(ref float __result)
        {
            if (Configuration.Patches.HighROF)
            {
                __result = 0.05f;
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
        [HarmonyPatch(typeof(CPlayerCombatValues), nameof(CPlayerCombatValues.GetWeaponDamage))]
        static bool InstantKill(ref float __result)
        {
            if (Configuration.Patches.InstantKill)
            {
                __result = 100000.0f;
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
        [HarmonyPatch(typeof(CPlayerCombatValues), nameof(CPlayerCombatValues.GetWeaponReloadTime))]
        static bool InstantReload(ref float __result)
        {
            if (Configuration.Patches.InstantReload)
            {
                __result = 0.0f;
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
