#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace ubt {
  class Value {
  public:

    enum class Type : uint8_t {
      Null = 0,
      Boolean,

      Uint8,
      Uint16,
      Uint32,
      Uint64,

      Int8,
      Int16,
      Int32,
      Int64,

      Real32,
      Real64,

      Vec2u8,
      Vec2u16,
      Vec2u32,
      Vec2u64,

      Vec2i8,
      Vec2i16,
      Vec2i32,
      Vec2i64,

      Vec2r32,
      Vec2r64,

      Vec3u8,
      Vec3u16,
      Vec3u32,
      Vec3u64,

      Vec3i8,
      Vec3i16,
      Vec3i32,
      Vec3i64,

      Vec3r32,
      Vec3r64,

      String,
      Array,
      ArrayEnd,
      Object,
      ObjectEnd
    };

    union Fixed {
      bool boolean;

      uint8_t uint8;
      uint16_t uint16;
      uint32_t uint32;
      uint64_t uint64;

      int8_t int8;
      int16_t int16;
      int32_t int32;
      int64_t int64;

      float real32;
      double real64;

      struct Vec2u8 {
        uint8_t x;
        uint8_t y;
      } vec2u8;
      struct Vec2u16 {
        uint16_t x;
        uint16_t y;
      } vec2u16;
      struct Vec2u32 {
        uint32_t x;
        uint32_t y;
      } vec2u32;
      struct Vec2u64 {
        uint64_t x;
        uint64_t y;
      } vec2u64;

      struct Vec2i8 {
        int8_t x;
        int8_t y;
      } vec2i8;
      struct Vec2i16 {
        int16_t x;
        int16_t y;
      } vec2i16;
      struct Vec2i32 {
        int32_t x;
        int32_t y;
      } vec2i32;
      struct Vec2i64 {
        int64_t x;
        int64_t y;
      } vec2i64;

      struct Vec2r32 {
        float x;
        float y;
      } vec2r32;
      struct Vec2r64 {
        double x;
        double y;
      } vec2r64;

      struct Vec3u8 {
        uint8_t x;
        uint8_t y;
        uint8_t z;
      } vec3u8;
      struct Vec3u16 {
        uint16_t x;
        uint16_t y;
        uint16_t z;
      } vec3u16;
      struct Vec3u32 {
        uint32_t x;
        uint32_t y;
        uint32_t z;
      } vec3u32;
      struct Vec3u64 {
        uint64_t x;
        uint64_t y;
        uint64_t z;
      } vec3u64;

      struct Vec3i8 {
        uint8_t x;
        uint8_t y;
        uint8_t z;
      } vec3i8;
      struct Vec3i16 {
        uint16_t x;
        uint16_t y;
        uint16_t z;
      } vec3i16;
      struct Vec3i32 {
        uint32_t x;
        uint32_t y;
        uint32_t z;
      } vec3i32;
      struct Vec3i64 {
        uint64_t x;
        uint64_t y;
        uint64_t z;
      } vec3i64;

      struct Vec3r32 {
        float x;
        float y;
        float z;
      } vec3r32;
      struct Vec3r64 {
        double x;
        double y;
        double z;
      } vec3r64;
    };

    Value() = default;
    Value(const Type type);
    Value(const Value& value);
    Value(Value&& value) noexcept;
    ~Value();

    Type getType() const;
    void setType(const Type type);

    Fixed getFixed() const;
    void  setFixed(const Fixed& fixed);

    const std::string& getString() const;
    void               setString(const std::string& string);

    std::vector<Value>& getArray() const;
    void                setArray(const std::vector<Value>& array);

    std::unordered_map<std::string, Value>& getObject() const;
    void                                    setObject(const std::unordered_map<std::string, Value>& object);

    Value& operator[](const uintptr_t index);
    Value& operator[](const std::string& string);

    Value& operator=(const Value& value);
    Value& operator=(Value&& value) noexcept;
  protected:

    union Variable {
      std::string* ptrString = nullptr;
      std::vector<Value>* ptrArray;
      std::unordered_map<std::string, Value>* ptrObject;
    };

    Type type_ = Type::Null;
    Fixed fixed_{};
    Variable variable_;
  };
}
