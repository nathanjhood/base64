#!/usr/bin/env node
import base64 from './base64.cjs'

console.log(base64.hello());
console.log(base64.version());

console.log("\nTest vector:\n");

// test vector
console.log("");
console.log("f");
console.log("fo");
console.log("foo");
console.log("foob");
console.log("fooba");
console.log("foobar");
console.log("");

console.log("\nEncoder test:\n");

// encoder test
console.log(base64.encode(""));
console.log(base64.encode("f"));
console.log(base64.encode("fo"));
console.log(base64.encode("foo"));
console.log(base64.encode("foob"));
console.log(base64.encode("fooba"));
console.log(base64.encode("foobar"));
console.log(base64.encode(""));

console.log("\nDecoder test:\n");

// decoder test
console.log(base64.decode("\n"));
console.log(base64.decode("Zg==\n"));
console.log(base64.decode("Zm8=\n"));
console.log(base64.decode("Zm9v\n"));
console.log(base64.decode("Zm9vYg==\n"));
console.log(base64.decode("Zm9vYmE=\n"));
console.log(base64.decode("Zm9vYmFy\n"));
console.log(base64.decode("\n"));

console.log("\nEncoder URL alphabet test:\n");

// encoder mode test
console.log(base64.encode("=", false));
console.log(base64.encode("/", false));
console.log(base64.encode("-", false));
console.log(base64.encode("_ ", false));

console.log(base64.encode("=", true));
console.log(base64.encode("/", true));
console.log(base64.encode("-", true));
console.log(base64.encode("_", true));
