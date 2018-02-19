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

public class UDPConnection
{
    private static UDPConnection instance = null;

    public static UDPConnection getInstance()
    {
        if (instance == null)
        {
            instance = new UDPConnection();
        }

        return instance;
    }

    public UDPConnection()
    {
        // define
        IP = "127.0.0.1";
        port = 33333;

        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();

        client.BeginReceive(new AsyncCallback(OnUdpData), client);
    }

    // prefs
    private string IP;  // define in init
    private int port;  // define in init

    // "connection" things
    private IPEndPoint remoteEndPoint;
    private UdpClient client;

    private Dictionary<string, List<Handler>> handlerDictionary = new Dictionary<string, List<Handler>>();

    void runHandlers(string key, FlatBuffers.ByteBuffer bb)
    {
        List<Handler> handlers = handlerDictionary[key];

        foreach (Handler handler in handlers) // Loop through List with foreach
        {
            handler(bb);
        }

    }

    void OnUdpData(IAsyncResult result)
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
            runHandlers("PLOC", bb);
        }
        if (TransferObjects.PlayerLogin.PlayerLoginBufferHasIdentifier(bb))
        {
            runHandlers("PLOG", bb);
        }

        // schedule the next receive operation once reading is done:
        socket.BeginReceive(new AsyncCallback(OnUdpData), socket);
    }
        
    void OnDestroy()
    {
        client.Close();
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
            //print(err.ToString());
        }
    }

    public void send(FlatBuffers.FlatBufferBuilder fbb)
    {
        byte[] dst = new byte[fbb.DataBuffer.Length - fbb.DataBuffer.Position];
        Array.Copy(fbb.DataBuffer.Data, fbb.DataBuffer.Position, dst, 0, dst.Length);
        send(dst);
    }
    
    public void addRecvHandler(string key, Handler handler)
    {
        if (!handlerDictionary.ContainsKey(key))
        {
            handlerDictionary[key] = new List<Handler>();
        }
        List<Handler> handlers = handlerDictionary[key];
        handlers.Add(handler);
    }

}
