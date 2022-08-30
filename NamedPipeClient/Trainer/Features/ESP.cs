using UnityEngine;

namespace mrBump.Trainer.Features
{
    public static class Esp
    {
        public static void DrawEnemyEsp(in Game.DataType.Enemy enemy)
        {
            if (enemy.Position.z < 1) { return;  }

            if (Configuration.Esp.Toggle)
            {
                if (Configuration.Esp.Bone)
                {
                    DrawBone(enemy);
                }

                if (Configuration.Esp.Box)
                {
                    DrawBox(enemy);
                }

                if (Configuration.Esp.Snapline)
                {
                    DrawSnapline(enemy);
                }

                if (Configuration.Esp.Health)
                {
                    DrawHealth(enemy);
                }
            }
        }

        public static void DrawItemEsp(in Game.DataType.Item item)
        {
            if (Configuration.Esp.Items)
            {
                DrawName(item);
            }
        }

        // Helper methods
        private static void DrawBone(in Game.DataType.Enemy enemy)
        {
            Render.DrawLine(enemy.Bones[0], enemy.Bones[5], 1);
            Render.DrawLine(enemy.Bones[0], enemy.Bones[3], 1);
            Render.DrawLine(enemy.Bones[0], enemy.Bones[4], 1);
            Render.DrawLine(enemy.Bones[5], enemy.Bones[2], 1);
            Render.DrawLine(enemy.Bones[5], enemy.Bones[1], 1);
        }

        private static void DrawBox(in Game.DataType.Enemy enemy)
        {
            Vector3 headpos = enemy.Bones[0];
            Vector3 footpos = enemy.Position;

            float height = footpos.y - headpos.y;
            float widthOffset = 2f;
            float width = height / widthOffset;

            Render.DrawBox(new Vector2(headpos.x - (width / 2), headpos.y), new Vector2(width, height), 1.0f);
        }

        private static void DrawSnapline(in Game.DataType.Enemy enemy)
        {
            Render.DrawLine(new Vector2(Screen.width / 2, Screen.height / 2), enemy.Position, 1.0f);
        }

        private static void DrawHealth(in Game.DataType.Enemy enemy)
        {
            Render.DrawString(enemy.Position + new Vector3(0, 2, 0), enemy.Health.ToString(), true);
        }

        private static void DrawName(in Game.DataType.Item item)
        {
            Render.DrawString(item.Position, item.Name, true);
        }
    }
}
