using UnityEngine;
using System.Collections;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public class UDPSend : MonoBehaviour
{

    // prefs
    private string IP;  // define in init
    private int port;  // define in init

    // "connection" things
    private IPEndPoint remoteEndPoint;
    private UdpClient client;

    public void Start()
    {
        // define
        IP = "127.0.0.1";
        port = 33333;

        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();
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

}
