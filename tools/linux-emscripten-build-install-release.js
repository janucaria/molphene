const path = require('path');
const { spawn } = require('child_process');

const options = {
  cwd: path.dirname(__dirname)
};

{
  let cmdCmakeBuild = spawn("cmake", [
    "--build", "./build/Release",
    "--config", "Release",
    "--target", "molphene-web",
    "--",
    "-j2"
  ], Object.assign({
    env: Object.assign({
      LLVM: "/opt/emsdk/upstream/bin"
    }, process.env)
  }, options));
  
  cmdCmakeBuild.stdout.on('data', data => process.stdout.write(data));
  cmdCmakeBuild.stderr.on('data', data => process.stderr.write(data));
  cmdCmakeBuild.on('close', code => console.log(`Build exited with code ${code}`));
}

{
  let cmdCmakeInstall = spawn("cmake", [
    "--build", "./build/Release",
    "--config", "Release",
    "--target", "install",
    "--",
    "-j2"
  ], Object.assign({
    env: Object.assign({
      LLVM: "/opt/emsdk/upstream/bin"
    }, process.env)
  }, options));
  
  cmdCmakeInstall.stdout.on('data', data => process.stdout.write(data));
  cmdCmakeInstall.stderr.on('data', data => process.stderr.write(data));
  cmdCmakeInstall.on('close', code => console.log(`Build exited with code ${code}`));
}