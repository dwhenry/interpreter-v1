#include "catch.hpp"
#include "../src/parser.h"

TEST_CASE("Simple parser", "[int]") {
  Parser * parser = new Parser();

  SECTION("Addition") {
    CHECK( parser->process("1+2") == "3" );
    CHECK( parser->process("1 + 2") == "3" );
    CHECK( parser->process("12 +24") == "36" );
    CHECK_THROWS_WITH(
      parser->process("+ 1"),
      Catch::Contains( "Invalid token: +" )
    );

    CHECK_THROWS_WITH(
      parser->process("1 1"),
      Catch::Contains( "Expected 'EOF' got: 1" )
    );
  }

  SECTION("Negation") {
    CHECK( parser->process("1-2") == "-1" );
    CHECK( parser->process("2 - 1") == "1" );
    CHECK( parser->process("12 -24") == "-12" );
  }

  SECTION("Multiplication") {
    CHECK( parser->process("3*2") == "6" );
  }

  SECTION("Division") {
    CHECK( parser->process("6/2") == "3" );
    CHECK( parser->process("7/2") == "3" );
  }

  SECTION("Precedence of multiplication/division over addition/subtraction") {
    CHECK( parser->process("1 + 6 * 2") == "13" );
    CHECK( parser->process("10 - 20 / 4") == "5" );
    CHECK_THROWS_WITH(
      parser->process("1 *"),
      Catch::Contains( "Invalid token: " )
    );
  }

  SECTION("Brackets and stuff") {
    CHECK( parser->process("(1 + 6)") == "7" );
    CHECK( parser->process("(1+ 6) * 2") == "14" );
    CHECK_THROWS_WITH(
      parser->process("(1+ 6"),
      Catch::Contains( "Expected ')' got: " )
    );

  }

}
