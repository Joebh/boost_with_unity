using UnityEngine;
using UnityEditor;
using System.Collections;
using System.IO;
using System.Text;

public class ObjExporterScript
{
    public static int StartIndex = 0;

    public static void Start()
    {
    }
    public static void End()
    {
        StartIndex = 0;
    }


    public static string MeshToString(MeshFilter mf, Transform t)
    {
        Vector3 s = t.localScale;
        Vector3 p = t.localPosition;
        Quaternion r = t.localRotation;


        int numVertices = 0;
        Mesh m = mf.sharedMesh;
        if (!m)
        {
            return "####Error####";
        }
        Material[] mats = mf.GetComponent<Renderer>().sharedMaterials;

        StringBuilder sb = new StringBuilder();

        foreach (Vector3 vv in m.vertices)
        {
            Vector3 v = t.TransformPoint(vv);
            numVertices++;
            sb.Append(string.Format("v {0} {1} {2}\n", -v.x, v.y, v.z));
        }
        sb.Append("\n");
        foreach (Vector3 nn in m.normals)
        {
            Vector3 v = r * nn;
            sb.Append(string.Format("vn {0} {1} {2}\n", v.x, -v.y, -v.z));
        }
        sb.Append("\n");
        foreach (Vector3 v in m.uv)
        {
            sb.Append(string.Format("vt {0} {1}\n", v.x, v.y));
        }
        for (int material = 0; material < m.subMeshCount; material++)
        {
            sb.Append("\n");
            sb.Append("usemtl ").Append(mats[material].name).Append("\n");
            sb.Append("usemap ").Append(mats[material].name).Append("\n");

            int[] triangles = m.GetTriangles(material);
            for (int i = 0; i < triangles.Length; i += 3)
            {
                sb.Append(string.Format("f {2}/{2}/{2} {1}/{1}/{1} {0}/{0}/{0}\n",
                    triangles[i] + 1 + StartIndex, triangles[i + 1] + 1 + StartIndex, triangles[i + 2] + 1 + StartIndex));
            }
        }

        StartIndex += numVertices;
        return sb.ToString();
    }
}

public class ObjExporter : ScriptableObject
{

    public static string DoExport(Transform parent, int startIndex)
    {
        ObjExporterScript.Start();
        ObjExporterScript.StartIndex = startIndex;

        StringBuilder meshString = new StringBuilder();

        Vector3 originalPosition = parent.position;
        parent.position = Vector3.zero;

        for (int i = 0; i < parent.childCount; i++)
        {
            meshString.Append(processTransform(parent.GetChild(i)));
        }

        parent.position = originalPosition;

        ObjExporterScript.End();

        return meshString.ToString();
    }

    static StringBuilder processTransform(Transform t)
    {
        StringBuilder meshString = new StringBuilder();
        
        meshString.Append("o ").Append(t.name).Append("\n");

        MeshFilter mf = t.GetComponent<MeshFilter>();
        if (mf)
        {
            meshString.Append(ObjExporterScript.MeshToString(mf, t));
        }

        for (int i = 0; i < t.childCount; i++)
        {
            meshString.Append(processTransform(t.GetChild(i)));
        }

        return meshString;
    }
    
}