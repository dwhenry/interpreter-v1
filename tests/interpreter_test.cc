#include "catch.hpp"
#include "../src/interpreter.h"

TEST_CASE("Simple interpreter", "[int]") {
  Interpreter * interpreter = new Interpreter();

  SECTION("Addition") {
    CHECK( interpreter->process("1+2") == "Result of 1+2 is: 3" );
    CHECK( interpreter->process("1 + 2") == "Result of 1 + 2 is: 3" );
    CHECK( interpreter->process("12 +24") == "Result of 12 +24 is: 36" );
  }

  SECTION("Negation") {
    CHECK( interpreter->process("1-2") == "Result of 1-2 is: -1" );
    CHECK( interpreter->process("2 - 1") == "Result of 2 - 1 is: 1" );
    CHECK( interpreter->process("12 -24") == "Result of 12 -24 is: -12" );
  }

  SECTION("Multiplication") {
    CHECK( interpreter->process("3*2") == "Result of 3*2 is: 6" );
  }

  SECTION("Division") {
    CHECK( interpreter->process("6/2") == "Result of 6/2 is: 3" );
    CHECK( interpreter->process("7/2") == "Result of 7/2 is: 3" );
  }

  SECTION("Precedence of multiplication/division over addition/subtraction") {
    CHECK( interpreter->process("1 + 6 * 2") == "Result of 1 + 6 * 2 is: 13" );
    CHECK( interpreter->process("10 - 20 / 4") == "Result of 10 - 20 / 4 is: 5" );
  }
}
