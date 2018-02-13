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
using Assets.networking.handlers;

public class UDPConnection : MonoBehaviour
{

    // prefs
    private string IP;  // define in init
    private int port;  // define in init

    // "connection" things
    private IPEndPoint remoteEndPoint;
    private UdpClient client;
    
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
        // define
        IP = "127.0.0.1";
        port = 33333;

        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();
        
        client.BeginReceive(new AsyncCallback(OnUdpData), client);
    }
    
    void Update()
    {
        
    }

    // sendData
    public void send(byte[] sendingBytes)
    {
        try
        {
            int sent = 0;
            do {
                sent = client.Send(sendingBytes, sendingBytes.Length, remoteEndPoint);
            } while (sent == 0);
        }
        catch (Exception err)
        {
            print(err.ToString());
        }
    }
    
    public void addRecvHandler(PlayerLocationHandler handler)
    {
        plHandlers.Add(handler);
    }

}
