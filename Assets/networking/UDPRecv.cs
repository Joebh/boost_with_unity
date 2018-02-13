using UnityEngine;
using System.Collections;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Collections.Generic;

public class UDPRecv : MonoBehaviour
{

    private UdpClient client;

    public delegate void PlayerLocationHandler(TransferObjects.PlayerLocation pl);
    private static List<PlayerLocationHandler> plHandlers = new List<PlayerLocationHandler>();

    static void OnUdpData(IAsyncResult result)
    {
        // this is what had been passed into BeginReceive as the second parameter:
        UdpClient socket = result.AsyncState as UdpClient;

        // points towards whoever had sent the message:
        IPEndPoint source = new IPEndPoint(0, 0);

        // get the actual message and fill out the source:
        byte[] message = socket.EndReceive(result, ref source);

        var bb = new FlatBuffers.ByteBuffer(message);

        if (TransferObjects.PlayerLocation.PlayerLocationBufferHasIdentifier(bb))
        {
            TransferObjects.PlayerLocation pl = TransferObjects.PlayerLocation.GetRootAsPlayerLocation(bb);

            foreach (PlayerLocationHandler handler in plHandlers) // Loop through List with foreach
            {
                handler(pl);
            }
        }

        // schedule the next receive operation once reading is done:
        socket.BeginReceive(new AsyncCallback(OnUdpData), socket);
    }

    public void Start()
    {
        client = new UdpClient();
        client.BeginReceive(new AsyncCallback(OnUdpData), client);

        addHook();
    }


    // sending everything until recved
    void Update()
    {

    }

    void test(TransferObjects.PlayerLocation pl)
    {
        Debug.Log(pl.Id);
    }

    void addHook()
    {
        PlayerLocationHandler handler = new PlayerLocationHandler(test);
        plHandlers.Add(handler);
    }

}
