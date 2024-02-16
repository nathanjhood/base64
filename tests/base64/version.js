function test_version() {

  let status = false;

  try {

    const base64 = require("../../lib/base64.node");

    console.log(`Napi Version: ${base64.version()}`);

    status = true;

  } catch(e) {

    console.log(`${e}`);
  }

  return status;
};

const res_test_version = test_version();

if((!res_test_version))
{
  console.log("'test_version()' failed.");
  return false;
}

console.log("'test_version()' passed.");
return true;
