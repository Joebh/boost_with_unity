﻿using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEditor;
using UnityEngine;
using UnityEngine.AI;
using System.IO;
using System;
using Assets.networking.handlers;

public class PlayerMovement : MonoBehaviour
{
    private Animator anim;
    private NavMeshAgent navMeshAgent;
    private bool walking;

    private bool updateFromServer_ = false;
    private Vector3 updatedPositionFromServer_;

    private UDPConnection udpConnection = UDPConnection.getInstance();

    void UpdateFromServer(FlatBuffers.ByteBuffer bb)
    {
        TransferObjects.PlayerLocation pl = TransferObjects.PlayerLocation.GetRootAsPlayerLocation(bb);

        if (pl.Dest.HasValue)
        {
            updateFromServer_ = true;
            updatedPositionFromServer_ = new Vector3(pl.Dest.Value.X, pl.Dest.Value.Y, pl.Dest.Value.Z);
        }
    }

    // Use this for initialization
    void Awake()
    {
        anim = GetComponent<Animator>();
        navMeshAgent = GetComponent<NavMeshAgent>();

        udpConnection.addRecvHandler("PLOC", new Handler(UpdateFromServer));
    }

    // Update is called once per frame
    void Update()
    {
        if (updateFromServer_)
        {
            navMeshAgent.Warp(updatedPositionFromServer_);
            updateFromServer_ = false;
        }

        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Input.GetButtonDown("Fire2"))
        {
            if (Physics.Raycast(ray, out hit, 100))
            {
                if (hit.collider.CompareTag("Ground"))
                {
                    walking = true;
                    navMeshAgent.destination = hit.point;
                    navMeshAgent.isStopped = false;

                    FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(Constants.Network.BUFFER_SIZE);
                    //FlatBuffers.StringOffset id = fbb.CreateString("Joe");
                    TransferObjects.PlayerLocation.StartPlayerLocation(fbb);
                    //TransferObjects.PlayerLocation.AddId(fbb, id);

                    TransferObjects.PlayerLocation.AddPos(fbb, 
                        TransferObjects.Vec3.CreateVec3(fbb, 
                        gameObject.transform.position.x,
                        gameObject.transform.position.y,
                        gameObject.transform.position.z));

                    TransferObjects.PlayerLocation.AddDest(fbb, 
                        TransferObjects.Vec3.CreateVec3(
                            fbb, 
                            hit.point.x, 
                            hit.point.y, 
                            hit.point.z));

                    FlatBuffers.Offset<TransferObjects.PlayerLocation> playerLocation = TransferObjects.PlayerLocation.EndPlayerLocation(fbb);

                    TransferObjects.PlayerLocation.FinishPlayerLocationBuffer(fbb, playerLocation);

                    udpConnection.send(fbb);
                }
            }
        }

        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            if (!navMeshAgent.hasPath || Mathf.Abs(navMeshAgent.velocity.sqrMagnitude) < float.Epsilon)
            {
                walking = false;
            }
        }
        else {
            walking = true;
        }

        anim.SetBool("IsWalking", walking);
    }

    private void MoveAndShoot()
    {
        //    if (targetedEnemy == null)
        //        return;
        //    navMeshAgent.destination = targetedEnemy.position;
        //    if (navMeshAgent.remainingDistance >= shootDistance)
        //    {

        //        navMeshAgent.Resume();
        //        walking = true;
        //    }

        //    if (navMeshAgent.remainingDistance <= shootDistance)
        //    {

        //        transform.LookAt(targetedEnemy);
        //        Vector3 dirToShoot = targetedEnemy.transform.position - transform.position;
        //        if (Time.time > nextFire)
        //        {
        //            nextFire = Time.time + shootRate;
        //            shootingScript.Shoot(dirToShoot);
        //        }
        //        navMeshAgent.Stop();
        //        walking = false;
        //    }

    }
}