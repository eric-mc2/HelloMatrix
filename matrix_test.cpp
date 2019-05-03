#include <string>
#include "catch.hpp"
#include "matrix.h"

TEST_CASE("constructor") {
	SECTION("normal") {
		Matrix mat(1,1);
		std::string expected = "1x1";
    	REQUIRE(0 == expected.compare(mat.shape()));
    	REQUIRE(0 == mat.get(0,0)); // initializes to zero.
	}
	SECTION("huge malloc") {
// 		// TODO how do we test exception safety of constructor? c++ just kills the program
		REQUIRE_NOTHROW(Matrix(4500,100000));
	}
}
TEST_CASE("list constructor"){
	Matrix dummy(1,1);
	SECTION("good"){
		Matrix eye {{1,0,0},{0,1,0},{0,0,1}};
		std::string expected = "3x3";
    	REQUIRE(0 == expected.compare(eye.shape()));
    	for (int i = 0; i < 3; i++){
    		for (int j = 0; j < 3; j++) {
    			if (i == j){
    				REQUIRE(1 == eye.get(i,j));
    			} else {
    				REQUIRE(0 == eye.get(i,j));
    			}
    		}
    	}
	}
	SECTION("empty list"){
		REQUIRE_THROWS((Matrix {}));
	}
	SECTION("empty row"){
		REQUIRE_THROWS(Matrix {{}});
	}
	SECTION("unequal columns") {
		REQUIRE_THROWS(Matrix {{1,2},{1,2,3}});
	}
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
TEST_CASE("getter and setter"){
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
TEST_CASE("addition assignment operator") {
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
		Matrix b(2,3);
		Matrix c(2,3);
		b.set(0,0,42);
		b.set(0,1,42);
		b.set(0,2,42);
		b.set(1,0,42);
		b.set(1,1,42);
		b.set(1,2,42);
		c.set(0,0,2);
		c.set(0,1,4);
		c.set(0,2,6);
		c.set(1,0,8);
		c.set(1,1,10);
		c.set(1,2,12);
		REQUIRE_NOTHROW(c += b);
		REQUIRE(44 == c.get(0,0));
		REQUIRE(46 == c.get(0,1));
		REQUIRE(48 == c.get(0,2));
		REQUIRE(50 == c.get(1,0));
		REQUIRE(52 == c.get(1,1));
		REQUIRE(54 == c.get(1,2));
	}
}
TEST_CASE("subtraction assignment operator") {
	Matrix a(1,1);
	SECTION("cant subtract different heights"){
		Matrix b(2,1);
		REQUIRE_THROWS(a -= b);
	}
	SECTION("cant subtract different widths"){
		Matrix b(1,2);
		REQUIRE_THROWS(a -= b);
	}
	SECTION("can subtract same shape"){
		Matrix b(2,3);
		Matrix c(2,3);
		b.set(0,0,42);
		b.set(0,1,42);
		b.set(0,2,42);
		b.set(1,0,42);
		b.set(1,1,42);
		b.set(1,2,42);
		c.set(0,0,2);
		c.set(0,1,4);
		c.set(0,2,6);
		c.set(1,0,8);
		c.set(1,1,10);
		c.set(1,2,12);
		REQUIRE_NOTHROW(b -= c);
		REQUIRE(40 == b.get(0,0));
		REQUIRE(38 == b.get(0,1));
		REQUIRE(36 == b.get(0,2));
		REQUIRE(34 == b.get(1,0));
		REQUIRE(32 == b.get(1,1));
		REQUIRE(30 == b.get(1,2));
	}
}
TEST_CASE("scalar multiplication assignment operator"){
	Matrix a(2,3);
	Matrix b(2,3);
	a*=3;
	REQUIRE(a == b);
	Matrix c({{1,1},{1,1},{1,1}});
	c*=0;
	REQUIRE(c == b);
	Matrix d({{1,0},{0,1}});
	d*=3;
	Matrix e({{3,0},{0,3}});
	REQUIRE(d == e);
	Matrix f({{-3,0},{0,-3}});
	d*=-1;
	REQUIRE(d == f);
}
TEST_CASE("addition operator"){
	Matrix a(2,2);
	Matrix b = a+a;
	REQUIRE(b == a);
	Matrix c({{1,2,3},{4,5,6}});
	Matrix d({{-1,-1,-1},{-1,-1,-1}});
	Matrix e({{0,1,2},{3,4,5}});
	REQUIRE (e == (c+d));
	REQUIRE_THROWS(a+c);
}
TEST_CASE("subtraction operator"){
	Matrix a(2,2);
	Matrix b = a-a;
	REQUIRE(b == a);
	Matrix c({{1,2,3},{4,5,6}});
	Matrix d({{-1,-1,-1},{-1,-1,-1}});
	Matrix e({{0,1,2},{3,4,5}});
	REQUIRE ((e-d) == c);
	REQUIRE_THROWS(a-c);
}
TEST_CASE("matrix multiplication operator"){
	Matrix a(2,2);
	Matrix b(2,1);
	REQUIRE_NOTHROW(a*b);
	REQUIRE_THROWS(b*a);
	Matrix eye({{1,0,0},{0,1,0},{0,0,1}});
	Matrix c({{2,4,6},{1,0,2},{0,2,5}});
	REQUIRE (c == (eye*c));
	REQUIRE (c == (c*eye));
	Matrix p({{0,1,0},{1,0,0},{0,0,1}});
	Matrix d({{1,0,2},{2,4,6},{0,2,5}});
	Matrix foo = (p*d);
	std::cout << foo << "\n";
	REQUIRE (c == p*d);
	REQUIRE (c != d*p);
}
TEST_CASE("scalar multiplication operator"){
	Matrix a(4,5);
	Matrix b = a * 22;
	REQUIRE(a == b);
	Matrix c({{1,2},{3,4}});
	Matrix e({{5,10},{15,20}});
	Matrix d = c * 5;
	REQUIRE(d == e);
	Matrix f(2,2);
	Matrix g = d*0;
	REQUIRE(f == g);
}
TEST_CASE("equality operator"){
	Matrix a {{0,0}};
	SECTION("different shape"){
		Matrix b {{0},{0}};
		REQUIRE_FALSE(a==b);
		REQUIRE_FALSE(b==a);
	}
	SECTION("via copy constructor"){
		Matrix b(a);
		REQUIRE(a==b);
		REQUIRE(b==a);
	}
	SECTION("via assignment"){
		Matrix b(3,3);
		b = a;
		REQUIRE(a==b);
		REQUIRE(b==a);
	}
	SECTION("different values"){
		Matrix b{{0,1}};
		REQUIRE_FALSE(a==b);
		REQUIRE_FALSE(b==a);
	}
	SECTION("same values"){
		Matrix b{{1,0},{0,1}};
		Matrix c{{1,0},{0,0}};
		c.set(1,1,1);
		REQUIRE(b==c);
		REQUIRE(c==b);
	}
}
TEST_CASE("inequality operator"){
	Matrix a {{0,0}};
	SECTION("different shape"){
		Matrix b {{0},{0}};
		REQUIRE(a!=b);
		REQUIRE(b!=a);
	}
	SECTION("via copy constructor"){
		Matrix b(a);
		REQUIRE_FALSE(a!=b);
		REQUIRE_FALSE(b!=a);
	}
	SECTION("via assignment"){
		Matrix b(3,3);
		b = a;
		REQUIRE_FALSE(a!=b);
		REQUIRE_FALSE(b!=a);
	}
	SECTION("different values"){
		Matrix b{{0,1}};
		REQUIRE(a!=b);
		REQUIRE(b!=a);
	}
	SECTION("same values"){
		Matrix b{{1,0},{0,1}};
		Matrix c{{1,0},{0,0}};
		c.set(1,1,1);
		REQUIRE_FALSE(b!=c);
		REQUIRE_FALSE(c!=b);
	}
}