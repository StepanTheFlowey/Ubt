#include <iostream>
#include "../Ubt/Document.hpp"

int main(int argc, char** argv) {
  if(argc < 2) {
  usage:
    std::cout << "Usage: " << argv[0] << " [-v] [-d] <input> [output]\n\t-v\tverbose\n\t-d\tdecompile instead\n\tinput\tinput file\n\toutput\toutput file" << std::endl;
    return EXIT_SUCCESS;
  }

  bool verbose = false;
  bool decompile = false;

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
            case 'v': verbose = true;   break;
            case 'd': decompile = true; break;
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


}