#include "Document.hpp"

#include <fstream>

namespace ubt {
  void Document::load(std::istream& input) {
    loadThing(*this, nullptr, input);
  }

  bool Document::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if(!file) {
      return false;
    }

    load(file);

    return true;
  }

  void Document::save(std::ostream& output) {
    saveThing(*this, std::string(), output);
  }

  bool Document::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if(!file) {
      return false;
    }

    save(file);

    return true;
  }

  void Document::loadString(std::string* string, std::istream& input) {
    if(!string) {
      return;
    }

    string->clear();

    char ch = input.get();
    while(ch != '\0') {
      if(input.eof()) {
        throw std::runtime_error("unexpected eof");
      }

      string->push_back(ch);
      input.get(ch);
    }
  }

  void Document::loadThing(Value& thing, std::string* name, std::istream& input) {
    if(input.eof()) {
      throw std::runtime_error("unexpected eof");
    }

    thing.setType(static_cast<Type>(input.get()));

    if(input.eof()) {
      throw std::runtime_error("unexpected eof");
    }

    Fixed fixed;
    switch(thing.getType()) {
      case Type::Null:
        loadString(name, input);
        break;

      case Type::Boolean:
        loadString(name, input);
        fixed.boolean = input.get();

        thing.setFixed(fixed);
        break;

      case Type::Uint8:
      case Type::Int8:
        loadString(name, input);
        loadNumber(fixed.uint8, input);

        thing.setFixed(fixed);
        break;

      case Type::Uint16:
      case Type::Int16:
        loadString(name, input);
        loadNumber(fixed.uint16, input);

        thing.setFixed(fixed);
        break;

      case Type::Uint32:
      case Type::Int32:
      case Type::Real32:
        loadString(name, input);
        loadNumber(fixed.uint32, input);

        thing.setFixed(fixed);
        break;

      case Type::Uint64:
      case Type::Int64:
      case Type::Real64:
        loadString(name, input);
        loadNumber(fixed.uint64, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u8:
      case Type::Vec2i8:
        loadString(name, input);
        loadNumber(fixed.vec2u8.x, input);
        loadNumber(fixed.vec2u8.y, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u16:
      case Type::Vec2i16:
        loadString(name, input);
        loadNumber(fixed.vec2u16.x, input);
        loadNumber(fixed.vec2u16.y, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u32:
      case Type::Vec2i32:
      case Type::Vec2r32:
        loadString(name, input);
        loadNumber(fixed.vec2u32.x, input);
        loadNumber(fixed.vec2u32.y, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u64:
      case Type::Vec2i64:
      case Type::Vec2r64:
        loadString(name, input);
        loadNumber(fixed.vec2u64.x, input);
        loadNumber(fixed.vec2u64.y, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u8:
      case Type::Vec3i8:
        loadString(name, input);
        loadNumber(fixed.vec3u8.x, input);
        loadNumber(fixed.vec3u8.y, input);
        loadNumber(fixed.vec3u8.z, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u16:
      case Type::Vec3i16:
        loadString(name, input);
        loadNumber(fixed.vec3u16.x, input);
        loadNumber(fixed.vec3u16.y, input);
        loadNumber(fixed.vec3u16.z, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u32:
      case Type::Vec3i32:
      case Type::Vec3r32:
        loadString(name, input);
        loadNumber(fixed.vec3u32.x, input);
        loadNumber(fixed.vec3u32.y, input);
        loadNumber(fixed.vec3u32.z, input);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u64:
      case Type::Vec3i64:
      case Type::Vec3r64:
        loadString(name, input);
        loadNumber(fixed.vec3u64.x, input);
        loadNumber(fixed.vec3u64.y, input);
        loadNumber(fixed.vec3u64.z, input);

        thing.setFixed(fixed);
        break;

      case Type::String:
        loadString(name, input);

        {
          std::string word;
          loadString(&word, input);
          thing.setString(word);
        }
        break;

      case Type::Array:
        loadString(name, input);

        do {
          loadThing(thing.getArray().emplace_back(), nullptr, input);
        } while(thing.getArray().back().getType() != Type::ArrayEnd);
        break;

      case Type::ArrayEnd:
        break;

      case Type::Object:
        loadString(name, input);

        {
          ubt::Value value;
          std::string word;
          while(true) {
            loadThing(value, &word, input);
            if(value.getType() == Type::ObjectEnd) {
              break;
            }
            thing[word] = value;
          };
        }
        break;

      case Type::ObjectEnd:
        break;

      default:
        throw std::range_error(std::to_string(static_cast<unsigned> (thing.getType())) + " is not known type");
    }
  }

  void Document::saveString(const std::string& string, std::ostream& output) {
    if(string.empty()) {
      return;
    }

    output.write(string.c_str(), string.length()).put('\0');
  }

  void Document::saveThing(const Value& thing, const std::string& name, std::ostream& output) {
    output.put(static_cast<char>(thing.getType()));

    saveString(name, output);

    switch(thing.getType()) {
      case Type::Boolean:
        output.put(thing.getFixed().boolean ? 255 : 0);
        break;

      case Type::Uint8:
      case Type::Int8:
        saveNumber(thing.getFixed().uint8, output);
        break;

      case Type::Uint16:
      case Type::Int16:
        saveNumber(thing.getFixed().uint16, output);
        break;

      case Type::Uint32:
      case Type::Int32:
      case Type::Real32:
        saveNumber(thing.getFixed().uint32, output);
        break;

      case Type::Uint64:
      case Type::Int64:
      case Type::Real64:
        saveNumber(thing.getFixed().uint64, output);
        break;

      case Type::Vec2u8:
      case Type::Vec2i8:
        saveNumber(thing.getFixed().vec2u8.x, output);
        saveNumber(thing.getFixed().vec2u8.y, output);
        break;

      case Type::Vec2u16:
      case Type::Vec2i16:
        saveNumber(thing.getFixed().vec2u16.x, output);
        saveNumber(thing.getFixed().vec2u16.y, output);
        break;

      case Type::Vec2u32:
      case Type::Vec2i32:
      case Type::Vec2r32:
        saveNumber(thing.getFixed().vec2u32.x, output);
        saveNumber(thing.getFixed().vec2u32.y, output);
        break;

      case Type::Vec2u64:
      case Type::Vec2i64:
      case Type::Vec2r64:
        saveNumber(thing.getFixed().vec2u64.x, output);
        saveNumber(thing.getFixed().vec2u64.y, output);
        break;

      case Type::Vec3u8:
      case Type::Vec3i8:
        saveNumber(thing.getFixed().vec3u8.x, output);
        saveNumber(thing.getFixed().vec3u8.y, output);
        saveNumber(thing.getFixed().vec3u8.z, output);
        break;

      case Type::Vec3u16:
      case Type::Vec3i16:
        saveNumber(thing.getFixed().vec3u16.x, output);
        saveNumber(thing.getFixed().vec3u16.y, output);
        saveNumber(thing.getFixed().vec3u16.z, output);
        break;

      case Type::Vec3u32:
      case Type::Vec3i32:
      case Type::Vec3r32:
        saveNumber(thing.getFixed().vec3u32.x, output);
        saveNumber(thing.getFixed().vec3u32.y, output);
        saveNumber(thing.getFixed().vec3u32.z, output);
        break;

      case Type::Vec3u64:
      case Type::Vec3i64:
      case Type::Vec3r64:
        saveNumber(thing.getFixed().vec3u64.x, output);
        saveNumber(thing.getFixed().vec3u64.y, output);
        saveNumber(thing.getFixed().vec3u64.z, output);
        break;

      case Type::String:
        saveString(thing.getString(), output);
        break;

      case Type::Array:
        for(auto& i : thing.getArray()) {
          saveThing(i, std::string(), output);
        }
        saveThing(Type::ArrayEnd, std::string(), output);
        break;

      case Type::Object:
        for(auto& [iKey, iVal] : thing.getObject()) {
          saveThing(iVal, iKey, output);
        }
        saveThing(Type::ObjectEnd, std::string(), output);
        break;

      default:
        throw std::range_error(std::to_string(static_cast<unsigned> (thing.getType())) + " is not known type");
    }
  }
}
