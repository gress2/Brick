# Brick

## Setup

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

## Generating and viewing graph visualizations
```parser``` and ```transformer``` can both output .gv graph descriptor files. 
These files may be used to generate PostScript files which are then viewable.

```Bash
./scripts/viz <PATH TO .GV FILE>
```
