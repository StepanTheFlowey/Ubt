#include <iostream>
#include <fstream>
#include <set>
#include "switch.h"
#include "../Ubt/Document.hpp"

bool beVerbose = false;

void verbose(const std::string& message) {
  if(beVerbose) {
    std::cout << message;
  }
}

void compile(std::istream& input, ubt::Value& output, std::string& name) {

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

    std::string dummy;
    compile(fileInput, document, dummy);

    std::ofstream fileOutput(filenameOutput);
    if(!fileOutput) {
      std::cout << "Failed to open output file." << std::endl;
      return EXIT_FAILURE;
    }

    document.save(filenameOutput);
  }

  return EXIT_SUCCESS;
}