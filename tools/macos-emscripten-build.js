const path = require('path');
const { spawn } = require('child_process');

const options = {
  cwd: path.dirname(__dirname)
};

let cmdCmakeBuild = spawn("cmake", [
  "--build", "./build",
  "--config", "Debug",
  "--target", "all",
  "--",
  "-j2"
], Object.assign({
  env: Object.assign({
    LLVM: "/usr/local/opt/emscripten/libexec/llvm/bin"
  }, process.env)
}, options));

cmdCmakeBuild.stdout.on('data', data => process.stdout.write(data));
cmdCmakeBuild.stderr.on('data', data => process.stderr.write(data));
cmdCmakeBuild.on('close', code => console.log(`Build exited with code ${code}`));
