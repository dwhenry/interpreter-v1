#include "catch.hpp"
#include "../src/interpreter.h"

TEST_CASE("Simple interpreter", "[int]") {
  Interpreter * interpreter = new Interpreter();

  SECTION("Addition") {
    CHECK( interpreter->process("1+2") == "3" );
    CHECK( interpreter->process("1 + 2") == "3" );
    CHECK( interpreter->process("12 +24") == "36" );
    CHECK_THROWS_WITH(
      interpreter->process("+ 1"),
      Catch::Contains( "Invalid token: +" )
    );

    CHECK_THROWS_WITH(
      interpreter->process("1 1"),
      Catch::Contains( "Expected 'EOF' got: 1" )
    );
  }

  SECTION("Negation") {
    CHECK( interpreter->process("1-2") == "-1" );
    CHECK( interpreter->process("2 - 1") == "1" );
    CHECK( interpreter->process("12 -24") == "-12" );
  }

  SECTION("Multiplication") {
    CHECK( interpreter->process("3*2") == "6" );
  }

  SECTION("Division") {
    CHECK( interpreter->process("6/2") == "3" );
    CHECK( interpreter->process("7/2") == "3" );
  }

  SECTION("Precedence of multiplication/division over addition/subtraction") {
    CHECK( interpreter->process("1 + 6 * 2") == "13" );
    CHECK( interpreter->process("10 - 20 / 4") == "5" );
    CHECK_THROWS_WITH(
      interpreter->process("1 *"),
      Catch::Contains( "Invalid token: " )
    );
  }

  SECTION("Brackets and stuff") {
    CHECK( interpreter->process("(1 + 6)") == "7" );
    CHECK( interpreter->process("(1+ 6) * 2") == "14" );
    CHECK_THROWS_WITH(
      interpreter->process("(1+ 6"),
      Catch::Contains( "Expected ')' got: " )
    );

  }

}
