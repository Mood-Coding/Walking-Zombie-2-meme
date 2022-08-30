using System;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using System.Diagnostics;
using UnityEngine.SceneManagement;
using WalkingZombie;
using System.Collections;

namespace mrBump.Game
{
    public static class Data
    {
        // Methods
        public static void GatherData()
        {
            if (MainCamera is null || DontDestroyOnLoadObjects is null) { return; }

            Enemies.Clear();
            ReadEnemies();

            Items.Clear();
            ReadItems();
        }

        public static IEnumerator ReadNecessaryObjects()
        {
            DontDestroyOnLoadScene = GameUtils.GetDontDestroyOnLoadScene();

            while (true)
            {
                yield return new WaitForSeconds(3.0f);

                DontDestroyOnLoadObjects = GameUtils.GetDontDestroyOnLoadObjects(DontDestroyOnLoadScene);
                MainCamera = Camera.main;
            }
        }

        private static void ReadEnemies()
        {
            try
            {
                // Iterate through all DontDestroyOnLoad Objects and find all Enemy objects
                foreach (var DDOLObject in DontDestroyOnLoadObjects)
                {
                    for (int childIdx = 0; childIdx < DDOLObject.transform.childCount; ++childIdx)
                    {
                        GameObject mainEnemy = DDOLObject.transform.GetChild(childIdx).gameObject;

                        if (!GameUtils.IsMainEnemyObject(mainEnemy)) { continue; }

                        for (int cloneIdx = 0; cloneIdx < mainEnemy.transform.childCount; ++cloneIdx)
                        {
                            GameObject cloneEnemy = mainEnemy.transform.GetChild(cloneIdx).gameObject;

                            if (!cloneEnemy.activeInHierarchy) { continue; }

                            Vector3 screenPos = GameUtils.GetObjectScreenPos(MainCamera, cloneEnemy);
                            if (screenPos.z <= 0) { continue; }

                            float currentHealth = GameUtils.GetEnemyHealth(cloneEnemy);
                            if (currentHealth <= 0) { continue; }

                            Vector3[] bones = GameUtils.GetEnemyBones(MainCamera, cloneEnemy, out Vector3 aimPosition);
                            if (bones.Length == 0) { continue; }

                            bool isVisible = GameUtils.IsVisible(MainCamera, aimPosition);

                            Enemies.Add(new DataType.Enemy(screenPos, currentHealth, bones, cloneEnemy, aimPosition, isVisible));
                        }
                    }
                }
            }
            catch (Exception e)
            {
                UnityEngine.Debug.Log("[ReadEnemies]");
                UnityEngine.Debug.Log(e.ToString());
                UnityEngine.Debug.Log(e.StackTrace);
                UnityEngine.Debug.Log(e.TargetSite);
            }
        }

        private static void ReadItems()
        {
            try
            {
                ActiveScene = SceneManager.GetActiveScene();
                
                GameObject[] sceneGameObj = ActiveScene.GetRootGameObjects();
                if (sceneGameObj is null) { return; }

                foreach (var gameObj in sceneGameObj)
                {
                    if (gameObj is null)
                    {
                        continue;
                    }

                    if (gameObj.name == "LocationData")
                    {
                        Transform treasureChestTransform = gameObj.transform.Find("TreasureChest(Clone)");

                        if (treasureChestTransform != null)
                        {
                            Vector3 screenPos = GameUtils.GetObjectScreenPos(MainCamera, treasureChestTransform.gameObject);
                            Items.Add(new DataType.Item(screenPos, "Treasure Chest"));
                        }
                    }
                }
            }
            catch (Exception e)
            {
                UnityEngine.Debug.Log("[ReadItems]");
                UnityEngine.Debug.Log(e.ToString());
                UnityEngine.Debug.Log(e.StackTrace);
                UnityEngine.Debug.Log(e.TargetSite);
            }
        }

        // Properties
        public static List<DataType.Enemy> Enemies { get; set; } = new List<DataType.Enemy>();
        public static List<DataType.Item> Items { get; set; } = new List<DataType.Item>();
        public static Camera MainCamera { get; set; }

        private static Scene DontDestroyOnLoadScene { get; set; }
        private static Scene ActiveScene { get; set; }
        private static GameObject[] DontDestroyOnLoadObjects { get; set; }
    }
}
