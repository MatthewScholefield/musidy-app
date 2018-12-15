# Musidy

*A song generation tool*

Musidy is a dynamic song generation tool that creates melodies and songs on the fly based on user input.


![Screenshot](https://images2.imgbox.com/74/29/SiylAtYV_o.png)


## Installation

To compile Musidy, you need to install the CMake build system. Once you have this, type the following commands to build the project:

```bash
mkdir build
cd build
cmake ..
make
```

After compilation, you should have an executable which can be run as follows:

```bash
./musidy
```

Usage:

```bash
./musidy --help
Dynamic Music Generation App
Usage: ./build/musidy [OPTIONS] soundfont_file

Positionals:
  soundfont_file TEXT REQUIRED
                              Soundfont file (.sf2) to play song with

Options:
  -h,--help                   Print this help message and exit
  -g,--gain FLOAT             Volume gain of instrument (negative or positive decimal)
```
