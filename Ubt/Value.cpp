#include "Value.hpp"

#include <stdexcept>

namespace ubt {
  Value::Value(const Type type) {
    setType(type);
  }

  Value::Value(const Value& value) :
    type_(value.type_),
    fixed_(value.fixed_) {

    switch(type_) {
      case Value::Type::String:
        variable_.ptrString = new std::string(*value.variable_.ptrString);
        break;

      case Value::Type::Array:
        variable_.ptrArray = new std::vector<Value>(*value.variable_.ptrArray);
        break;

      case Value::Type::Object:
        variable_.ptrObject = new std::unordered_map<std::string, Value>(*value.variable_.ptrObject);
        break;
    }
  }

  Value::Value(Value&& value) noexcept :
    type_(std::exchange(value.type_, Type::Null)),
    fixed_(value.fixed_),
    variable_(value.variable_) {}

  Value::~Value() {
    setType(Type::Null);
  }

  Value::Type Value::getType() const {
    return type_;
  }

  void Value::setType(const Type type) {
    switch(type_) {
      case Value::Type::String: delete variable_.ptrString; break;
      case Value::Type::Array:  delete variable_.ptrArray;  break;
      case Value::Type::Object: delete variable_.ptrObject; break;
    }

    switch(type) {
      case Value::Type::String: variable_.ptrString = new std::string;                            break;
      case Value::Type::Array:  variable_.ptrArray = new std::vector<Value>;                      break;
      case Value::Type::Object: variable_.ptrObject = new std::unordered_map<std::string, Value>; break;
    }

    type_ = type;
  }


  Value::Fixed Value::getFixed() const {
    return fixed_;
  }

  void Value::setFixed(const Fixed& fixed) {
    fixed_ = fixed;
  }

  const std::string& Value::getString() const {
    if(type_ != Type::String) {
      throw std::logic_error("Type is not String");
    }

    return *variable_.ptrString;
  }

  void Value::setString(const std::string& string) {
    if(type_ != Type::String) {
      throw std::logic_error("type is not String");
    }

    *variable_.ptrString = string;
  }

  std::vector<Value>& Value::getArray() const {
    if(type_ != Type::Array) {
      throw std::logic_error("type is not Array");
    }

    return *variable_.ptrArray;
  }

  void Value::setArray(const std::vector<Value>& array) {
    if(type_ != Type::Array) {
      throw std::logic_error("type is not Array");
    }

    *variable_.ptrArray = array;
  }

  std::unordered_map<std::string, Value>& Value::getObject() const {
    if(type_ != Type::Object) {
      throw std::logic_error("type is not Object");
    }

    return *variable_.ptrObject;
  }

  void Value::setObject(const std::unordered_map<std::string, Value>& object) {
    if(type_ != Type::Object) {
      throw std::logic_error("type is not Object");
    }

    *variable_.ptrObject = object;
  }

  Value& Value::operator[](const uintptr_t index) {
    if(type_ != Type::Array) {
      throw std::logic_error("type is not array");
    }

    return (*variable_.ptrArray)[index];
  }

  Value& Value::operator[](const std::string& string) {
    if(type_ != Type::Object) {
      throw std::logic_error("type is not object");
    }

    return (*variable_.ptrObject)[string];
  }

  Value& Value::operator=(const Value& value) {
    setType(Type::Null);

    switch(value.type_) {
      case Value::Type::String:
        variable_.ptrString = new std::string(*value.variable_.ptrString);
        break;

      case Value::Type::Array:
        variable_.ptrArray = new std::vector<Value>(*value.variable_.ptrArray);
        break;

      case Value::Type::Object:
        variable_.ptrObject = new std::unordered_map<std::string, Value>(*value.variable_.ptrObject);
        break;
    }

    type_ = value.type_;
    fixed_ = value.fixed_;

    return *this;
  }

  Value& Value::operator=(Value&& value) noexcept {
    type_ = std::exchange(value.type_, Type::Null);
    fixed_ = value.fixed_;
    variable_ = value.variable_;

    return *this;
  }
}
