# myGrep

A command-line program made to mimic some functionalities of Linux's "grep"-utility. This program was made as a project
for our "Advanced Features of C++" -course

## Table of Contents

* [Getting started](#getting-started)
* [Functionality](#functionality)

## Getting started

<a name="getting-started"></a>

Clone the files from this repo to your machine:

```
$ git clone https://github.com/Tommiri/myGrep.git
```

<br>

Build the executable

```
$ cd myGrep
$ g++ src/main.cpp src/searchFromFile.cpp src/searchFromString.cpp include/searchFromFile.h 
include/searchFromString.h -o myGrep
```

<br>

Run the program from your terminal using this syntax:

```
Usage: ./myGrep [[options] [keyword fileName]]

Available options (access with -o)
l - Print line number
o - Print occurrences
r - Reverse search
i - Ignore case
```

## Functionality

<a name="functionality"></a>

```
$ ./myGrep
```

The most basic functionality of the program:

* Input a string you wish to search from
* Input a string you wish to search for from the first string
* The program will search the first string for the string you wished to search for

<br>

```
$ ./myGrep keyword filename
```

The program will search for the keyword from the given file.

<br>

```
$ ./myGrep options keyword filename
```

The program will search for the keyword from the given file using user-given options. Options are accessed using the '
-o' prefix (e.g. -ol). See above for available options and their functionalities.
