using UnityEngine;
using WalkingZombie;

namespace mrBump.Trainer.Features
{
    public static class Aimbot
    {
        public static void FindNearestEnemy(Camera camera, Game.DataType.Enemy enemy)
        {
            Vector3 enemyAimScreenPos = GameUtils.StandardizeYPos(camera.WorldToScreenPoint(enemy.AimPosition));
            float distanceToMiddleScreen = Vector2.Distance(enemyAimScreenPos, MiddleScreenPos());

            if (distanceToMiddleScreen < NearestDistance)
            {
                IsFound = true;
                NearestDistance = distanceToMiddleScreen;
                NearestEnemy = enemy;
            }
        }

        public static void Aim(Camera camera)
        {
            if (!Configuration.Aimbot.Toggle) { return; }
            
            if (IsFound)
            {
                // Line to Found Enemy
                Render.DrawLine(GameUtils.StandardizeYPos(camera.WorldToScreenPoint(NearestEnemy.AimPosition)), MiddleScreenPos(), 1);

                //Debug.Log("aim.... " + (aimVector).ToString());

                CFirstPersonCamera playerCamera = Object.FindObjectOfType<CFirstPersonCamera>();
                if (playerCamera != null)
                {
                    Transform cameraHolder = playerCamera.TransformCameraHolder;

                    if (Input.GetMouseButton(0) && IsFound && NearestEnemy.IsVisible)
                    {
                        cameraHolder.LookAt(NearestEnemy.AimPosition);
                    }
                    //Debug.Log("current " + cameraHolder.forward);
                }

                ResetNearestEnemy();
            }
        }

        private static void ResetNearestEnemy()
        {
            IsFound = false;
            NearestDistance = int.MaxValue;
        }

        public static Vector2 MiddleScreenPos()
        {
            return new Vector2(Screen.width / 2, Screen.height / 2);
        }

        // Properties
        private static bool IsFound { get; set; } = false;
        private static float NearestDistance { get; set; } = int.MaxValue;
        private static Game.DataType.Enemy NearestEnemy;
    }
}
