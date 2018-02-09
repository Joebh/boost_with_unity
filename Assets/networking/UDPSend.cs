using UnityEngine;
using System.Collections;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Assets.networking;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public class UDPSend : MonoBehaviour {
    
    // prefs
    private string IP;  // define in init
    private int port;  // define in init

    // "connection" things
    private IPEndPoint remoteEndPoint;
    private UdpClient client;
    private BinaryFormatter bf;
    private ArrayList sending;
    
    public void Start()
    {
        // define
        IP = "127.0.0.1";
        port = 33333;
        
        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();
        bf = new BinaryFormatter();
        sending = new ArrayList();
    }

    private void sendMessage(SendingStructure structure)
    {
        try
        {
            client.Send(structure.data, structure.data.Length, remoteEndPoint);
        }
        catch (Exception err)
        {
            print(err.ToString());
        }
    }

    // sending everything until recved
    void Update()
    {
        foreach (SendingStructure item in sending)
        {
            sendMessage(item);
        }
    }

    // sendData
    public void send(object sendingObject)
    {
        using (var ms = new MemoryStream())
        {
            bf.Serialize(ms, sendingObject);
            SendingStructure structure = new SendingStructure(ms.ToArray(), sendingObject.GetHashCode());

            sendMessage(structure);

            sending.Add(structure);

            // once sent wait for a recv message saying that this sending object was received

        }
    }

}
