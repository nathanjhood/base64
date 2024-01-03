#!/usr/bin/env node
import base64 from './base64.cjs'

console.log(base64.hello());
console.log(base64.version());

// test vector
console.log("");
console.log("f");
console.log("fo");
console.log("foo");
console.log("foob");
console.log("fooba");
console.log("foobar");
console.log("");

// encoder test
console.log(base64.encode(""));
console.log(base64.encode("f"));
console.log(base64.encode("fo"));
console.log(base64.encode("foo"));
console.log(base64.encode("foob"));
console.log(base64.encode("fooba"));
console.log(base64.encode("foobar"));
console.log(base64.encode(""));

// decoder test
// console.log(base64.decode(""));
console.log(base64.decode("Zg=="));
console.log(base64.decode("Zm8="));
console.log(base64.decode("Zm9v"));
console.log(base64.decode("Zm9vYg=="));
console.log(base64.decode("Zm9vYmE="));
console.log(base64.decode("Zm9vYmFy"));
// console.log(base64.decode(""));
