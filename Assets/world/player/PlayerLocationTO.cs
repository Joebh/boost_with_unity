using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class PlayerLocationTO {

    private int playerId;
    private float x, y, z;
    
    public PlayerLocationTO(int playerId, Vector3 location)
    {
        this.playerId = playerId;
        this.x = location.x;
        this.y = location.y;
        this.z = location.z;
    }
}
