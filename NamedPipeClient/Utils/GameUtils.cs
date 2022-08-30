using System;
using UnityEngine;
using UnityEngine.SceneManagement;
using WalkingZombie;

namespace mrBump
{
    public static class GameUtils
    {
        public static float StandardizeYPos(float y_pos)
        {
            return Screen.height - y_pos;
        }

        public static Vector3 StandardizeYPos(Vector3 vector)
        {
            vector.y = Screen.height - vector.y;
            return vector;
        }

        // Game data
        public static void GetDontDestroyOnLoadScene(out Scene dontDestroyOnLoadScene)
        {
            GameObject temp = new GameObject();
            GameObject.DontDestroyOnLoad(temp);
            dontDestroyOnLoadScene = temp.scene;
            GameObject.DestroyImmediate(temp);
        }

        public static Scene GetDontDestroyOnLoadScene()
        {
            GameObject temp = new GameObject();
            GameObject.DontDestroyOnLoad(temp);
            Scene dontDestroyOnLoadScene = temp.scene;
            GameObject.DestroyImmediate(temp);

            return dontDestroyOnLoadScene; 
        }

        public static void GetDontDestroyOnLoadObjects(in Scene dontDestroyOnLoadScene, out GameObject[] dontDestroyOnLoadObjects)
        {
            dontDestroyOnLoadObjects = dontDestroyOnLoadScene.GetRootGameObjects();
        }

        public static GameObject[] GetDontDestroyOnLoadObjects(in Scene dontDestroyOnLoadScene)
        {
            return dontDestroyOnLoadScene.GetRootGameObjects();
        }

        public static void GetMainCamera(out Camera mainCamera)
        {
            mainCamera = Camera.main;
        }

        // GameObject data
        public static Vector3 GetObjectScreenPos(Camera main_camera, GameObject clone_enemy)
        {
            if (main_camera is null)
            {
                return Vector3.zero;
            }

            Vector3 screenPos = main_camera.WorldToScreenPoint(clone_enemy.transform.position);
            screenPos.y = StandardizeYPos(screenPos.y);

            return screenPos;
        }

        public static float GetEnemyHealth(GameObject clone_enemy)
        {
            CEnemyDamageHandler damageHandler = clone_enemy.GetComponent<CEnemyDamageHandler>();
            if (damageHandler is null)
            {
                return 0.0f;
            }

            return damageHandler.CurrentHealth;
        }

        public static Vector3[] GetEnemyBones(Camera main_camera, GameObject clone_enemy, out Vector3 aim_position)
        {
            aim_position = Vector3.zero;
            
            CEnemyBoneStructureController boneStruct = clone_enemy.GetComponent<CEnemyBoneStructureController>();
            if (boneStruct is null)
            {
                return new Vector3[0];
            }

            Vector3[] bones = new Vector3[6];

            for (int boneIdx = 0; boneIdx < 11; ++boneIdx)
            {
                if (boneStruct.Bones[boneIdx].name.Contains("Head"))
                {
                    aim_position = boneStruct.Bones[boneIdx].gameObject.transform.position;
                    bones[0] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
                else if (boneStruct.Bones[boneIdx].name.Contains("L Forearm"))
                {
                    bones[3] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
                else if (boneStruct.Bones[boneIdx].name.Contains("R Forearm"))
                {
                    bones[4] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
                else if (boneStruct.Bones[boneIdx].name.Contains("Pelvis"))
                {
                    bones[5] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
                else if (boneStruct.Bones[boneIdx].name.Contains("L Calf"))
                {
                    bones[1] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
                else if (boneStruct.Bones[boneIdx].name.Contains("R Calf"))
                {
                    bones[2] = main_camera.WorldToScreenPoint(boneStruct.Bones[boneIdx].gameObject.transform.position);
                }
            }

            for (int boneIdx = 0; boneIdx < bones.Length; ++boneIdx)
            {
                bones[boneIdx].y = StandardizeYPos(bones[boneIdx].y);
            }

            return bones;
        }

        // Checking
        public static bool IsMainEnemyObject(GameObject mainObj)
        {
            if (mainObj.name == "BanditChief" || mainObj.name == "BanditGirlKark98" || mainObj.name == "BanditLittlePerson"
                || mainObj.name == "BanditMachineGunner" || mainObj.name == "BanditPunk" || mainObj.name == "BlueGangMemberMaleAk47"
                || mainObj.name == "BossExperiment626" || mainObj.name == "BossZombieExperiment626" || mainObj.name == "BossIronCleaner" || mainObj.name == "BossKiller"
                || mainObj.name == "BossMissNature" || mainObj.name == "BossRevil" || mainObj.name == "BossRobotCj"
                || mainObj.name == "BossRocket" || mainObj.name == "BossSuperSoldier" || mainObj.name == "BossVincent"
                || mainObj.name == "BossYeti" || mainObj.name == "ChicaCompanion" || mainObj.name == "ChuckCompanion"
                || mainObj.name == "CutterFemaleKnife" || mainObj.name == "CutterFlamethrower" || mainObj.name == "CutterMale"
                || mainObj.name == "Frank" || mainObj.name == "GiantChicken" || mainObj.name == "HunterMaleGarandNorthtown"
                || mainObj.name == "JoanCompanion" || mainObj.name == "MayorKark98" || mainObj.name == "PhoebeBoss" || mainObj.name == "BossPhoebe"
                || mainObj.name == "PostmanCompanion" || mainObj.name == "SoldierFemale" || mainObj.name == "SoldierPrivate"
                || mainObj.name == "SoldierSergeant" || mainObj.name == "TargetTutorial" || mainObj.name == "Trader"
                || mainObj.name == "TraitorMaleGarand" || mainObj.name == "TrampFemaleGarand" || mainObj.name == "TrampFemaleKnife"
                || mainObj.name == "TrampMaleAk47" || mainObj.name == "TrampMaleGarand" || mainObj.name == "TrampMaleGrenadeLauncher"
                || mainObj.name == "TrampMaleKnife" || mainObj.name == "TrampMaleShotgun" || mainObj.name == "TrampNoWeaponMaleA"
                || mainObj.name == "TrampNoWeaponMaleC" || mainObj.name == "WaitressCompanion"
                || mainObj.name == "ZombieBat" || mainObj.name == "ZombieBear" || mainObj.name == "ZombieCheerleader"
                || mainObj.name == "ZombieDog" || mainObj.name == "ZombieFatBoy" || mainObj.name == "ZombieFirefighter"
                || mainObj.name == "ZombieHoodieMale" || mainObj.name == "ZombieHoodie" || mainObj.name == "ZombieJacketMale"
                || mainObj.name == "ZombieMilitary" || mainObj.name == "ZombieMother" || mainObj.name == "ZombiePoliceMan"
                || mainObj.name == "ZombiePrisoner" || mainObj.name == "ZombiePuker" || mainObj.name == "ZombiePukerPro"
                || mainObj.name == "ZombieQB" || mainObj.name == "ZombieQBGirlfriend" || mainObj.name == "ZombieRadioactive"
                || mainObj.name == "ZombieRat" || mainObj.name == "ZombieSchoolGirl" || mainObj.name == "ZombieScientist"
                || mainObj.name == "ZombieSecurityMan" || mainObj.name == "ZombieSkinny" || mainObj.name == "ZombieSpider" || mainObj.name == "ZombieSpiderMini"
                || mainObj.name == "ZombieTrasher" || mainObj.name == "ZombieWolf" || mainObj.name == "ZombieWorm")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool IsMainItemObject(GameObject mainObj)
        {
            if (mainObj.name == "LocationData")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool IsChildItemObject(GameObject childObj)
        {
            if (childObj.name == "TreasureChest(Clone)")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool IsVisible(Camera camera, Vector3 destination_pos)
        {
            var dir = destination_pos - camera.transform.position;
            if (Physics.Raycast(camera.transform.position, dir.normalized, out RaycastHit raycast, float.PositiveInfinity, Physics.AllLayers))
            {
                if (raycast.transform.name.Contains("E-")
                    || raycast.transform.name == "HeadAffinity")
                {
                    return true;
                }
            }

            return false;
        }

        //public static bool IsVisible(Camera camera, Game.DataType.Enemy enemy)
        //{
        //    var dir = enemy.AimPosition - Camera.main.transform.position;
        //    if (Physics.Raycast(Camera.main.transform.position, dir.normalized, out RaycastHit raycast, float.PositiveInfinity, Physics.AllLayers))
        //    {
        //        if (raycast.transform.name.Contains("E-")
        //            || raycast.transform.name == "HeadAffinity")
        //        {
        //            return true;
        //        }
        //    }

        //    return false;
        //}

        // Miscs
        public static string GetPath(this Transform current)
        {
            if (current.parent == null)
                return "/" + current.name;
            return current.parent.GetPath() + "/" + current.name;
        }
    }
}
