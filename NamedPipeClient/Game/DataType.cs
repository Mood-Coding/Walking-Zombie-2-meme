using UnityEngine;

namespace mrBump.Game.DataType
{
    public struct Enemy
    {
        public Enemy(Vector3 position, float health, Vector3[] bones, GameObject game_obj, Vector3 aim_position, bool is_visible)
        {
            Position = position;
            Health = health;
            Bones = bones;
            GameObj = game_obj;
            AimPosition = aim_position;
            IsVisible = is_visible;
        }

        public Vector3 Position { get; set; }
        public float Health { get; set; }
        public Vector3[] Bones { get; set; }
        public bool IsVisible { get; set; }

        public Vector3 AimPosition { get; set; }

        public GameObject GameObj { get; set; }
    }

    public struct Item
    {
        public Item(Vector3 position, string name)
        {
            Position = position;
            Name = name;
        }

        public Vector3 Position { get; set; }
        public string Name { get; set; }
    }
}
