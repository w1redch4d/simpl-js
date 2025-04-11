#include <iostream>
#include "jslib/token.h"

int main(int argc, char* argv[]) {
    jslib::internal::Token token;
    if (argc < 2) {
      std::cout << "Usage: " << argv[0] << " " << "[script]\n";
      std::exit(1);
    } else if (argc == 2) {
      std::cout << "Supplied arg: " <<  token.StringToName(argv[1]) << std::endl;
    } else {
      exit(1);
    }
}