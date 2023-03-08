#include <stdexcept>
#include <iostream>
#include <fstream>
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
  std::string name;

  if(!doReadTagName) {
    return name;
  }

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
      verbose("Type Null");
      name = compileName(input);
      output.setType(ubt::Value::Type::Null);
      break;

    case strHashSwitch("Bool"):
    case strHashSwitch("Boolean"):
      verbose("Type Boolean");
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
      verbose("Type Uint8");
      name = compileName(input);

      input >> word;
      fixed.uint8 = std::stoi(word);

      output.setType(ubt::Value::Type::Uint8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint16"):
      verbose("Type Uint16");
      name = compileName(input);

      input >> word;
      fixed.uint16 = std::stoi(word);

      output.setType(ubt::Value::Type::Uint16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint32"):
      verbose("Type Uint32");
      name = compileName(input);

      input >> word;
      fixed.uint32 = std::stoul(word);

      output.setType(ubt::Value::Type::Uint32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Uint64"):
      verbose("Type Uint64");
      name = compileName(input);

      input >> word;
      fixed.uint64 = std::stoull(word);

      output.setType(ubt::Value::Type::Uint64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int8"):
      verbose("Type Int8");
      name = compileName(input);

      input >> word;
      fixed.int8 = std::stoi(word);

      output.setType(ubt::Value::Type::Int8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int16"):
      verbose("Type Int16");
      name = compileName(input);

      input >> word;
      fixed.int16 = std::stoi(word);

      output.setType(ubt::Value::Type::Int16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int32"):
      verbose("Type Int32");
      name = compileName(input);

      input >> word;
      fixed.int32 = std::stol(word);

      output.setType(ubt::Value::Type::Int32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Int64"):
      verbose("Type Int64");
      name = compileName(input);

      input >> word;
      fixed.int64 = std::stoll(word);

      output.setType(ubt::Value::Type::Int64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Real32"):
      verbose("Type Real32");
      name = compileName(input);

      input >> word;
      fixed.real32 = std::stof(word);

      output.setType(ubt::Value::Type::Real32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Real64"):
      verbose("Type Real64");
      name = compileName(input);

      input >> word;
      fixed.real64 = std::stod(word);

      output.setType(ubt::Value::Type::Real64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2u8"):
      verbose("Type Vec2u8");
      name = compileName(input);

      input >> word;
      fixed.vec2u8.x = std::stoi(word);

      input >> word;
      fixed.vec2u8.y = std::stoi(word);

      output.setType(ubt::Value::Type::Vec2u8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2u16"):
      verbose("Type Vec2u16");
      name = compileName(input);

      input >> word;
      fixed.vec2u16.x = std::stoi(word);

      input >> word;
      fixed.vec2u16.y = std::stoi(word);

      output.setType(ubt::Value::Type::Vec2u16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2u32"):
      verbose("Type Vec2u32");
      name = compileName(input);

      input >> word;
      fixed.vec2u32.x = std::stoul(word);

      input >> word;
      fixed.vec2u32.y = std::stoul(word);

      output.setType(ubt::Value::Type::Vec2u32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2u64"):
      verbose("Type Vec2u64");
      name = compileName(input);

      input >> word;
      fixed.vec2u64.x = std::stoull(word);

      input >> word;
      fixed.vec2u64.y = std::stoull(word);

      output.setType(ubt::Value::Type::Vec2u64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2i8"):
      verbose("Type Vec2i8");
      name = compileName(input);

      input >> word;
      fixed.vec2i8.x = std::stoi(word);

      input >> word;
      fixed.vec2i8.y = std::stoi(word);

      output.setType(ubt::Value::Type::Vec2i8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2i16"):
      verbose("Type Vec2i16");
      name = compileName(input);

      input >> word;
      fixed.vec2i16.x = std::stoi(word);

      input >> word;
      fixed.vec2i16.y = std::stoi(word);

      output.setType(ubt::Value::Type::Vec2i16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2i32"):
      verbose("Type Vec2i32");
      name = compileName(input);

      input >> word;
      fixed.vec2i32.x = std::stol(word);

      input >> word;
      fixed.vec2i32.y = std::stol(word);

      output.setType(ubt::Value::Type::Vec2i32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2i64"):
      verbose("Type Vec2i64");
      name = compileName(input);

      input >> word;
      fixed.vec2i64.x = std::stoll(word);

      input >> word;
      fixed.vec2i64.y = std::stoll(word);

      output.setType(ubt::Value::Type::Vec2i64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2r32"):
      verbose("Type Vec2r32");
      name = compileName(input);

      input >> word;
      fixed.vec2r32.x = std::stof(word);

      input >> word;
      fixed.vec2r32.y = std::stof(word);

      output.setType(ubt::Value::Type::Vec2r32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec2r64"):
      verbose("Type Vec2r64");
      name = compileName(input);

      input >> word;
      fixed.vec2r64.x = std::stod(word);

      input >> word;
      fixed.vec2r64.y = std::stod(word);

      output.setType(ubt::Value::Type::Vec2r64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3u8"):
      verbose("Type Vec3u8");
      name = compileName(input);

      input >> word;
      fixed.vec3u8.x = std::stoi(word);

      input >> word;
      fixed.vec3u8.y = std::stoi(word);

      input >> word;
      fixed.vec3u8.z = std::stoi(word);

      output.setType(ubt::Value::Type::Vec3u8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3u16"):
      verbose("Type Vec3u16");
      name = compileName(input);

      input >> word;
      fixed.vec3u16.x = std::stoi(word);

      input >> word;
      fixed.vec3u16.y = std::stoi(word);

      input >> word;
      fixed.vec3u16.z = std::stoi(word);

      output.setType(ubt::Value::Type::Vec3u16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3u32"):
      verbose("Type Vec3u32");
      name = compileName(input);

      input >> word;
      fixed.vec3u32.x = std::stoul(word);

      input >> word;
      fixed.vec3u32.y = std::stoul(word);

      input >> word;
      fixed.vec3u32.z = std::stoul(word);

      output.setType(ubt::Value::Type::Vec3u32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3u64"):
      verbose("Type Vec3u64");
      name = compileName(input);

      input >> word;
      fixed.vec3u64.x = std::stoull(word);

      input >> word;
      fixed.vec3u64.y = std::stoull(word);

      input >> word;
      fixed.vec3u64.z = std::stoull(word);

      output.setType(ubt::Value::Type::Vec3u64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3i8"):
      verbose("Type Vec3i8");
      name = compileName(input);

      input >> word;
      fixed.vec3i8.x = std::stoi(word);

      input >> word;
      fixed.vec3i8.y = std::stoi(word);

      input >> word;
      fixed.vec3i8.z = std::stoi(word);

      output.setType(ubt::Value::Type::Vec3i8);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3i16"):
      verbose("Type Vec3i16");
      name = compileName(input);

      input >> word;
      fixed.vec3i16.x = std::stoi(word);

      input >> word;
      fixed.vec3i16.y = std::stoi(word);

      input >> word;
      fixed.vec3i16.z = std::stoi(word);

      output.setType(ubt::Value::Type::Vec3i16);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3i32"):
      verbose("Type Vec3i32");
      name = compileName(input);

      input >> word;
      fixed.vec3i32.x = std::stol(word);

      input >> word;
      fixed.vec3i32.y = std::stol(word);

      input >> word;
      fixed.vec3i32.z = std::stol(word);

      output.setType(ubt::Value::Type::Vec3i32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3i64"):
      verbose("Type Vec3i64");
      name = compileName(input);

      input >> word;
      fixed.vec3i64.x = std::stoll(word);

      input >> word;
      fixed.vec3i64.y = std::stoll(word);

      input >> word;
      fixed.vec3i64.z = std::stoll(word);

      output.setType(ubt::Value::Type::Vec3i64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3r32"):
      verbose("Type Vec3r32");
      name = compileName(input);

      input >> word;
      fixed.vec3r32.x = std::stof(word);

      input >> word;
      fixed.vec3r32.y = std::stof(word);

      input >> word;
      fixed.vec3r32.z = std::stof(word);

      output.setType(ubt::Value::Type::Vec3r32);
      output.setFixed(fixed);
      break;

    case strHashSwitch("Vec3r64"):
      verbose("Type Vec3r64");
      name = compileName(input);

      input >> word;
      fixed.vec3r64.x = std::stod(word);

      input >> word;
      fixed.vec3r64.y = std::stod(word);

      input >> word;
      fixed.vec3r64.z = std::stod(word);

      output.setType(ubt::Value::Type::Vec3r64);
      output.setFixed(fixed);
      break;

    case strHashSwitch("String"):
      verbose("Type String");
      name = compileName(input);

      output.setType(ubt::Value::Type::String);
      {
        char ch = input.get();
        if(ch != '\"') {
          throw std::runtime_error("string scope not beginned");
        }

        input.get(ch);
        while(ch != '\"') {
          if(input.eof()) {
            throw std::runtime_error("unexpected eof");
          }
          word.push_back(ch);
          input.get(ch);
        }
      }
      output.setString(word);
      break;

    case strHashSwitch("Array"):
      verbose("Type Array");
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
            throw std::runtime_error("unexpected eof");
          }

          output.getArray().push_back(value);

          compile(input, value, word);
          doReadTagName = false;
        }
      }
      doReadTagName = true;
      break;

    case strHashSwitch("ArrayEnd"):
      verbose("Type ArrayEnd");
      output.setType(ubt::Value::Type::ArrayEnd);
      break;

    case strHashSwitch("Object"):
      verbose("Type Object");
      name = compileName(input);

      output.setType(ubt::Value::Type::Object);

      {
        ubt::Value value;
        compile(input, value, word);
        while(value.getType() != ubt::Value::Type::ObjectEnd) {
          if(input.eof()) {
            throw std::runtime_error("unexpected eof");
          }
          output[word] = value;
          compile(input, value, word);
        }
      }
      break;

    case strHashSwitch("ObjectEnd"):
      verbose("Type ObjectEnd");
      output.setType(ubt::Value::Type::ObjectEnd);
      break;

    default:
      throw std::range_error(word + " is not known type");
  }
}

void compile(std::istream& input, ubt::Value& output) {
  std::string name;

  compile(input, output, name);
}

void decompile(ubt::Value& value, std::ostream& output, const std::string& name, unsigned space = 0) {
  output << std::string(space * 2, ' ');

  switch(value.getType()) {
    case ubt::Value::Type::Null:
      output << "Null " << name << '\n';
      break;

    case ubt::Value::Type::Uint8:
      output << "Uint8 " << name << ' ' << static_cast<unsigned>(value.getFixed().uint8) << '\n';
      break;

    case ubt::Value::Type::Uint16:
      output << "Uint16 " << name << ' ' << value.getFixed().uint16 << '\n';
      break;

    case ubt::Value::Type::Uint32:
      output << "Uint32 " << name << ' ' << value.getFixed().uint32 << '\n';
      break;

    case ubt::Value::Type::Uint64:
      output << "Uint64 " << name << ' ' << value.getFixed().uint64 << '\n';
      break;

    case ubt::Value::Type::Int8:
      output << "Int8 " << name << ' ' << static_cast<int>(value.getFixed().int8) << '\n';
      break;

    case ubt::Value::Type::Int16:
      output << "Int16 " << name << ' ' << value.getFixed().int16 << '\n';
      break;

    case ubt::Value::Type::Int32:
      output << "Int32 " << name << ' ' << value.getFixed().int32 << '\n';
      break;

    case ubt::Value::Type::Int64:
      output << "Int64 " << name << ' ' << value.getFixed().int64 << '\n';
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
        << static_cast<unsigned>(value.getFixed().vec2u8.x) << ' '
        << static_cast<unsigned>(value.getFixed().vec2u8.y) << '\n';
      break;

    case ubt::Value::Type::Vec2u16:
      output << "Vec2u16 " << name << ' '
        << value.getFixed().vec2u16.x << ' '
        << value.getFixed().vec2u16.y << '\n';
      break;

    case ubt::Value::Type::Vec2u32:
      output << "Vec2u32 " << name << ' '
        << value.getFixed().vec2u32.x << ' '
        << value.getFixed().vec2u32.y << '\n';
      break;

    case ubt::Value::Type::Vec2u64:
      output << "Vec2u64 " << name << ' '
        << value.getFixed().vec2u64.x << ' '
        << value.getFixed().vec2u64.y << '\n';
      break;

    case ubt::Value::Type::Vec2i8:
      output << "Vec2i8 " << name << ' '
        << static_cast<int>(value.getFixed().vec2i8.x) << ' '
        << static_cast<int>(value.getFixed().vec2i8.y) << '\n';
      break;

    case ubt::Value::Type::Vec2i16:
      output << "Vec2i16 " << name << ' '
        << value.getFixed().vec2i16.x << ' '
        << value.getFixed().vec2i16.y << '\n';
      break;

    case ubt::Value::Type::Vec2i32:
      output << "Vec2i32 " << name << ' '
        << value.getFixed().vec2i32.x << ' '
        << value.getFixed().vec2i32.y << '\n';
      break;

    case ubt::Value::Type::Vec2i64:
      output << "Vec2i64 " << name << ' '
        << value.getFixed().vec2i64.x << ' '
        << value.getFixed().vec2i64.y << '\n';
      break;

    case ubt::Value::Type::Vec2r32:
      output.precision(std::numeric_limits<float>::digits10);

      output << "Vec2r32 " << name << ' '
        << value.getFixed().vec2r32.x << ' '
        << value.getFixed().vec2r32.y << '\n';
      break;

    case ubt::Value::Type::Vec2r64:
      output.precision(std::numeric_limits<double>::digits10);

      output << "Vec2r64 " << name << ' '
        << value.getFixed().vec2r64.x << ' '
        << value.getFixed().vec2r64.y << '\n';
      break;

    case ubt::Value::Type::Vec3u8:
      output << "Vec3u8 " << name << ' '
        << static_cast<unsigned>(value.getFixed().vec3u8.x) << ' '
        << static_cast<unsigned>(value.getFixed().vec3u8.y) << ' '
        << static_cast<unsigned>(value.getFixed().vec3u8.z) << '\n';
      break;

    case ubt::Value::Type::Vec3u16:
      output << "Vec3u16 " << name << ' '
        << value.getFixed().vec3u16.x << ' '
        << value.getFixed().vec3u16.y << ' '
        << value.getFixed().vec3u16.z << '\n';
      break;

    case ubt::Value::Type::Vec3u32:
      output << "Vec3u32 " << name << ' '
        << value.getFixed().vec3u32.x << ' '
        << value.getFixed().vec3u32.y << ' '
        << value.getFixed().vec3u32.z << '\n';
      break;

    case ubt::Value::Type::Vec3u64:
      output << "Vec3u64 " << name << ' '
        << value.getFixed().vec3u64.x << ' '
        << value.getFixed().vec3u64.y << ' '
        << value.getFixed().vec3u64.z << '\n';
      break;

    case ubt::Value::Type::Vec3i8:
      output << "Vec3i8 " << name << ' '
        << static_cast<int>(value.getFixed().vec3i8.x) << ' '
        << static_cast<int>(value.getFixed().vec3i8.y) << ' '
        << static_cast<int>(value.getFixed().vec3i8.z) << '\n';
      break;

    case ubt::Value::Type::Vec3i16:
      output << "Vec3i16 " << name << ' '
        << value.getFixed().vec3i16.x << ' '
        << value.getFixed().vec3i16.y << ' '
        << value.getFixed().vec3i16.z << '\n';
      break;

    case ubt::Value::Type::Vec3i32:
      output << "Vec3i32 " << name << ' '
        << value.getFixed().vec3i32.x << ' '
        << value.getFixed().vec3i32.y << ' '
        << value.getFixed().vec3i32.z << '\n';
      break;

    case ubt::Value::Type::Vec3i64:
      output << "Vec3i64 " << name << ' '
        << value.getFixed().vec3i64.x << ' '
        << value.getFixed().vec3i64.y << ' '
        << value.getFixed().vec3i64.z << '\n';
      break;

    case ubt::Value::Type::Vec3r32:
      output.precision(std::numeric_limits<float>::digits10);

      output << "Vec3r32 " << name << ' '
        << value.getFixed().vec3r32.x << ' '
        << value.getFixed().vec3r32.y << ' '
        << value.getFixed().vec3r32.z << '\n';
      break;

    case ubt::Value::Type::Vec3r64:
      output.precision(std::numeric_limits<double>::digits10);

      output << "Vec3r64 " << name << ' '
        << value.getFixed().vec3r64.x << ' '
        << value.getFixed().vec3r64.y << ' '
        << value.getFixed().vec3r64.z << '\n';
      break;

    case ubt::Value::Type::String:
      output << "String " << name << " \"" << value.getString() << "\"\n";
      break;

    case ubt::Value::Type::Array:
      output << "Array " << name << '\n';

      for(auto& i : value.getArray()) {
        decompile(i, output, "", space + 1);
      }

      output << std::string(space * 2, ' ') << "ArrayEnd\n";
      break;

    case ubt::Value::Type::Object:
      output << "Object " << name << '\n';

      for(auto& [iKey, iVal] : value.getObject()) {
        decompile(iVal, output, iKey, space + 1);
      }

      output << std::string(space * 2, ' ') << "ObjectEnd\n";
      break;

    default:
      throw std::range_error(std::to_string(static_cast<unsigned>(value.getType())) + " is not known type");
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
  std::string filenameOutput;

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

  try {
    if(doDecompile) {
      ubt::Document document;
      if(!document.loadFromFile(filenameInput)) {
        std::cout << "Failed to load input." << std::endl;
        return EXIT_SUCCESS;
      }

      if(filenameOutput.empty()) {
        filenameOutput = "out.txt";
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

      if(filenameOutput.empty()) {
        filenameOutput = "out.ubt";
      }

      if(!document.saveToFile(filenameOutput)) {
        std::cout << "Failed to save output." << std::endl;
        return EXIT_FAILURE;
      }
    }
  }
  catch(const std::range_error& e) {
    std::cout << "Range error: " << e.what() << '.' << std::endl;
    return EXIT_FAILURE;
  }
  catch(const std::runtime_error& e) {
    std::cout << "Runtime error: " << e.what() << '.' << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}