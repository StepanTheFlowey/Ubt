#include <iostream>
#include <fstream>
#include <set>
#include "StringSwitch.h"
#include "../Ubt/Document.hpp"

bool beVerbose = false;

void verbose(const std::string& message) {
  if(beVerbose) {
    std::cout << message << '\n';
  }
}

bool doReadTagName = true;
std::string compileName(std::istream& input) {
  if(!doReadTagName) {
    return std::string();
  }

  std::string name;
  input >> name;
  verbose("Name \'" + name + '\'');
  return name;
}

void compile(std::istream& input, ubt::Value& output, std::string& name) {
  ubt::Value::Fixed fixed;
  std::string word;

  input >> word;

  switch(strHashSwitch(word)) {
    case strHashSwitch("Null"):
      verbose("Tag Null");
      name = compileName(input);
      output.setType(ubt::Value::Type::Null);
      break;

    case strHashSwitch("Bool"):
    case strHashSwitch("Boolean"):
      verbose("Tag Boolean");
      name = compileName(input);

      input >> word;
      if(word == "true") {
        fixed.boolean = true;
      }
      else if(word == "false") {
        fixed.boolean = false;
      }
      else {
        std::cout << "Invalid value \'" << word << "\' for Bool \'" << name << "\'!\n";
        exit(EXIT_FAILURE);
      }

      output.setType(ubt::Value::Type::Boolean);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint8"):
      verbose("Tag Uint8");
      name = compileName(input);

      input >> word;
      fixed.uint8 = std::stoi(word);

      output.setType(ubt::Value::Type::Uint8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint16"):
      verbose("Tag Uint16");
      name = compileName(input);

      input >> word;
      fixed.uint16 = std::stoi(word);

      output.setType(ubt::Value::Type::Uint16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint32"):
      verbose("Tag Uint32");
      name = compileName(input);

      input >> word;
      fixed.uint32 = std::stoul(word);

      output.setType(ubt::Value::Type::Uint32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint64"):
      verbose("Tag Uint64");
      name = compileName(input);

      input >> word;
      fixed.uint64 = std::stoull(word);

      output.setType(ubt::Value::Type::Uint64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int8"):
      verbose("Tag Int8");
      name = compileName(input);

      input >> word;
      fixed.int8 = std::stoi(word);

      output.setType(ubt::Value::Type::Int8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int16"):
      verbose("Tag Int16");
      name = compileName(input);

      input >> word;
      fixed.int16 = std::stoi(word);

      output.setType(ubt::Value::Type::Int16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int32"):
      verbose("Tag Int32");
      name = compileName(input);

      input >> word;
      fixed.int32 = std::stol(word);

      output.setType(ubt::Value::Type::Int32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int64"):
      verbose("Tag Int64");
      name = compileName(input);

      input >> word;
      fixed.int64 = std::stoll(word);

      output.setType(ubt::Value::Type::Int64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Real32"):
      verbose("Tag Real32");
      name = compileName(input);

      input >> word;
      fixed.real32 = std::stof(word);

      output.setType(ubt::Value::Type::Real32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Real64"):
      verbose("Tag Real64");
      name = compileName(input);

      input >> word;
      fixed.real64 = std::stod(word);

      output.setType(ubt::Value::Type::Real64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2u8"):
      verbose("Tag Vec2u8");
      name = compileName(input);

      input >> word;
      fixed.vec2u8.x = std::stoi(word);

      input >> word;
      fixed.vec2u8.y = std::stoi(word);

      output.setType(ubt::Value::Type::Vec2u8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("String"):
      verbose("Tag String");
      name = compileName(input);

      output.setType(ubt::Value::Type::String);
      {
        char ch = input.get();
        if(ch != '\"') {
          std::cout << "String scope not beginned." << std::endl;
          exit(EXIT_FAILURE);
        }
        ch = input.get();
        while(ch != '\"') {
          word.push_back(ch);
          ch = input.get();
        }
      }
      output.setString(word);
      break;

    case strHashSwitch("Array"):
      verbose("Tag Array");
      name = compileName(input);

      output.setType(ubt::Value::Type::Array);
      output.getArray().reserve(32);
      doReadTagName = false;

      {
        uintptr_t c = 0;
        ubt::Value value;
        compile(input, value, word);
        while(value.getType() != ubt::Value::Type::ArrayEnd) {
          if(input.eof()) {
            std::cout << "Unexpected file end. Array scope not closed!" << std::endl;
            exit(EXIT_FAILURE);
          }

          output.getArray().push_back(value);

          compile(input, value, word);
          doReadTagName = false;
        }
      }
      doReadTagName = true;
      break;

    case strHashSwitch("ArrayEnd"):
      verbose("Tag ArrayEnd");
      output.setType(ubt::Value::Type::ArrayEnd);
      break;

    case strHashSwitch("Object"):
      verbose("Tag Object");
      name = compileName(input);

      output.setType(ubt::Value::Type::Object);

      {
        ubt::Value value;
        compile(input, value, word);
        while(value.getType() != ubt::Value::Type::ObjectEnd) {
          if(input.eof()) {
            std::cout << "Unexpected file end. Object scope not closed!" << std::endl;
            exit(EXIT_FAILURE);
          }
          output[word] = value;
          compile(input, value, word);
        }
      }
      break;

    case strHashSwitch("ObjectEnd"):
      verbose("Tag ObjectEnd");
      output.setType(ubt::Value::Type::ObjectEnd);
      break;
  }
}

void compile(std::istream& input, ubt::Value& output) {
  std::string name("");

  compile(input, output, name);
}

void decompile(ubt::Value& value, std::ostream& output, const std::string& name, unsigned space = 0) {
  output << std::string(space * 2, ' ');

  switch(value.getType()) {
    case ubt::Value::Type::Null:
      output << "Null " << name << '\n';
      break;

    case ubt::Value::Type::Uint8:
      output << "Uint8 " << name << ' ' << std::to_string(value.getFixed().uint8) << '\n';
      break;

    case ubt::Value::Type::Uint16:
      output << "Uint16 " << name << ' ' << std::to_string(value.getFixed().uint16) << '\n';
      break;

    case ubt::Value::Type::Uint32:
      output << "Uint32 " << name << ' ' << std::to_string(value.getFixed().uint32) << '\n';
      break;

    case ubt::Value::Type::Uint64:
      output << "Uint64 " << name << ' ' << std::to_string(value.getFixed().uint64) << '\n';
      break;

    case ubt::Value::Type::Int8:
      output << "Int8 " << name << ' ' << std::to_string(value.getFixed().int8) << '\n';
      break;

    case ubt::Value::Type::Int16:
      output << "Int16 " << name << ' ' << std::to_string(value.getFixed().int16) << '\n';
      break;

    case ubt::Value::Type::Int32:
      output << "Int32 " << name << ' ' << std::to_string(value.getFixed().int32) << '\n';
      break;

    case ubt::Value::Type::Int64:
      output << "Int64 " << name << ' ' << std::to_string(value.getFixed().int64) << '\n';
      break;

    case ubt::Value::Type::Real32:
      output.precision(std::numeric_limits<float>::digits10);

      output << "Real32 " << name << ' ' << value.getFixed().real32 << '\n';
      break;

    case ubt::Value::Type::Real64:
      output.precision(std::numeric_limits<double>::digits10);

      output << "Real64 " << name << ' ' << value.getFixed().real64 << '\n';
      break;

    case ubt::Value::Type::Vec2u8:
      output << "Vec2u8 " << name << ' '
        << std::to_string(value.getFixed().vec2u8.x) << ' '
        << std::to_string(value.getFixed().vec2u8.y) << '\n';
      break;

    case ubt::Value::Type::Vec2u16:
      output << "Vec2u16 " << name << ' '
        << std::to_string(value.getFixed().vec2u16.x) << ' '
        << std::to_string(value.getFixed().vec2u16.y) << '\n';
      break;

    case ubt::Value::Type::Vec2u32:
      output << "Vec2u32 " << name << ' '
        << std::to_string(value.getFixed().vec2u32.x) << ' '
        << std::to_string(value.getFixed().vec2u32.y) << '\n';
      break;

    case ubt::Value::Type::Vec2u64:
      output << "Vec2u64 " << name << ' '
        << std::to_string(value.getFixed().vec2u64.x) << ' '
        << std::to_string(value.getFixed().vec2u64.y) << '\n';
      break;

    case ubt::Value::Type::Vec2i8:
      output << "Vec2u8 " << name << ' '
        << std::to_string(value.getFixed().vec2i8.x) << ' '
        << std::to_string(value.getFixed().vec2i8.y) << '\n';
      break;

    case ubt::Value::Type::Vec2i16:
      output << "Vec2u16 " << name << ' '
        << std::to_string(value.getFixed().vec2i16.x) << ' '
        << std::to_string(value.getFixed().vec2i16.y) << '\n';
      break;

    case ubt::Value::Type::Vec2i32:
      output << "Vec2u32 " << name << ' '
        << std::to_string(value.getFixed().vec2i32.x) << ' '
        << std::to_string(value.getFixed().vec2i32.y) << '\n';
      break;

    case ubt::Value::Type::Vec2i64:
      output << "Vec2u64 " << name << ' '
        << std::to_string(value.getFixed().vec2i64.x) << ' '
        << std::to_string(value.getFixed().vec2i64.y) << '\n';
      break;

    case ubt::Value::Type::Vec2f:
      output.precision(std::numeric_limits<float>::digits10);

      output << "Vec2f " << name << ' '
        << value.getFixed().vec2f.x << ' '
        << value.getFixed().vec2f.y << '\n';
      break;

    case ubt::Value::Type::Vec2d:
      output.precision(std::numeric_limits<double>::digits10);

      output << "Vec2d " << name << ' '
        << value.getFixed().vec2d.x << ' '
        << value.getFixed().vec2d.y << '\n';
      break;

    case ubt::Value::Type::Vec3u8:
      output << "Vec3u8 " << name << ' '
        << std::to_string(value.getFixed().vec3u8.x) << ' '
        << std::to_string(value.getFixed().vec3u8.y) << ' '
        << std::to_string(value.getFixed().vec3u8.z) << '\n';
      break;

    case ubt::Value::Type::Vec3u16:
      output << "Vec3u16 " << name << ' '
        << std::to_string(value.getFixed().vec3u16.x) << ' '
        << std::to_string(value.getFixed().vec3u16.y) << ' '
        << std::to_string(value.getFixed().vec3u16.z) << '\n';
      break;

    case ubt::Value::Type::Vec3u32:
      output << "Vec3u32 " << name << ' '
        << std::to_string(value.getFixed().vec3u32.x) << ' '
        << std::to_string(value.getFixed().vec3u32.y) << ' '
        << std::to_string(value.getFixed().vec3u32.z) << '\n';
      break;

    case ubt::Value::Type::Vec3u64:
      output << "Vec3u64 " << name << ' '
        << std::to_string(value.getFixed().vec3u64.x) << ' '
        << std::to_string(value.getFixed().vec3u64.y) << ' '
        << std::to_string(value.getFixed().vec3u64.z) << '\n';
      break;

    case ubt::Value::Type::Vec3i8:
      output << "Vec3i8 " << name << ' '
        << std::to_string(value.getFixed().vec3i8.x) << ' '
        << std::to_string(value.getFixed().vec3i8.y) << ' '
        << std::to_string(value.getFixed().vec3i8.z) << '\n';
      break;

    case ubt::Value::Type::Vec3i16:
      output << "Vec3i16 " << name << ' '
        << std::to_string(value.getFixed().vec3i16.x) << ' '
        << std::to_string(value.getFixed().vec3i16.y) << ' '
        << std::to_string(value.getFixed().vec3i16.z) << '\n';
      break;

    case ubt::Value::Type::Vec3i32:
      output << "Vec3i32 " << name << ' '
        << std::to_string(value.getFixed().vec3i32.x) << ' '
        << std::to_string(value.getFixed().vec3i32.y) << ' '
        << std::to_string(value.getFixed().vec3i32.z) << '\n';
      break;

    case ubt::Value::Type::Vec3i64:
      output << "Vec3i64 " << name << ' '
        << std::to_string(value.getFixed().vec3i64.x) << ' '
        << std::to_string(value.getFixed().vec3i64.y) << ' '
        << std::to_string(value.getFixed().vec3i64.z) << '\n';
      break;

    case ubt::Value::Type::Vec3f:
      output.precision(std::numeric_limits<float>::digits10);

      output << "Vec3f " << name << ' '
        << value.getFixed().vec3f.x << ' '
        << value.getFixed().vec3f.y << ' '
        << value.getFixed().vec3f.z << '\n';
      break;

    case ubt::Value::Type::Vec3d:
      output.precision(std::numeric_limits<double>::digits10);

      output << "Vec3d " << name << ' '
        << value.getFixed().vec3d.x << ' '
        << value.getFixed().vec3d.y << ' '
        << value.getFixed().vec3d.z << '\n';
      break;

    case ubt::Value::Type::String:
      output << "String " << name << " \"" << value.getString() << "\"\n";
      break;

    case ubt::Value::Type::Array:
      output << "Array " << name << '\n';

      for(auto& i : value.getArray()) {
        decompile(i, output, "", space + 1);
      }

      output << "ArrayEnd\n";
      break;

    case ubt::Value::Type::Object:
      output << "Object " << name << '\n';

      for(auto& [iKey, iVal] : value.getObject()) {
        decompile(iVal, output, iKey, space + 1);
      }

      output << "ObjectEnd\n";
      break;
  }
}

void decompile(ubt::Value& value, std::ostream& output) {
  decompile(value, output, "");
}

int main(int argc, char** argv) {
  if(argc < 2) {
  usage:
    std::cout << "Usage: " << argv[0] << " [-v] [-d] <input> [output]\n\t-v\tverbose\n\t-d\tdecompile instead\n\tinput\tinput file\n\toutput\toutput file" << std::endl;
    return EXIT_SUCCESS;
  }

  bool doDecompile = false;

  std::string filenameInput;
  std::string filenameOutput = "out.ubt";

  {
    int wordCount = 0;
    std::string arg;
    for(int i = 1; i < argc; ++i) {
      arg = argv[i];

      if(arg.front() == '-') {
        for(uintptr_t j = 1; j < arg.size(); ++j) {
          switch(arg[j]) {
            case 'v': beVerbose = true;   break;
            case 'd': doDecompile = true; break;
          }
        }
      }
      else {
        switch(wordCount++) {
          case 0: filenameInput = arg;  break;
          case 1: filenameOutput = arg; break;
        }
      }
    }

    if(wordCount == 0) {
      goto usage;
    }
  }


  if(doDecompile) {
    ubt::Document document;
    if(!document.load(filenameInput)) {
      std::cout << "Failed to load input." << std::endl;
      return EXIT_SUCCESS;
    }

    std::ofstream fileOutput(filenameOutput);
    if(!fileOutput) {
      std::cout << "Failed to open output file." << std::endl;
      return EXIT_FAILURE;
    }

    decompile(document, fileOutput);
    fileOutput.close();
  }
  else {
    std::ifstream fileInput(filenameInput);
    if(!fileInput) {
      std::cout << "Failed to open input file." << std::endl;
      return EXIT_FAILURE;
    }

    ubt::Document document;
    compile(fileInput, document);
    fileInput.close();

    if(!document.save(filenameOutput)) {
      std::cout << "Failed to save output." << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}