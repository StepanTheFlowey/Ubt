#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Value {
public:

  enum class Type {
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

    Float,
    Double,

    Vector2u8,
    Vector2u16,
    Vector2u32,
    Vector2u64,

    Vector2i8,
    Vector2i16,
    Vector2i32,
    Vector2i64,

    Vector3u8,
    Vector3u16,
    Vector3u32,
    Vector3u64,

    Vector3i8,
    Vector3i16,
    Vector3i32,
    Vector3i64,

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

    float Float;
    double Double;

    struct Vector2u8 {
      uint8_t x;
      uint8_t y;
    } vector2u8;
    struct Vector2u16 {
      uint16_t x;
      uint16_t y;
    } vector2u16;
    struct Vector2u32 {
      uint32_t x;
      uint32_t y;
    } vector2u32;
    struct Vector2u64 {
      uint64_t x;
      uint64_t y;
    } vector2u64;

    struct Vector2i8 {
      int8_t x ;
      int8_t y ;
    } vector2i8;
    struct Vector2i16 {
      int16_t x;
      int16_t y;
    } vector2i16;
    struct Vector2i32 {
      int32_t x;
      int32_t y;
    } vector2i32;
    struct Vector2i64 {
      int64_t x ;
      int64_t y ;
    } vector2i64;

    struct Vector3u8 {
      uint8_t x ;
      uint8_t y ;
      uint8_t z ;
    } vector3u8;
    struct Vector3u16 {
      uint16_t x;
      uint16_t y;
      uint16_t z;
    } vector3u16;
    struct Vector3u32 {
      uint32_t x;
      uint32_t y;
      uint32_t z;
    } vector3u32;
    struct Vector3u64 {
      uint64_t x;
      uint64_t y;
      uint64_t z;
    } vector3u64;

    struct Vector3i8 {
      uint8_t x ;
      uint8_t y ;
      uint8_t z ;
    } vector3i8;
    struct Vector3i16 {
      uint16_t x;
      uint16_t y;
      uint16_t z;
    } vector3i16;
    struct Vector3i32 {
      uint32_t x;
      uint32_t y;
      uint32_t z;
    } vector3i32;
    struct Vector3i64 {
      uint64_t x;
      uint64_t y;
      uint64_t z;
    } vector3i64;
  };

  Value() = default;
  Value(const Type type);
  ~Value() = default;

  Type getType() const;
  void setType(const Type type);

  Fixed getFixed() const;
  void  setFixed(const Fixed& fixed);

  std::string getString() const;
  void        setString(const std::string& string);

  std::vector<Value> getArray() const;
  void               setArray(const std::vector<Value>& array);

  std::unordered_map<std::string, Value> getObject() const;
  void                                   setObject(const std::unordered_map<std::string, Value>& object);
protected:
  union Variable {
    std::string* ptrString = nullptr;
    std::vector<Value>* ptrArray;
    std::unordered_map<std::string, Value>* ptrObject;
  };

  Type type_ = Type::Null;
  Fixed fixed_;
  Variable variable_;
};

