using Assets.networking.handlers;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadingWorld : MonoBehaviour {

    public UDPConnection udpConnection;

    public bool loggedIn_ = false;

    void UpdateFromServer(FlatBuffers.ByteBuffer bb)
    {
        TransferObjects.PlayerLogin pl = TransferObjects.PlayerLogin.GetRootAsPlayerLogin(bb);

        if (pl.Success)
        {
            loggedIn_ = true;
        }
    }

    void login(string username, string password)
    {
        FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(Constants.Network.BUFFER_SIZE);
        FlatBuffers.StringOffset fb_username = fbb.CreateString(username);
        FlatBuffers.StringOffset fb_password = fbb.CreateString(password);
        TransferObjects.PlayerLogin.StartPlayerLogin(fbb);
        TransferObjects.PlayerLogin.AddUsername(fbb, fb_username);
        TransferObjects.PlayerLogin.AddPassword(fbb, fb_password);
        FlatBuffers.Offset<TransferObjects.PlayerLogin> playerLogin = TransferObjects.PlayerLogin.EndPlayerLogin(fbb);
        TransferObjects.PlayerLogin.FinishPlayerLoginBuffer(fbb, playerLogin);

        udpConnection.send(fbb);
    }

	// Use this for initialization
	void Start () {
        login("joe", "asdfasdf");

        udpConnection.addRecvHandler("PLOG", new Handler(UpdateFromServer));
    }
	
	// Update is called once per frame
	void Update () {
		if (loggedIn_)
        {
            // switch scenes
            SceneManager.LoadScene("world", LoadSceneMode.Single);
        }
	}
}
