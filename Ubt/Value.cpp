#include "Value.hpp"

#include <exception>

Value::Value(const Type type) {
  setType(type);
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

std::string Value::getString() const {
  if(type_ != Type::String) {
    throw std::exception("Type is not string");
  }

  return *variable_.ptrString;
}

void Value::setString(const std::string& string) {
  if(type_ != Type::String) {
    throw std::exception("Type is not string");
  }

  *variable_.ptrString = string;
}

std::vector<Value> Value::getArray() const {
  if(type_ != Type::Array) {
    throw std::exception("Type is not array");
  }

  return *variable_.ptrArray;
}

void Value::setArray(const std::vector<Value>& array) {
  if(type_ != Type::Array) {
    throw std::exception("Type is not array");
  }

  *variable_.ptrArray = array;
}

std::unordered_map<std::string, Value> Value::getObject() const {
  if(type_ != Type::Object) {
    throw std::exception("Type is not object");
  }

  return *variable_.ptrObject;
}

void Value::setObject(const std::unordered_map<std::string, Value>& object) {
  if(type_ != Type::Object) {
    throw std::exception("Type is not object");
  }

  *variable_.ptrObject = object;
}
