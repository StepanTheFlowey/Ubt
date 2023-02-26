#pragma once

#include <iostream>
#include "Value.hpp"

namespace ubt {
  class Document : public Value {
  public:

    Document() = default;
    ~Document() = default;

    bool load(const std::string& filename);
    bool save(const std::string& filename);
  protected:

    void loadString(std::string& string, std::istream& input);
    void loadThing(Value& thing, std::string& name, std::istream& input);

    void saveString(const std::string& string, std::ostream& stream);
    void saveThing(const Value& thing, const std::string& name, std::ostream& stream);
  };
}
