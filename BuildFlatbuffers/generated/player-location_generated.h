// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PLAYERLOCATION_NETWORKING_H_
#define FLATBUFFERS_GENERATED_PLAYERLOCATION_NETWORKING_H_

#include "flatbuffers/flatbuffers.h"

namespace Networking {

struct Vec3;

struct PlayerLocation;

MANUALLY_ALIGNED_STRUCT(4) Vec3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  Vec3() {
    memset(this, 0, sizeof(Vec3));
  }
  Vec3(float _x, float _y, float _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
STRUCT_END(Vec3, 12);

struct PlayerLocation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_POS = 4,
    VT_ID = 6
  };
  const Vec3 *pos() const {
    return GetStruct<const Vec3 *>(VT_POS);
  }
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Vec3>(verifier, VT_POS) &&
           VerifyOffset(verifier, VT_ID) &&
           verifier.Verify(id()) &&
           verifier.EndTable();
  }
};

struct PlayerLocationBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const Vec3 *pos) {
    fbb_.AddStruct(PlayerLocation::VT_POS, pos);
  }
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(PlayerLocation::VT_ID, id);
  }
  explicit PlayerLocationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerLocationBuilder &operator=(const PlayerLocationBuilder &);
  flatbuffers::Offset<PlayerLocation> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerLocation>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerLocation> CreatePlayerLocation(
    flatbuffers::FlatBufferBuilder &_fbb,
    const Vec3 *pos = 0,
    flatbuffers::Offset<flatbuffers::String> id = 0) {
  PlayerLocationBuilder builder_(_fbb);
  builder_.add_id(id);
  builder_.add_pos(pos);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerLocation> CreatePlayerLocationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const Vec3 *pos = 0,
    const char *id = nullptr) {
  return Networking::CreatePlayerLocation(
      _fbb,
      pos,
      id ? _fbb.CreateString(id) : 0);
}

inline const Networking::PlayerLocation *GetPlayerLocation(const void *buf) {
  return flatbuffers::GetRoot<Networking::PlayerLocation>(buf);
}

inline bool VerifyPlayerLocationBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Networking::PlayerLocation>(nullptr);
}

inline void FinishPlayerLocationBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Networking::PlayerLocation> root) {
  fbb.Finish(root);
}

}  // namespace Networking

#endif  // FLATBUFFERS_GENERATED_PLAYERLOCATION_NETWORKING_H_
