// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace TransferObjects
{

using global::System;
using global::FlatBuffers;

public struct PlayerLocation : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static PlayerLocation GetRootAsPlayerLocation(ByteBuffer _bb) { return GetRootAsPlayerLocation(_bb, new PlayerLocation()); }
  public static PlayerLocation GetRootAsPlayerLocation(ByteBuffer _bb, PlayerLocation obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public PlayerLocation __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Vec3? Pos { get { int o = __p.__offset(4); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public string Id { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
  public ArraySegment<byte>? GetIdBytes() { return __p.__vector_as_arraysegment(6); }

  public static void StartPlayerLocation(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddPos(FlatBufferBuilder builder, Offset<Vec3> posOffset) { builder.AddStruct(0, posOffset.Value, 0); }
  public static void AddId(FlatBufferBuilder builder, StringOffset idOffset) { builder.AddOffset(1, idOffset.Value, 0); }
  public static Offset<PlayerLocation> EndPlayerLocation(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<PlayerLocation>(o);
  }
  public static void FinishPlayerLocationBuffer(FlatBufferBuilder builder, Offset<PlayerLocation> offset) { builder.Finish(offset.Value); }
};


}