#include <iostream>
#include <fstream>
#include <set>
#include "switch.h"
#include "../Ubt/Document.hpp"

bool beVerbose = false;

void verbose(const std::string& message) {
  if(beVerbose) {
    std::cout << message << '\n';
  }
}

std::string compileName(std::istream& input) {
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

    case strHashSwitch("Object"):
    verbose("Tag Object");
    name = compileName(input);

    output.setType(ubt::Value::Type::Object);

    {
      ubt::Value value;
      do {
        compile(input, value, word);
        output[word] = value;
      } while(value.getType() != ubt::Value::Type::ObjectEnd);
    }
    break;

    case strHashSwitch("ObjectEnd"):
    verbose("Tag ObjectEnd");
    output.setType(ubt::Value::Type::ObjectEnd);
    break;
  }
}

void compile(std::istream& input, ubt::Value& output) {
  std::string name;

  compile(input, output, name);
}

void decompile(std::istream& input, std::ostream& output) {

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

  }
  else {
    ubt::Document document;
    std::ifstream fileInput(filenameInput);
    if(!fileInput) {
      std::cout << "Failed to open input file." << std::endl;
      return EXIT_FAILURE;
    }

    compile(fileInput, document);

    std::ofstream fileOutput(filenameOutput);
    if(!fileOutput) {
      std::cout << "Failed to open output file." << std::endl;
      return EXIT_FAILURE;
    }

    document.save(filenameOutput);
  }

  return EXIT_SUCCESS;
}