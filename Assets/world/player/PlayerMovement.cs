using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEditor;
using UnityEngine;
using UnityEngine.AI;
using System.IO;

public class PlayerMovement : MonoBehaviour
{
    public UDPSend udpSend;
    private Animator anim;
    private NavMeshAgent navMeshAgent;
    private bool walking;

    // Use this for initialization
    void Awake()
    {
        anim = GetComponent<Animator>();
        navMeshAgent = GetComponent<NavMeshAgent>();
    }

    // Update is called once per frame
    void Update()
    {
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

                    FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(64);
                    FlatBuffers.StringOffset id = fbb.CreateString("Joe");
                    TransferObjects.PlayerLocation.StartPlayerLocation(fbb);
                    TransferObjects.PlayerLocation.AddId(fbb, id);
                    TransferObjects.PlayerLocation.AddPos(fbb, TransferObjects.Vec3.CreateVec3(fbb, hit.point.x, hit.point.y, hit.point.z));
                    FlatBuffers.Offset<TransferObjects.PlayerLocation> playerLocation = TransferObjects.PlayerLocation.EndPlayerLocation(fbb);

                    fbb.Finish(playerLocation.Value);
                    udpSend.send(fbb.DataBuffer.Data, fbb.DataBuffer.GetHashCode());
                }
            }
        }
        
        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            if (!navMeshAgent.hasPath || Mathf.Abs(navMeshAgent.velocity.sqrMagnitude) < float.Epsilon)
                walking = false;
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