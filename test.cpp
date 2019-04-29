#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.hpp"
#include "matrix.h"

TEST_CASE("constructor") {
	Matrix mat(1,1);
	std::string expected = "1x1";
    REQUIRE(0 == expected.compare(mat.shape()));
}
