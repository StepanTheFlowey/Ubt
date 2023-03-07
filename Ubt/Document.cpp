#include "Document.hpp"

#include <fstream>
#include "NetworkOrderConvert.hpp"

namespace ubt {
  bool Document::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if(!file) {
      return false;
    }

    loadThing(*this, nullptr, file);

    return true;
  }

  bool Document::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::in | std::ios::binary);

    if(!file) {
      return false;
    }

    saveThing(*this, std::string(), file);

    return true;
  }

  void Document::loadString(std::string* string, std::istream& input) {
    if(!string) {
      return;
    }

    string->clear();

    char ch = input.get();
    while(ch != '\0') {
      string->push_back(ch);
      if(input.eof()) {
        throw std::out_of_range("unexpected end of file!");
      }
      ch = input.get();
    }
  }

  void Document::loadThing(Value& thing, std::string* name, std::istream& input) {
    if(input.eof()) {
      throw std::out_of_range("unexpected end of file!");
    }

    thing.setType(static_cast<Type>(input.get()));

    if(input.eof()) {
      throw std::out_of_range("unexpected end of file!");
    }

    Fixed fixed;
    switch(thing.getType()) {
      case Type::Null:
        loadString(name, input);
        break;

      case Type::Boolean:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.boolean), sizeof(fixed.boolean)).gcount() != sizeof(fixed.boolean)) {

        }

        thing.setFixed(fixed);
        break;

      case Type::Uint8:
      case Type::Int8:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.uint8), sizeof(fixed.uint8)).gcount() != sizeof(fixed.uint8)) {

        }

        thing.setFixed(fixed);
        break;

      case Type::Uint16:
      case Type::Int16:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.uint16), sizeof(fixed.uint16)).gcount() != sizeof(fixed.uint16)) {

        }
        fixed.uint16 = ntoh(fixed.uint16);

        thing.setFixed(fixed);
        break;

      case Type::Uint32:
      case Type::Int32:
      case Type::Real32:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.uint32), sizeof(fixed.uint32)).gcount() != sizeof(fixed.uint32)) {

        }
        fixed.uint32 = ntoh(fixed.uint32);

        thing.setFixed(fixed);
        break;

      case Type::Uint64:
      case Type::Int64:
      case Type::Real64:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.uint64), sizeof(fixed.uint64)).gcount() != sizeof(fixed.uint64)) {

        }
        fixed.uint64 = ntoh(fixed.uint64);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u8:
      case Type::Vec2i8:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec2u8.x), sizeof(fixed.vec2u8.x)).gcount() != sizeof(fixed.vec2u8.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec2u8.y), sizeof(fixed.vec2u8.y)).gcount() != sizeof(fixed.vec2u8.y)) {

        }

        thing.setFixed(fixed);
        break;

      case Type::Vec2u16:
      case Type::Vec2i16:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec2u16.x), sizeof(fixed.vec2u16.x)).gcount() != sizeof(fixed.vec2u16.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec2u16.y), sizeof(fixed.vec2u16.y)).gcount() != sizeof(fixed.vec2u16.y)) {

        }
        fixed.vec2u16.x = ntoh(fixed.vec2u16.x);
        fixed.vec2u16.y = ntoh(fixed.vec2u16.y);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u32:
      case Type::Vec2i32:
      case Type::Vec2r32:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec2u32.x), sizeof(fixed.vec2u32.x)).gcount() != sizeof(fixed.vec2u32.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec2u32.y), sizeof(fixed.vec2u32.y)).gcount() != sizeof(fixed.vec2u32.y)) {

        }
        fixed.vec2u32.x = ntoh(fixed.vec2u32.x);
        fixed.vec2u32.y = ntoh(fixed.vec2u32.y);

        thing.setFixed(fixed);
        break;

      case Type::Vec2u64:
      case Type::Vec2i64:
      case Type::Vec2r64:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec2u64.x), sizeof(fixed.vec2u64.x)).gcount() != sizeof(fixed.vec2u64.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec2u64.y), sizeof(fixed.vec2u64.y)).gcount() != sizeof(fixed.vec2u64.y)) {

        }
        fixed.vec2u64.x = ntoh(fixed.vec2u64.x);
        fixed.vec2u64.y = ntoh(fixed.vec2u64.y);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u8:
      case Type::Vec3i8:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec3u8.x), sizeof(fixed.vec3u8.x)).gcount() != sizeof(fixed.vec3u8.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u8.y), sizeof(fixed.vec3u8.y)).gcount() != sizeof(fixed.vec3u8.y)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u8.z), sizeof(fixed.vec3u8.y)).gcount() != sizeof(fixed.vec3u8.y)) {

        }

        thing.setFixed(fixed);
        break;

      case Type::Vec3u16:
      case Type::Vec3i16:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec3u16.x), sizeof(fixed.vec3u16.x)).gcount() != sizeof(fixed.vec3u16.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u16.y), sizeof(fixed.vec3u16.y)).gcount() != sizeof(fixed.vec3u16.y)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u16.z), sizeof(fixed.vec3u16.y)).gcount() != sizeof(fixed.vec3u16.y)) {

        }
        fixed.vec3u16.x = ntoh(fixed.vec3u16.x);
        fixed.vec3u16.y = ntoh(fixed.vec3u16.y);
        fixed.vec3u16.z = ntoh(fixed.vec3u16.z);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u32:
      case Type::Vec3i32:
      case Type::Vec3r32:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec3u32.x), sizeof(fixed.vec3u32.x)).gcount() != sizeof(fixed.vec3u32.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u32.y), sizeof(fixed.vec3u32.y)).gcount() != sizeof(fixed.vec3u32.y)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u32.z), sizeof(fixed.vec3u32.y)).gcount() != sizeof(fixed.vec3u32.y)) {

        }
        fixed.vec3u32.x = ntoh(fixed.vec3u32.x);
        fixed.vec3u32.y = ntoh(fixed.vec3u32.y);
        fixed.vec3u32.z = ntoh(fixed.vec3u32.z);

        thing.setFixed(fixed);
        break;

      case Type::Vec3u64:
      case Type::Vec3i64:
      case Type::Vec3r64:
        loadString(name, input);

        if(input.read(reinterpret_cast<char*>(&fixed.vec3u64.x), sizeof(fixed.vec3u64.x)).gcount() != sizeof(fixed.vec3u64.x)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u64.y), sizeof(fixed.vec3u64.y)).gcount() != sizeof(fixed.vec3u64.y)) {

        }
        if(input.read(reinterpret_cast<char*>(&fixed.vec3u64.z), sizeof(fixed.vec3u64.z)).gcount() != sizeof(fixed.vec3u64.z)) {

        }
        fixed.vec3u64.x = ntoh(fixed.vec3u64.x);
        fixed.vec3u64.y = ntoh(fixed.vec3u64.y);
        fixed.vec3u64.z = ntoh(fixed.vec3u64.z);

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
    }
  }

  void Document::saveString(const std::string& string, std::ostream& stream) {
    if(string.empty()) {
      return;
    }

    stream.write(string.c_str(), string.size());
    stream.put('\0');
  }

  void Document::saveThing(const Value& thing, const std::string& name, std::ostream& stream) {
    stream.put(static_cast<char>(thing.getType()));

    saveString(name, stream);

    switch(thing.getType()) {
      case Type::Boolean:
        stream.put(thing.getFixed().boolean ? 255 : 0);
        break;

      case Type::Uint8:
      case Type::Int8:
      {
        auto n = thing.getFixed().uint8;
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint16:
      case Type::Int16:
      {
        auto n = hton(thing.getFixed().uint16);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint32:
      case Type::Int32:
      case Type::Real32:
      {
        auto n = hton(thing.getFixed().uint32);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint64:
      case Type::Int64:
      case Type::Real64:
      {
        auto n = hton(thing.getFixed().uint64);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Vec2u8:
      case Type::Vec2i8:
      {
        auto x = thing.getFixed().vec2u8.x;
        auto y = thing.getFixed().vec2u8.y;

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
      }
      break;

      case Type::Vec2u16:
      case Type::Vec2i16:
      {
        auto x = hton(thing.getFixed().vec2u16.x);
        auto y = hton(thing.getFixed().vec2u16.y);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
      }
      break;

      case Type::Vec2u32:
      case Type::Vec2i32:
      case Type::Vec2r32:
      {
        auto x = hton(thing.getFixed().vec2u32.x);
        auto y = hton(thing.getFixed().vec2u32.y);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
      }
      break;

      case Type::Vec2u64:
      case Type::Vec2i64:
      case Type::Vec2r64:
      {
        auto x = hton(thing.getFixed().vec2u64.x);
        auto y = hton(thing.getFixed().vec2u64.y);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
      }
      break;

      case Type::Vec3u8:
      case Type::Vec3i8:
      {
        auto x = thing.getFixed().vec3u8.x;
        auto y = thing.getFixed().vec3u8.y;
        auto z = thing.getFixed().vec3u8.z;

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
        stream.write(reinterpret_cast<const char*>(&z), sizeof(z));
      }
      break;

      case Type::Vec3u16:
      case Type::Vec3i16:
      {
        auto x = hton(thing.getFixed().vec3u16.x);
        auto y = hton(thing.getFixed().vec3u16.y);
        auto z = hton(thing.getFixed().vec3u16.z);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
        stream.write(reinterpret_cast<const char*>(&z), sizeof(z));
      }
      break;

      case Type::Vec3u32:
      case Type::Vec3i32:
      case Type::Vec3r32:
      {
        auto x = hton(thing.getFixed().vec3u32.x);
        auto y = hton(thing.getFixed().vec3u32.y);
        auto z = hton(thing.getFixed().vec3u32.z);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
        stream.write(reinterpret_cast<const char*>(&z), sizeof(z));
      }
      break;

      case Type::Vec3u64:
      case Type::Vec3i64:
      case Type::Vec3r64:
      {
        auto x = hton(thing.getFixed().vec3u64.x);
        auto y = hton(thing.getFixed().vec3u64.y);
        auto z = hton(thing.getFixed().vec3u64.z);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
        stream.write(reinterpret_cast<const char*>(&z), sizeof(z));
      }
      break;

      case Type::String:
        saveString(thing.getString(), stream);
        break;

      case Type::Array:
        for(auto& i : thing.getArray()) {
          saveThing(i, std::string(), stream);
        }
        saveThing(Type::ArrayEnd, std::string(), stream);
        break;

      case Type::Object:
        for(auto& [iKey, iVal] : thing.getObject()) {
          saveThing(iVal, iKey, stream);
        }
        saveThing(Type::ObjectEnd, std::string(), stream);
        break;
    }
  }
}
