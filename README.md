
# paint-piet

The goal of this project is to create a collection of tools and libraries to
run and create programs, using
[Piet](https://www.dangermouse.net/esoteric/piet.html) language.

# Features

- Interpret and run commands from `.png` files (1 pixel = 1 codel pixel)

# Usage 

Download last version from [releases](https://github.com/lunaro-4/paint-piet/releases) 
and execute it from command line
``` bash
paint-piet /path/to/file.png
```

# Building from source

## Prerequisites

Ensure you have the following libraries:

- [libpng](http://www.libpng.org/pub/png/libpng.html) - decodes `png`
- [zlib](https://github.com/madler/zlib) - required by `libpng`
- [make](https://www.gnu.org/software/make/) and [cmake](https://cmake.org/) - for compiling
- (optional) [check](https://github.com/libcheck/check) - for testing

## Compiling
Clone the repo:
``` bash
git clone https://github.com/lunaro-4/paint-piet
cd paint-piet
```
Build the `Makefile` and `Make` it!
``` bash
cmake .
make 
```
If you do not have `check` library installed, use `make main` instead of `make`

The executable should be in `out` folder

# Features to be implemented

- [ ] Interpretation
    - [ ] Support for enlarged images
    - [ ] Support for more formats, such as `.gif`
- [ ] GUI
    - [ ] Code live preview
    - [ ] Debugging tools
    - [ ] command highliting
- [ ] Extract libraries for external use


# Copyright and support

This project is under the `MIT` license. You can use whatever code you want,
however you want. Although you are not obliged, I would appreciate you mention
me in you projects!

If you see any issues with this codebase, you can always open issue, pull request,
or contact me in other way!
