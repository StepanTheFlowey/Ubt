#include "Document.hpp"

#include <fstream>
#include "NetworkOrderConvert.hpp"

namespace ubt {
  bool Document::load(const std::string& filename) {
    return false;
  }

  bool Document::save(const std::string& filename) {
    std::ofstream file(filename);

    if(!file) {
      return false;
    }

    saveThing(*this, std::string(), file);

    return true;
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
      {
        auto n = hton(thing.getFixed().uint8);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint16:
      {
        auto n = hton(thing.getFixed().uint16);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint32:
      {
        auto n = hton(thing.getFixed().uint32);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
      break;

      case Type::Uint64:
      {
        auto n = hton(thing.getFixed().uint64);
        stream.write(reinterpret_cast<const char*>(&n), sizeof(n));
      }
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
