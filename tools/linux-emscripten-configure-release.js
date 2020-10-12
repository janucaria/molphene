const path = require('path');
const { spawn } = require('child_process');

const options = {
  cwd: path.dirname(__dirname)
};

let cmdConfigureCmake = spawn("emcmake", [
  "cmake",
  "-DCMAKE_BUILD_TYPE=Release",
  `-DCMAKE_INSTALL_PREFIX=${path.dirname(__dirname)}/install`,
  "-DCMAKE_FIND_ROOT_PATH=/",
  "-DCMAKE_INCLUDE_PATH=/usr/include;/usr/local/include",
  "-B./build/Release",
  "-H."
], Object.assign({
  env: Object.assign({
  }, process.env)
}, options));

cmdConfigureCmake.stdout.on('data', data => process.stdout.write(data));
cmdConfigureCmake.stderr.on('data', data => process.stderr.write(data));
cmdConfigureCmake.on('close', code => console.log(`Configure exited with code ${code}`));
