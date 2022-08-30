using UnityEngine;

namespace mrBump
{
    public static class Loader
    {
        public static GameObject Meme { get; set; } = new GameObject();

        public static void Load()
        {
            Meme.transform.parent = null;
            Meme.AddComponent<Trainer.Main>();
            Object.DontDestroyOnLoad(Meme);
        }

        public static void Unload()
        {
            Debug.Log("Unloading");
            Object.Destroy(Meme);
        }
    }
}