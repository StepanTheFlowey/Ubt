#include <iostream>
#include "../Ubt/Document.hpp"

int main(int argc, char** argv) {
  ubt::Document document;

  document.setType(ubt::Value::Type::Object);
  document["name"].setType(ubt::Value::Type::Uint32);
  document.save("test.ubt");
}