# Base64

Base64 encode/decode CLI in C++.

- [Usage](/#usage)
- [Examples](/#examples)
- [Build from source](/#build_from_source)
- [Acknowledgments](/#acknowledgments)

## Usage

```.sh
$ base64 [FILE]...
```

## Examples

Will parse almost any file type the OS can handle:

```.sh
$ base64 icon__32x32.png

base64 encode/decode tool


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

base64 encode/decode tool


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

Build the library and executable with CMake:

```.sh
$ cmake -S . -B build
```
*NOTE: The '-S .' arg tells CMake to start from the current directory. The -B arg tells CMake to place it's output in the 'build' directory (which you can of course change if you wish).*

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

## Acknowledgements:

- 'base64.h' and 'base64.cpp' Copyright (C) 2004-2008 René Nyffenegger

[https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c](https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c)
