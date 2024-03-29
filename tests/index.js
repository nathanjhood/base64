const base64 = require("../lib/base64.node");

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
// console.log(base64.decode(""));  // Napi::String doesn't like these, much!
console.log(base64.decode("Zg==")); // Napi::String doesn't like these, also!
console.log(base64.decode("Zm8="));
console.log(base64.decode("Zm9v"));
console.log(base64.decode("Zm9vYg=="));
console.log(base64.decode("Zm9vYmE="));
console.log(base64.decode("Zm9vYmFy"));
// console.log(base64.decode(""));

// encoder mode test
console.log("\nEncoder non-URL alphabet test:\n");
console.log("= %s", base64.encode("=", false));
console.log("/ %s", base64.encode("/", false));
console.log("- %s", base64.encode("-", false));
console.log("_ %s", base64.encode("_", false));

console.log("\nEncoder URL alphabet test:\n");
console.log("= %s", base64.encode("=", true));
console.log("/ %s", base64.encode("/", true));
console.log("- %s", base64.encode("-", true));
console.log("_ %s", base64.encode("_", true));

// decoder mode test
console.log("\nDecoder non-URL alphabet test:\n");
console.log("PQ== %s", base64.decode("PQ==", false));
console.log("Lw== %s", base64.decode("Lw==", false));
console.log("LQ== %s", base64.decode("LQ==", false));
console.log("XyA= %s", base64.decode("XyA=", false));

console.log("\nDecoder URL alphabet test:\n");
console.log("PQ== %s", base64.decode("PQ==", true));
console.log("Lw== %s", base64.decode("Lw==", true));
console.log("LQ== %s", base64.decode("LQ==", true));
console.log("Xw== %s", base64.decode("Xw==", true));

// encode/decode test
console.log("\nStress test: encode/decode\n");
console.log(base64.decode(base64.encode("foobar")));


const fs = require('fs');

// Calling the readFileSync() method
// to read 'input.txt' file
const data = fs.readFileSync('./tst.txt',
    { encoding: 'base64', flag: 'r' });

// Display the file data
console.log(base64.decode(data));

console.log(base64.get_node_version());
console.log(base64.get_napi_version());
