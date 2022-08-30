using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace mrBump.Trainer.Features
{
    public static class Chams
    {
        // Methods
        public static bool Setup()
        {
            if (ChamsMaterial is null)
            {
                Debug.Log("[Chams.Setup] Can't find Hidden/Internal-Colored Material");
                return false;
            }

            ChamsMaterial.SetInt("_SrcBlend", (int)UnityEngine.Rendering.BlendMode.SrcAlpha);
            ChamsMaterial.SetInt("_DstBlend", 10);
            ChamsMaterial.SetInt("_Cull", (int)UnityEngine.Rendering.CullMode.Off);
            ChamsMaterial.SetInt("_ZWrite", 0);
            ChamsMaterial.SetInt("_ZTest", (int)UnityEngine.Rendering.CompareFunction.Always); // Render through walls.
            ChamsMaterial.SetColor("_Color", new Color(255, 255, 255, 255));

            Debug.Log("[Chams.Setup] Completed!");

            return true;
        }

        public static void ApplyChams(Game.DataType.Enemy enemy)
        {
            if (!Configuration.Esp.Chams)
            {
                return;
            }

            // Prepare
            Renderer[] renderers = enemy.GameObj.GetComponentsInChildren<Renderer>();
            if (renderers is null) { return; }

            Material material;

            // Renderer material based on Config Chams toggle state
            ChamsMaterial.SetColor("_Color", enemy.IsVisible ? new Color(255, 0, 0, 255) : new Color(255, 255, 255, 255));
            material = ChamsMaterial;

            // Both renderers[0] and renderers[1] have the same material, here we use renderers[0] to check
            if (renderers[0].material.color == ChamsMaterial.color)
            {
                return;
            }

            // Apply Chams
            foreach (Renderer render in renderers)
            {
                render.material = material;
                for (int i = 0; i < render.materials.Length; ++i)
                {
                    render.materials[i] = material;
                }
            }
        }

        // Properties
        private static readonly Material ChamsMaterial = new Material(Shader.Find("Hidden/Internal-Colored"))
        {
            hideFlags = HideFlags.DontSaveInEditor | HideFlags.HideInHierarchy,
        };
    }
}
