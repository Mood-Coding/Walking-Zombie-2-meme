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
            int id = enemy.GameObj.GetInstanceID();

            Renderer[] renderers = enemy.GameObj.GetComponentsInChildren<Renderer>();
            if (renderers is null) { return; }

            // Cache Renderer's original material if not cached
            if (!DefaultRendererMaterial.ContainsKey(id))
            {
                // Both renderers[0] and renderers[1] have the same material
                DefaultRendererMaterial.Add(id, renderers[0].material);
            }

            // Cache Chams toggle state if not cached
            if (!ChamsToggleState.ContainsKey(id))
            {
                ChamsToggleState.Add(id, null);
            }

            // Skip already applied Chams enemy
            if (ChamsToggleState[id] == Configuration.Esp.Chams)
            {
                return;
            }
            else
            {
                ChamsToggleState[id] = Configuration.Esp.Chams;
            }

            // Apply renderer material based on Config Chams toggle state
            Material material = Configuration.Esp.Chams ? ChamsMaterial : DefaultRendererMaterial[id];
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
        private static readonly Dictionary<int, bool?> ChamsToggleState = new Dictionary<int, bool?>();
        private static readonly Dictionary<int, Material> DefaultRendererMaterial = new Dictionary<int, Material>();
    }
}
