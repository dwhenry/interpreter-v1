#include "interpreter.h"
#include <iostream>
#include <string>

int main( int argc, char * argv[] ) {
  std::string command;
  Interpreter * interpreter = new Interpreter();
  while(true) {
    std::cout << "Enter command tio process (exit to quit): ";
    std::cin >> command;
    if(command == "exit") return 0;
    std::cout << interpreter->process(command);
  }
}
