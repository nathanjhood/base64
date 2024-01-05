# Base64

Base64 encode/decode CLI in C++.

```.sh
$ base64 [OPTIONS] [FILE]...
```

Base64 encode/decode functions in NodeJs.

```.js
import base64 from './base64.cjs'

console.log(base64.encode("foobar"));
```

- [Usage](https://github.com/nathanjhood/base64/tree/main#usage)
  - [Command Line Interface](https://github.com/nathanjhood/base64/tree/main#command_line_interface)
  - [NodeJs Interface](https://github.com/nathanjhood/base64/tree/main#nodejs_interface)
- [Goals](https://github.com/nathanjhood/base64/tree/main#goals)
- [Examples](https://github.com/nathanjhood/base64/tree/main#examples)
- [About](https://github.com/nathanjhood/base64/tree/main#about)
- [Build from source](https://github.com/nathanjhood/base64/tree/main#build-from-source)
- [Additional support for NodeJs package managers](https://github.com/nathanjhood/base64#additional-support-for-nodejs-package-managers)
- [Hacking](https://github.com/nathanjhood/base64/tree/main#hacking)
- [Coming Soon](https://github.com/nathanjhood/base64/tree/main#coming-soon)
- [Acknowledgments](https://github.com/nathanjhood/base64/tree/main#acknowledgments)

## Usage

### Command Line Interface

*PLEASE NOTE: The following steps assume that you have [built the executable from the source code](https://github.com/nathanjhood/base64/tree/main#build-from-source) and it is located ```\<project folder\>/build/bin/base64```as per the provided build-script.*

Let's say we have a file on disk that we want to encode to base 64...

```.sh
# tst.txt

f
fo
foo
foob
fooba
foobar

```

We can simply pass the file's location as an argument to base64 to get a readout:

```.sh
$ ./build/bin/base64 tst.txt

Zg==
Zm8=
Zm9v
Zm9vYg==
Zm9vYmE=
Zm9vYmFy
```

For further human readability, we can include the line numbers of the file with the ```-n``` (or ```---show-lines```) flag:

```.sh
$ ./build/bin/base64 -n tst.txt
     1
     2  Zg==
     3  Zm8=
     4  Zm9v
     5  Zm9vYg==
     6  Zm9vYmE=
     7  Zm9vYmFy
     8
```

As a result of this flag, we can clearly see that there are two empty lines in the file (lines 1 and 8).

In the case of more complex input/output files, it can also be helpful to report the line endings as ```$```. To do this, include the ```-E``` (or ```--show-ends```) flag:

```.sh
$ ./build/bin/base64 -n -E tst.txt
     1  $
     2  Zg==$
     3  Zm8=$
     4  Zm9v$
     5  Zm9vYg==$
     6  Zm9vYmE=$
     7  Zm9vYmFy$
     8  $
```

You can write the output to a file on disk with the streaming operator (place ```>> name.ext``` after the command):

```.sh
$ ./build/bin/base64 tst.txt >> foo.txt
```

To decode the data back again, just add the ```--decode``` flag:

```.sh
$ ./build/bin/base64 --decode --show-lines --show-ends foo.txt
     1  $
     2  f$
     3  fo$
     4  foo$
     5  foob$
     6  fooba$
     7  foobar$
     8  $
```

To go full circle, just ```--decode``` back to a new file:

```.sh
$ ./build/bin/base64 --decode foo.txt >> bar.txt
```

You can also pass the ```--encode``` flag when you want to be specific:

```.sh
$ ./build/bin/base64 --encode --show-lines bar.txt
     1
     2  Zg==
     3  Zm8=
     4  Zm9v
     5  Zm9vYg==
     6  Zm9vYmE=
     7  Zm9vYmFy
```

*PLEASE NOTE: only one mode - encode or decode - can be specified per run, and if neither flag is passed, then the encode function will be selected by default.*

### NodeJs Interface

*PLEASE NOTE: The following assumes that you have both a C++ compiler toolchain, and CMake, installed on your system. These commands will build the binary from the source code, which means the system requirements are the same as when [building from source](https://github.com/nathanjhood/base64/tree/main#build-from-source).*

Build and run with npm:

```.sh
$ npm install && npm run start
```

Or, build and run with yarn:

```.sh
$ yarn && yarn start
```

The above commands will build the NodeJs module from source, then execute the contents of ```index.js``` which serves as a demonstration.

Currently the NodeJS binary module implements both the ```encode()``` and ```decode()``` functions, which are exported from ```base64.cjs```. <b>Since the file input parsing is currently a part of the CLI implementation, the NodeJS module parses input strings, not files</b>. Just import/require ```base64``` from this file, and call the functions:

```.js
// index.js

import base64 from './base64.cjs'
...

console.log(base64.encode(""));
console.log(base64.encode("f"));
console.log(base64.encode("fo"));
console.log(base64.encode("foo"));
console.log(base64.encode("foob"));
console.log(base64.encode("fooba"));
console.log(base64.encode("foobar"));
console.log(base64.encode(""));

...
```

Run ```node ./index.js``` to execute the test script:

```
...

Zg==
Zm8=
Zm9v
Zm9vYg==
Zm9vYmE=
Zm9vYmFy

...
```

*PLEASE NOTE: the 'url' version of the base64 alphabet is much more well-suited for usage in tasks where javascript is often deployed.*

Both functions also have an additional second parameter, 'urlMode' , which accepts a boolean value. Setting this parameter to 'true' will switch to the base64 alphabet; this alphabet supports URL-like strings:

```.sh
// encoder mode test - using non-url alphabet
console.log(base64.encode("=", false));
console.log(base64.encode("/", false));
console.log(base64.encode("-", false));
console.log(base64.encode("_ ", false));

// encoder mode test - using url alphabet
console.log(base64.encode("=", true));
console.log(base64.encode("/", true));
console.log(base64.encode("-", true));
console.log(base64.encode("_", true));
```

You can also access the built CLI executable (and all of it's options) directly from the npm script:

```.sh
$ npm run base64 --encode --show-lines tst.txt

// or...

$ yarn base64 --encode --show-lines tst.txt
```

## Goals

My primary interest in this project is to extend functionality to include other algorithms and alphabets, such as Base32, Hex, etc, with a unified interface - or perhaps just a single interface, eventually - and implement a variety of hand-rolled alphabets as a Node C++ addon, beyond the standard ```atob()```.

This project will serve as a workbench for certain aspects of the intended final application, mostly focusing on the underlying algorithm, as well as interfacing with it from other code - the provided CLI being one example of a possible consumer runtime, and NodeJs being another.

## Examples

Will parse almost any file type the OS can handle:

```.sh
$ ./build/bin/base64 icon__32x32.png

iVBORw0=
Gg==
AAAADUlIRFIAAAAgAAAAIAgGAAAAc3p69AAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAFzUkdCAK7OHOkAAAAEZ0FNQQAAsY8L/GEFAAAD3klEQVR4Ae1XS08TURS+M9NSngIhwUB4hWLiookLSQgLYxqkPHZsXPkTXKnRjcGwdaMrEo1BDbpwoZK6QKQJEHFjAk1MA6Qttg3UpLSF0gZKXzN+p6Gm7XQ6fbjTL7k50zn3nvvd87pTxv51cEo...
```

Can be useful for writing contents to new files by streaming:

```.sh
$ ./build/bin/base64 icon__32x32.png >> icon__32x32.png.base64.txt
```

Accepts multiple files as arguments in a single command:

```.sh
$ ./build/bin/base64 package.json include/base64/base64.h


# file: package.json

ew==
ICAibmFtZSI6ICJiYXNlNjQiLA==
ICAidmVyc2lvbiI6ICIwLjAuMCIs
ICAibWFpbiI6ICJpbmRleC5qcyIs
ICAiYXV0aG9yIjogIlN0b25leURTUCA8bmF0aGFuamhvb2RAZ29vZ2xlbWFpbC5jb20+Iiw=
ICAibGljZW5zZSI6ICJNSVQiLA==
ICAic2NyaXB0cyI6IHs=
ICAgICJwb3N0aW5zdGFsbCI6ICJjbWFrZS1qcyBjb21waWxlIiw=
ICAgICJjb25maWd1cmUiOiAiY21ha2UtanMgY29uZmlndXJlIiw=
ICAgICJyZWNvbmZpZ3VyZSI6ICJjbWFrZS1qcyByZWNvbmZpZ3VyZSIs
ICAgICJidWlsZCI6ICJjbWFrZS1qcyBidWlsZCIs
ICAgICJyZWJ1aWxkIjogImNtYWtlLWpzIHJlYnVpbGQiLA==
ICAgICJjbGVhbiI6ICJjbWFrZS1qcyBjbGVhbiIs
ICAgICJ3aXBlIjogImNtYWtlLWpzIGNsZWFuICYmIHJtIC1ydmYgLi9ub2RlX21vZHVsZXMiLA==
ICAgICJzdGFydCI6ICIuL2J1aWxkL2Jpbi9iYXNlNjQgZmF2aWNvbi5pY28gaWNvbl9fMzJ4MzIucG5nIg==
ICB9LA==
ICAiZGVwZW5kZW5jaWVzIjogew==
ICAgICJjbWFrZS1qcyI6ICJeNy4yLjEi
ICB9
fQ==


# file: include/base64/base64.h

Lyoq
ICogQGZpbGUgYmFzZTY0Lmg=
ICogQGF1dGhvciBSZW7DqSBOeWZmZW5lZ2dlciAocmVuZS5ueWZmZW5lZ2dlckBhZHAtZ21iaC5jaCk=
ICogQGJyaWVm
ICogQHZlcnNpb24gMC4x
ICogQGRhdGUgMjAyMy0xMi0yOQ==
ICo...
```

Use the output data directly in various software design tasks:

```.sh
# styles.css
html {
    background-image: url("data:image/png;base64,ICogQGF1dGhvciBSZW7DqSBOeWZmZW5lZ....");
}
```

```.sh
# index.html
<head>
    <link rel="favicon" type="image/x-icon" href="Content-Type: image/x-icon;ICogQGF1dGhvciBSZW7DqSBOeWZmZW5lZ....">
</head>
```

## About

The encoding process represents 24-bit groups of input bits as output
strings of 4 encoded characters.  Proceeding from left to right, a
24-bit input group is formed by concatenating 3 8-bit input groups.
These 24 bits are then treated as 4 concatenated 6-bit groups, each
of which is translated into a single character in the base 64
alphabet.

```
  <===========>                                   1st character
                  <===========>                   2nd character
                                  <===========>   3rd character
+---------------+---------------+---------------+
| <     1     > | <     2     > | <     3     > | 3 groups (8 bit)
+---------------+---------------+---------------+
|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0| Stream (24 bits)
+-----------+---+-------+-------+---+-----------+
|<    1    >|<    2    >|<    3    >|<    4    >| 4 groups (6 bit)
+-----------+-----------+-----------+-----------+
|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0| Index  (24 bits)

                                     <=========>  4th character
                         <=========>              3rd character
             <=========>                          2nd character
 <=========>                                      1st character
```

Each 6-bit group is used as an index into an array of 64 printable
characters.  The character referenced by the index is placed in the
output string.

A 65-character subset of US-ASCII is used, enabling 6 bits to be
represented per printable character.  (The extra 65th character, "=",
is used to signify a special processing function.)

Each 6-bit group is used as an index into an array of 64 printable
characters.  The character referenced by the index is placed in the
output string.

```
                  The Base 64 Alphabet

  Value Encoding  Value Encoding  Value Encoding  Value Encoding
       0 A           17 R            34 i            51 z
       1 B           18 S            35 j            52 0
       2 C           19 T            36 k            53 1
       3 D           20 U            37 l            54 2
       4 E           21 V            38 m            55 3
       5 F           22 W            39 n            56 4
       6 G           23 X            40 o            57 5
       7 H           24 Y            41 p            58 6
       8 I           25 Z            42 q            59 7
       9 J           26 a            43 r            60 8
      10 K           27 b            44 s            61 9
      11 L           28 c            45 t            62 +
      12 M           29 d            46 u            63 /
      13 N           30 e            47 v
      14 O           31 f            48 w         (pad) =
      15 P           32 g            49 x
      16 Q           33 h            50 y
```

```.txt

BASE64 ENCODE:

  <===========>                                   1st character
                  <===========>                   2nd character
                                  <===========>   3rd character
+---------------+---------------+---------------+
| <     1     > | <     2     > | <     3     > | 3 groups (8 bit)
+---------------+---------------+---------------+
|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0| Stream (24 bits)
+-----------+---+-------+-------+---+-----------+
|<    1    >|<    2    >|<    3    >|<    4    >| 4 groups (6 bit)
+-----------+-----------+-----------+-----------+
|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0| Index (24 bits)

                                     <=========>  4th character
                         <=========>              3rd character
             <=========>                          2nd character
 <=========>                                      1st character


BASE64 DECODE:

 <=========>                                      1st character
             <=========>                          2nd character
                         <=========>              3rd character
                                     <=========>  4th character
+-----------+-----------+-----------+-----------+
|<    1    >|<    2    >|<    3    >|<    4    >| 4 groups (6 bit)
+-----------+-----------+-----------+-----------+
|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0| Index (24 bits)
+-----------+---+-------+-------+---+-----------+
| <     1     > | <     2     > | <     3     > | 3 groups (8 bit)
+---------------+---------------+---------------+
|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0| Stream (24 bits)

                                  <===========>   3rd character
                  <===========>                   2nd character
  <===========>                                   1st character

```

## Build from source

Requirements:
- C++ compiler (GNU, MSVC...)
- CMake
- Ninja (optional/recommended)

Check out out the project:

```.sh
$ git clone https://github.com/nathanjhood/base64.git
$ cd base64
```

Configure the library and executable with CMake:

```.sh
$ cmake -S . -B ./build
```
*NOTE: The '-S .' arg tells CMake to start from the current directory. The -B arg tells CMake to place it's output in the 'build' directory (which you can of course change if you wish).*

Build it (replace with ```make``` or whichever generator you prefer):
```
$ ninja ./build
```

Try running the built executable:

```.sh
$ ./build/bin/base64 icon__32x32.png

# output should appear...
...
```

<s>Optionally, try running the tests *(coming soon)*:

```.sh
$ cmake --test build
```
Install base64 *(coming soon)*:
```.sh
$ cmake --install build
```
</s>

## Hacking

### Trying to build the NodeJs addon manually?

When building this project from the npm/yarn command, the package 'cmake-js' is invoked, which reads from the same build script (```CMakeLists.txt```) as the CMake CLI does. However, cmake-js also passes an argument equivalent to ```-DCMAKE_CXX_FLAGS:STRING=-DBUILDING_NODE_EXTENSION```, which is used in the build script to detect that we are also building the node addon part of the script. You may also pass the above arg manually when building with CMake directly on the command line, as long as you have already done ```npm install```or ```yarn``` to acquire these headers; they should be found in the usual ```node_modules``` folder at the project root. Note that the entire 'addon.cpp' is guarded by requiring ```napi.h``` to be found and ```BUILDING_NODE_EXTENSION``` to be defined. See the next section if you can't find ```napi.h```.

### "Where is 'napi.h'?"

When building the NodeJS addon, your IDE might not find the ```<napi.h>``` file, even when building successfully. The file(s) you need should be in the ```node_modules``` directory, under ```node-api-headers/include``` (C headers for NodeJs) and ```node-addon-api``` (C++ headers which wrap the C headers)\*. The build script(s) will pick them up automatically, but your IDE might not. You just need to add these two directories appropriately to your IDE's intellisense engine path.

VSCode with C++ extension example:

```.json
// .vscode/c_cpp_properties.json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "node_modules/node-addon-api",
        "node_modules/node-api-headers/include"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/g++",
      "cStandard": "c17",
      "cppStandard": "c++14",
      "intelliSenseMode": "linux-gcc-x64",
      "configurationProvider": "ms-vscode.cmake-tools"
    }
  ],
  "version": 4
}

```

\*Important distinction: ```<napi.h>``` is the C++ addon header, and is ABI-stable.

### Node versions, nvm, and ABI stability

If you are using nvm (node version manager), or have different Node installations on your system, NodeJs addons written using the NodeJS C headers will complain that the NodeJS version used during build is different to the one attempting to run the built module. The C++ addon header provides an ABI stability promise, which circumvents this issue.

When choosing to build an addon using the NodeJS C headers directly, you must build against the same NodeJS version that you intend to run on.

The above is the primary reason why I have adapted a C++ base64 implementation, instead of a more common C implementation (such as GNU); you should not experience any issues with differing NodeJs versions and nvm when building this project, thanks to the NodeJs C++ addon's ABI stability.

## Coming soon...

Currently working on adding the standard CLI flags (```--version```, ```--help```, ```--verbose```, etc) but without depending on ```getopt``` or any C library. Also enhancing the CLI switch argument for the different modes (encode, decode, possibly a 'diff' mode for testing, debugging, etc). Furthermore, colorization line numbers and line ending chars is already in the codebase, but will need a bit of system-detection logic to ensure that the end-user's terminal actually [supports colourized output](https://linux.die.net/man/5/terminfo). Finally, the CLI should also accept strings passed in as arguments, in place of any input file, if a certain flag is used.

The CLI compiles into a shared library that the executable links with; this should probably be amended such that the CLI only gets baked into the executable and is not compiled into a seperate library, because the CLI is really part of the executable, *not* part of the base64 implementation, and is not really intended to be shared with other code.

Windows support depends on defining a 'wmain()' entry in place of the usual 'main()', and parsing support for ```w_char``` type. Flags are sometimes prepended with a ```/``` instead of a ```-``` - depending on how much Windows integration is required. Many command line executables running on Windows terminals do accept the usual UNIX-style argument syntax, these days.

<i>PLEASE NOTE: This project should not really be installed system-wide nor placed in your operating system's ```PATH```, due to the naming conflict with the actual system-level base64 implementation.

Due to this, and also some interest in implementing further encode/decode algorithms as well as implementing the entire package as NodeJs binary addons, this project will likely either be renamed, or deprecated in favor of a larger, more realized project.</i>

## Thanks for reading!

[Nathan J. Hood](https://github.com/nathanjhood)

## Acknowledgements:

- ["The Base16, Base32, and Base64 Data Encodings"](https://datatracker.ietf.org/doc/html/rfc4648); S. Josefsson (Copyright (C) 2006 The Internet Society).

- 'base64.cpp'; The central encode/decode algorithm is a slightly modified implementation taken from René Nyffenegger's 'base64.cpp' (Copyright (C) 2004-2008 René Nyffenegger) from the below discussion:

- [https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c](https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c)

- [A more recent (version 2) revision of this algorithm is also publically available](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/). My reasons for adapting an earlier version is because I intend to attempt several other encode/decode algorithms using a similar approach to this implementation, which has slightly less of the functionality tailored specifically for base64, and thus shall be more adaptable into other forms.
