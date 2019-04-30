#include <string>
#include "catch.hpp"
#include "matrix.h"

TEST_CASE("constructor") {
	Matrix mat(1,1);
	std::string expected = "1x1";
    REQUIRE(0 == expected.compare(mat.shape()));
    REQUIRE(0 == mat.get(0,0)); // initializes to zero.
}
TEST_CASE("copy constructor"){
	Matrix a(1,1);
	a.set(0,0,42);
	Matrix b(a);
	REQUIRE(42 == b.get(0,0)); // initializes to rhs
	a.set(0,0,43);
	REQUIRE(42 == b.get(0,0)); // points to different obj
}
TEST_CASE("assignment operator"){
	Matrix a(2,3);
	a.set(1,2,42);
	Matrix b(1,1);
	b.set(0,0,43);
	SECTION("assert data copied") {
		b = a;
		REQUIRE(2 == b.nrows());
		REQUIRE(3 == b.ncols());
		REQUIRE(0 == b.get(0,0));
		REQUIRE(42 == b.get(1,2));
	}
	SECTION("points to different obj") {
		Matrix c(1,1);
		c = b;
		b = a; // destroys b's data
		c.get(0,0); // if c points to new data, this wont crash
	}
}
TEST_CASE("can get set"){
	Matrix m(2,5);
	SECTION("negative row"){
		REQUIRE_THROWS(m.get(-1,2));
		REQUIRE_THROWS(m.set(-1,2,3));
	}
	SECTION("negative col"){
		REQUIRE_THROWS(m.get(1,-2));
		REQUIRE_THROWS(m.set(1,-2,3));
	}
	SECTION("row out of range"){
		REQUIRE_THROWS(m.get(2,2));
		REQUIRE_THROWS(m.set(2,2,3));
	}
	SECTION("col out of range"){
		REQUIRE_THROWS(m.get(1,5));
		REQUIRE_THROWS(m.set(1,5,3));
	}
	SECTION("valid"){
		REQUIRE_NOTHROW(m.set(0,0,7));
		REQUIRE_NOTHROW(m.set(0,3,8));
		REQUIRE_NOTHROW(m.set(1,4,9));
		REQUIRE_NOTHROW(m.get(0,0));
		REQUIRE_NOTHROW(m.get(0,3));
		REQUIRE_NOTHROW(m.get(1,4));
		REQUIRE(7 == m.get(0,0));
		REQUIRE(8 == m.get(0,3));
		REQUIRE(9 == m.get(1,4));
	}
}
TEST_CASE("plus equals") {
	Matrix a(1,1);
	SECTION("cant add different heights"){
		Matrix b(2,1);
		REQUIRE_THROWS(a += b);
	}
	SECTION("cant add different widths"){
		Matrix b(1,2);
		REQUIRE_THROWS(a += b);
	}
	SECTION("can add same shape"){
		Matrix b(1,1);
		b.set(0,0,2);
		REQUIRE_NOTHROW(a += b);
		REQUIRE(2 == a.get(0,0));
	}
}