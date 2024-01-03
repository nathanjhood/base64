# Base64

Base64 encode/decode CLI in C++.

```.sh
$ base64 [OPTIONS] [FILE]...
```

- [Usage](https://github.com/nathanjhood/base64/tree/main#usage)
- [Examples](https://github.com/nathanjhood/base64/tree/main#examples)
- [About](https://github.com/nathanjhood/base64/tree/main#about)
- [Build from source](https://github.com/nathanjhood/base64/tree/main#build-from-source)
- [Additional support for NodeJs package managers](https://github.com/nathanjhood/base64#additional-support-for-nodejs-package-managers)
- [Coming Soon](https://github.com/nathanjhood/base64/tree/main#coming-soon)
- [Acknowledgments](https://github.com/nathanjhood/base64/tree/main#acknowledgments)

## Usage

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
$./build/bin/base64 tst.txt

Zg==
Zm8=
Zm9v
Zm9vYg==
Zm9vYmE=
Zm9vYmFy
```

For further human readability, we can include the line numbers of the file with the ```-n``` (or ```---show-lines```) flag:

```.sh
$./build/bin/base64 -n tst.txt
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
$./build/bin/base64 -n -E tst.txt
     1  $
     2  Zg==$
     3  Zm8=$
     4  Zm9v$
     5  Zm9vYg==$
     6  Zm9vYmE=$
     7  Zm9vYmFy$
     8  $
```

## Examples

Will parse almost any file type the OS can handle:

```.sh
$ base64 icon__32x32.png


file: icon__32x32.png

iVBORw0=
Gg==
AAAADUlIRFIAAAAgAAAAIAgGAAAAc3p69AAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAFzUkdCAK7OHOkAAAAEZ0FNQQAAsY8L/GEFAAAD3klEQVR4Ae1XS08TURS+M9NSngIhwUB4hWLiookLSQgLYxqkPHZsXPkTXKnRjcGwdaMrEo1BDbpwoZK6QKQJEHFjAk1MA6Qttg3UpLSF0gZKXzN+p6Gm7XQ6fbjTL7k50zn3nvvd87pTxv51cEo...
```

Can be useful for writing contents to new files by streaming:

```.sh
$ base64 icon__32x32.png >> icon__32x32.png.base64.txt
```

Accepts multiple files as arguments in a single command:

```.sh
$ base64 package.json include/base64/base64.h


file: package.json

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


file: include/base64/base64.h

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

## Additional support for NodeJs package managers

With npm:

```.sh
$ npm install && npm run start
```

With yarn:

```.sh
$ yarn && yarn start
```

Currently the NodeJS binary module implements both the ```encode()``` and ````decode()``` functions, which are exported from ```base64.cjs```. Just import/require ```base64``` from this file, and call the functions:

```.js
// index.js

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

Run ```$ node index.js``` to execute the test script:

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

## Coming soon...

<i>PLEASE NOTE: This project should not really be installed system-wide nor placed in your operating system's ```PATH```, due to the naming conflict with the actual system-level base64 implementation.

Due to this, and also some interest in implementing further encode/decode algorithms as well as implementing the entire package as NodeJs binary addons, this project will likely either be renamed, or deprecated in favor of a larger, more realized project.</i>

Currently working on a switch argument for the different modes (encode, decode, possibly a 'diff' mode for testing, debugging, etc). Also adding the standard CLI flags (```--version```, ```--help```, ```--verbose```, etc) but without depending on ```getopt``` or any C library. Furthermore, colorization line numbers and line ending chars is already in the codebase, but will need a bit of system-detection logic to ensure that the end-user's terminal actually [supports colourized output](https://linux.die.net/man/5/terminfo).

My primary interest in this project is to extend functionality to include other algorithms and alphabets, such as Base32, Hex, etc, with a unified interface - or perhaps just a single interface, eventually - and potentially to be used as a Node C++ addon.

## Thanks for reading!

[Nathan J. Hood](https://github.com/nathanjhood)

## Acknowledgements:
- ["The Base16, Base32, and Base64 Data Encodings"](https://datatracker.ietf.org/doc/html/rfc4648); S. Josefsson (Copyright (C) 2006 The Internet Society).

- 'base64.cpp'; The central encode/decode algorithm is a slightly modified implementation taken from René Nyffenegger's 'base64.cpp' (Copyright (C) 2004-2008 René Nyffenegger) from the below discussion:

[https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c](https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c)

[A more recent (version 2) revision of this algorithm is also publically available](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/). My reasons for adapting an earlier version is because I intend to attempt several other encode/decode algorithms using a similar to this implementation, which has slightly less of the functionality specific only to base64 (for example, no base64 URL alphabet) and thus shall be more adaptable into other forms.
