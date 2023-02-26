#include "Document.hpp"

#include <fstream>
#include "NetworkOrderConvert.hpp"

namespace ubt {
  bool Document::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if(!file) {
      return false;
    }

    std::string name;
    loadThing(*this, name, file);

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

  void Document::loadString(std::string& string, std::istream& input) {
    char ch = input.get();
    while(ch != 0) {
      string += ch;
      ch = input.get();
    }
  }

  void Document::loadThing(Value& thing, std::string& name, std::istream& input) {
    thing.setType(static_cast<Value::Type>(input.get()));


  }

  void Document::saveString(const std::string& string, std::ostream& stream) {
    stream.write(string.c_str(), string.size());
    stream.put(0);
  }

  void Document::saveThing(const Value& thing, const std::string& name, std::ostream& stream) {
    stream.put(static_cast<uint8_t>(thing.getType()));

    if(!name.empty()) {
      saveString(name, stream);
    }

    switch(thing.getType()) {
      case Type::Boolean:
      stream.put(thing.getFixed().boolean ? 255 : 0);
      break;

      case Type::Uint8:
      case Type::Int8:
      {
        auto n = hton(thing.getFixed().uint8);
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
        auto x = hton(thing.getFixed().vec2u8.x);
        auto y = hton(thing.getFixed().vec2u8.y);

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
      case Type::Vec2f:
      {
        auto x = hton(thing.getFixed().vec2u32.x);
        auto y = hton(thing.getFixed().vec2u32.y);

        stream.write(reinterpret_cast<const char*>(&x), sizeof(x));
        stream.write(reinterpret_cast<const char*>(&y), sizeof(y));
      }
      break;

      case Type::Vec2u64:
      case Type::Vec2i64:
      case Type::Vec2d:
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
        auto x = hton(thing.getFixed().vec3u8.x);
        auto y = hton(thing.getFixed().vec3u8.y);
        auto z = hton(thing.getFixed().vec3u8.z);

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
      case Type::Vec3f:
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
      case Type::Vec3d:
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
