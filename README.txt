Project Layout:
/
- maybe a makefile will go here
- maybe a gitignore will go here
- maybe CMake to create our
/bin/
    - executables compiled to here
/build/
    - object files compiled to here
/doc/
    - documentation
/include/
    /projectname/
        - header file for exposing public api
/lib/
    - third party libraries
    - (c++ libs are included as source??)
    - (is there no maven for c++?)
/src/
    - headers for private + protected code
    - source code
/test/
    - tests
    
Compiling & Linking:
    Suppose main.cpp requires a.cpp and b.cpp.
    g++ -c *.cpp # compiling
    g++ *.o -o binary # linking
    