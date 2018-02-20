// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace TransferObjects
{

using global::System;
using global::FlatBuffers;

public struct Player : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static Player GetRootAsPlayer(ByteBuffer _bb) { return GetRootAsPlayer(_bb, new Player()); }
  public static Player GetRootAsPlayer(ByteBuffer _bb, Player obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public static bool PlayerBufferHasIdentifier(ByteBuffer _bb) { return Table.__has_identifier(_bb, "PDAT"); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public Player __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string Name { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
  public ArraySegment<byte>? GetNameBytes() { return __p.__vector_as_arraysegment(4); }
  public string Zone { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
  public ArraySegment<byte>? GetZoneBytes() { return __p.__vector_as_arraysegment(6); }
  public Vec3? Pos { get { int o = __p.__offset(8); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public Vec3? Dest { get { int o = __p.__offset(10); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartPlayer(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddZone(FlatBufferBuilder builder, StringOffset zoneOffset) { builder.AddOffset(1, zoneOffset.Value, 0); }
  public static void AddPos(FlatBufferBuilder builder, Offset<Vec3> posOffset) { builder.AddStruct(2, posOffset.Value, 0); }
  public static void AddDest(FlatBufferBuilder builder, Offset<Vec3> destOffset) { builder.AddStruct(3, destOffset.Value, 0); }
  public static Offset<Player> EndPlayer(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Player>(o);
  }
  public static void FinishPlayerBuffer(FlatBufferBuilder builder, Offset<Player> offset) { builder.Finish(offset.Value, "PDAT"); }
};


}
