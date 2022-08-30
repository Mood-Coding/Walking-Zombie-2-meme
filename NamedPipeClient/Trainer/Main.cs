using UnityEngine;
using WalkingZombie;

namespace mrBump.Trainer
{
    public class Main : MonoBehaviour
    {
        private void Awkae()
        {
            // goodbye useless bitch
            CodeStage.AntiCheat.Detectors.InjectionDetector.Dispose();
            CodeStage.AntiCheat.Detectors.ObscuredCheatingDetector.Dispose();
            CodeStage.AntiCheat.Detectors.SpeedHackDetector.Dispose();
            CodeStage.AntiCheat.Detectors.TimeCheatingDetector.Dispose();
            CodeStage.AntiCheat.Detectors.WallHackDetector.Dispose();
        }

        private void Start()
        {
            if (!NamedPipeClient.Setup())
            {
                Loader.Unload();
            }

            StartCoroutine(Game.Data.ReadNecessaryObjects());

            if (!Features.Chams.Setup())
            {
                Loader.Unload();
            }

            Features.Patches.PatchManager.DoPatch();
        }

        private void OnDestroy()
        {
            NamedPipeClient.Unload();
        }

        private void Update()
        {
            Game.Data.GatherData();
        }

        // Can run several times per frame
        private void OnGUI()
        {
            // Forces OnGui to run once per frame
            // So Esp will be draw only once to save fps
            if (Event.current.type != EventType.Repaint) { return; }

            GUI.backgroundColor = Render.TransparentColor;
            GUI.Window(1337, new Rect(0f, 0f, Screen.width, Screen.height), new GUI.WindowFunction(DrawESP), "");
        }

        private static void DrawESP(int id)
        {
            if (id != 1337)
            {
                return;
            }

            foreach (Game.DataType.Enemy enemy in Game.Data.Enemies)
            {
                Features.Chams.ApplyChams(enemy);

                Features.Aimbot.FindNearestEnemy(Game.Data.MainCamera, enemy);

                Features.Esp.DrawEnemyEsp(enemy);

                // TODO visible check on chams
                 //Render.DrawString(GameUtils.StandardizeYPos(Camera.main.WorldToScreenPoint(enemy.AimPosition)), enemy.IsVisible ? "visible" : "hide");
            }

            Features.Aimbot.Aim(Game.Data.MainCamera);

            for (int i = 0; i < Game.Data.Items.Count; ++i)
            {
                Features.Esp.DrawItemEsp(Game.Data.Items[i]);
            }
        }
    }
}
