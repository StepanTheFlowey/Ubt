#pragma once

#include <concepts>
#include <iostream>
#include "Value.hpp"

namespace ubt {
  class Document : public Value {
  public:

    Document() = default;
    ~Document() = default;

    void load(std::istream& input);
    bool loadFromFile(const std::string& filename);

    void save(std::ostream& output);
    bool saveToFile(const std::string& filename);
  protected:

    template <std::integral T>
    void loadNumber(T& number, std::istream& input);
    void loadString(std::string* string, std::istream& input);
    void loadThing(Value& thing, std::string* name, std::istream& input);

    template <std::integral T>
    void saveNumber(const T& number, std::ostream& output);
    void saveString(const std::string& string, std::ostream& output);
    void saveThing(const Value& thing, const std::string& name, std::ostream& output);
  };
}

#include "Document.inl"
