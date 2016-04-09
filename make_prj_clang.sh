rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake
cmake cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ .
make
