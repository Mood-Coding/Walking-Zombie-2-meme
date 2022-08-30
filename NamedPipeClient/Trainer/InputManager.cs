using UnityEngine;

namespace mrBump
{
    public static class InputManager
    {
        public static void Update()
        {
            // Input manager
            if (!Input.anyKey || !Input.anyKeyDown)
            {
                return;
            }

            if (Input.GetKeyDown(KeyCode.Delete))
            {
                Utils.Log("Unload");
                Loader.Unload();
            }
        }
    }
}
