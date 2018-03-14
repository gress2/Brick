# AST

### Building
```Bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
### Building with tests
```Bash
git submodule update --init --recursive
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DMAKE_TESTS=ON ..
make
```
### Running unit tests
```Bash
./Release/bin/unit_tests
```
