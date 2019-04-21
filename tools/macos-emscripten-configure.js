const path = require('path');
const { spawn } = require('child_process');

const options = {
  cwd: path.dirname(__dirname)
};

let cmdConfigureCmake = spawn("cmake", [
  "-DBOOST_ROOT=/usr/local/opt/boost",
  "-DCMAKE_TOOLCHAIN_FILE=/usr/local/opt/emscripten/libexec/cmake/Modules/Platform/Emscripten.cmake",
  "-B./build",
  "-H."
], Object.assign({
  env: Object.assign({
    LLVM: "/usr/local/opt/emscripten/libexec/llvm/bin"
  }, process.env)
}, options));

cmdConfigureCmake.stdout.on('data', data => process.stdout.write(data));
cmdConfigureCmake.stderr.on('data', data => process.stderr.write(data));
cmdConfigureCmake.on('close', code => console.log(`Configure exited with code ${code}`));
