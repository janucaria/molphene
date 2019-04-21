const path = require('path');
const { spawn } = require('child_process');

const options = {
  cwd: path.join(path.dirname(__dirname), "build")
};

function logOutput(data) {
  const dataStr = data.toString();
  console.log(dataStr.substring(0, dataStr.length - 1));
}

let cmdRunTest = spawn("ctest", [
  "-j2",
  "-C", "Debug",
  "-T", "test",
  "--output-on-failure"
], Object.assign({
  env: process.env
}, options));

cmdRunTest.stdout.on('data', logOutput);
cmdRunTest.stderr.on('data', logOutput);
cmdRunTest.on('close', code => {
  console.log(`child process exited with code ${code}`);
});
