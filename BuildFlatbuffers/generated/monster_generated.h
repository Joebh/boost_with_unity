// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MONSTER_MYGAME_H_
#define FLATBUFFERS_GENERATED_MONSTER_MYGAME_H_

#include "flatbuffers/flatbuffers.h"

namespace MyGame {

struct Vec3;

struct Monster;

enum Color {
  Color_Red = 1,
  Color_Green = 2,
  Color_Blue = 3,
  Color_MIN = Color_Red,
  Color_MAX = Color_Blue
};

inline Color (&EnumValuesColor())[3] {
  static Color values[] = {
    Color_Red,
    Color_Green,
    Color_Blue
  };
  return values;
}

inline const char **EnumNamesColor() {
  static const char *names[] = {
    "Red",
    "Green",
    "Blue",
    nullptr
  };
  return names;
}

inline const char *EnumNameColor(Color e) {
  const size_t index = static_cast<int>(e) - static_cast<int>(Color_Red);
  return EnumNamesColor()[index];
}

enum Any {
  Any_NONE = 0,
  Any_Monster = 1,
  Any_MIN = Any_NONE,
  Any_MAX = Any_Monster
};

inline Any (&EnumValuesAny())[2] {
  static Any values[] = {
    Any_NONE,
    Any_Monster
  };
  return values;
}

inline const char **EnumNamesAny() {
  static const char *names[] = {
    "NONE",
    "Monster",
    nullptr
  };
  return names;
}

inline const char *EnumNameAny(Any e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesAny()[index];
}

template<typename T> struct AnyTraits {
  static const Any enum_value = Any_NONE;
};

template<> struct AnyTraits<Monster> {
  static const Any enum_value = Any_Monster;
};

bool VerifyAny(flatbuffers::Verifier &verifier, const void *obj, Any type);
bool VerifyAnyVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

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

struct Monster FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_POS = 4,
    VT_MANA = 6,
    VT_HP = 8,
    VT_NAME = 10,
    VT_INVENTORY = 14,
    VT_COLOR = 16,
    VT_TEST_TYPE = 18,
    VT_TEST = 20
  };
  const Vec3 *pos() const {
    return GetStruct<const Vec3 *>(VT_POS);
  }
  int16_t mana() const {
    return GetField<int16_t>(VT_MANA, 150);
  }
  int16_t hp() const {
    return GetField<int16_t>(VT_HP, 100);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<uint8_t> *inventory() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_INVENTORY);
  }
  Color color() const {
    return static_cast<Color>(GetField<int8_t>(VT_COLOR, 3));
  }
  Any test_type() const {
    return static_cast<Any>(GetField<uint8_t>(VT_TEST_TYPE, 0));
  }
  const void *test() const {
    return GetPointer<const void *>(VT_TEST);
  }
  template<typename T> const T *test_as() const;
  const Monster *test_as_Monster() const {
    return test_type() == Any_Monster ? static_cast<const Monster *>(test()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Vec3>(verifier, VT_POS) &&
           VerifyField<int16_t>(verifier, VT_MANA) &&
           VerifyField<int16_t>(verifier, VT_HP) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.Verify(name()) &&
           VerifyOffset(verifier, VT_INVENTORY) &&
           verifier.Verify(inventory()) &&
           VerifyField<int8_t>(verifier, VT_COLOR) &&
           VerifyField<uint8_t>(verifier, VT_TEST_TYPE) &&
           VerifyOffset(verifier, VT_TEST) &&
           VerifyAny(verifier, test(), test_type()) &&
           verifier.EndTable();
  }
};

template<> inline const Monster *Monster::test_as<Monster>() const {
  return test_as_Monster();
}

struct MonsterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const Vec3 *pos) {
    fbb_.AddStruct(Monster::VT_POS, pos);
  }
  void add_mana(int16_t mana) {
    fbb_.AddElement<int16_t>(Monster::VT_MANA, mana, 150);
  }
  void add_hp(int16_t hp) {
    fbb_.AddElement<int16_t>(Monster::VT_HP, hp, 100);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Monster::VT_NAME, name);
  }
  void add_inventory(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> inventory) {
    fbb_.AddOffset(Monster::VT_INVENTORY, inventory);
  }
  void add_color(Color color) {
    fbb_.AddElement<int8_t>(Monster::VT_COLOR, static_cast<int8_t>(color), 3);
  }
  void add_test_type(Any test_type) {
    fbb_.AddElement<uint8_t>(Monster::VT_TEST_TYPE, static_cast<uint8_t>(test_type), 0);
  }
  void add_test(flatbuffers::Offset<void> test) {
    fbb_.AddOffset(Monster::VT_TEST, test);
  }
  explicit MonsterBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MonsterBuilder &operator=(const MonsterBuilder &);
  flatbuffers::Offset<Monster> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Monster>(end);
    return o;
  }
};

inline flatbuffers::Offset<Monster> CreateMonster(
    flatbuffers::FlatBufferBuilder &_fbb,
    const Vec3 *pos = 0,
    int16_t mana = 150,
    int16_t hp = 100,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> inventory = 0,
    Color color = Color_Blue,
    Any test_type = Any_NONE,
    flatbuffers::Offset<void> test = 0) {
  MonsterBuilder builder_(_fbb);
  builder_.add_test(test);
  builder_.add_inventory(inventory);
  builder_.add_name(name);
  builder_.add_pos(pos);
  builder_.add_hp(hp);
  builder_.add_mana(mana);
  builder_.add_test_type(test_type);
  builder_.add_color(color);
  return builder_.Finish();
}

inline flatbuffers::Offset<Monster> CreateMonsterDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const Vec3 *pos = 0,
    int16_t mana = 150,
    int16_t hp = 100,
    const char *name = nullptr,
    const std::vector<uint8_t> *inventory = nullptr,
    Color color = Color_Blue,
    Any test_type = Any_NONE,
    flatbuffers::Offset<void> test = 0) {
  return MyGame::CreateMonster(
      _fbb,
      pos,
      mana,
      hp,
      name ? _fbb.CreateString(name) : 0,
      inventory ? _fbb.CreateVector<uint8_t>(*inventory) : 0,
      color,
      test_type,
      test);
}

inline bool VerifyAny(flatbuffers::Verifier &verifier, const void *obj, Any type) {
  switch (type) {
    case Any_NONE: {
      return true;
    }
    case Any_Monster: {
      auto ptr = reinterpret_cast<const Monster *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyAnyVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyAny(
        verifier,  values->Get(i), types->GetEnum<Any>(i))) {
      return false;
    }
  }
  return true;
}

inline const MyGame::Monster *GetMonster(const void *buf) {
  return flatbuffers::GetRoot<MyGame::Monster>(buf);
}

inline bool VerifyMonsterBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MyGame::Monster>(nullptr);
}

inline void FinishMonsterBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyGame::Monster> root) {
  fbb.Finish(root);
}

}  // namespace MyGame

#endif  // FLATBUFFERS_GENERATED_MONSTER_MYGAME_H_
