using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Assets.entering_world
{

    public class UDPReceive : MonoBehaviour
    {

        // receiving Thread
        Thread receiveThread;

        // udpclient object
        UdpClient client;

        // public
        public string IP = "127.0.0.1"; // default local
        public int port; // define > init

        // infos
        public string lastReceivedUDPPacket = "";
        public string allReceivedUDPPackets = ""; // clean up this from time to time!

        // start from unity3d
        public void Start()
        {
            init();
        }

        // OnGUI
        void OnGUI()
        {
            Rect rectObj = new Rect(40, 10, 200, 400);
            GUIStyle style = new GUIStyle();
            style.alignment = TextAnchor.UpperLeft;
            GUI.Box(rectObj, "# UDPReceive\n" + IP + " " + port + " #\n"
                        + "shell> nc -u" + IP + " " + " : " + port + " \n"
                        + "\nLast Packet: \n" + lastReceivedUDPPacket
                        + "\n\nAll Messages: \n" + allReceivedUDPPackets
                    , style);
        }

        // init
        private void init()
        {
            port = 0;
            receiveThread = new Thread(
                new ThreadStart(ReceiveData));
            receiveThread.IsBackground = true;
            receiveThread.Start();
        }

        void OnApplicationQuit()
        {
            receiveThread.Abort();
        }

        // receive thread
        private void ReceiveData()
        {
            client = new UdpClient(port);
            Console.WriteLine("UDP port : " + ((IPEndPoint)client.Client.LocalEndPoint).Port.ToString());
            while (true)
            {
                try
                {
                    byte[] buffer = Encoding.UTF8.GetBytes("a");
                    client.Send(buffer, buffer.Length, new IPEndPoint(IPAddress.Parse(IP), port));

                    IPEndPoint anyIP = new IPEndPoint(IPAddress.Any, 0);
                    byte[] data = client.Receive(ref anyIP);
                    string text = Encoding.UTF8.GetString(data);

                    print(">> " + text);

                    lastReceivedUDPPacket = text;

                    allReceivedUDPPackets = allReceivedUDPPackets + text;

                }
                catch (Exception err)
                {
                    print(err);
                    print(err.ToString());
                }
            }
        }

        // getLatestUDPPacket
        // cleans up the rest
        public string getLatestUDPPacket()
        {
            allReceivedUDPPackets = "";
            return lastReceivedUDPPacket;
        }
    }
}
