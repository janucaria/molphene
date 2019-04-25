const path = require('path');
const fs = require('fs');
const { spawnSync } = require('child_process');

async function* getFiles(dir) {
  const subdirs = await fs.promises.readdir(dir, { withFileTypes: true });

  for (const subdir of subdirs) {
    const res = path.resolve(dir, subdir.name);
    if (subdir.isDirectory()) {
      yield* getFiles(res);
    } else if (/\.(hpp|cpp)$/i.test(subdir.name)) {
      yield res;
    }
  }
}

const projectDir = path.dirname(__dirname);
const binsDir = path.resolve(projectDir, "bins");
const libsDir = path.resolve(projectDir, "libs");
const externalDir = path.resolve(projectDir, "third_party");

const options = {
  cwd: projectDir,
  stdio: "inherit"
};

let proccessError = false;
function runCheckFile(file) {
  console.log(`Check ${file}`);

  let cmdClangTidy = spawnSync("/usr/local/opt/llvm/bin/clang-tidy", [
    "-quiet",
    file,
    "--",

    "-DGL_SILENCE_DEPRECATION",

    "-I" + path.resolve(libsDir, "molecule", "src"),
    "-I" + path.resolve(libsDir, "gfxm", "src"),
    "-I" + path.resolve(libsDir, "core", "src"),
    "-I" + path.resolve(libsDir, "io", "src"),
    "-I" + path.resolve(binsDir, "app", "src"),
    "-I" + path.resolve(externalDir, "Gm3d", "src"),
    "-I" + path.resolve(externalDir, "json", "single_include"),
    "-isystem", path.resolve(externalDir, "GSL"),
    "-isystem", path.resolve(externalDir, "GSL", "include"),
    "-isystem", "/usr/local/opt/boost/include",
    "-isystem", "/usr/local/opt/glfw/include",
    "-isysroot", "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk",

    "-Wall",
    "-Wpedantic",
    "-pedantic-errors",
    "-fno-rtti",
    "-std=gnu++1z",
  ], Object.assign({
    env: Object.assign({
    }, process.env)
  }, options));

  if (cmdClangTidy.stdout) {
    process.stdout.write(cmdClangTidy.stdout);
  }
  if (cmdClangTidy.stderr) {
    process.stderr.write(cmdClangTidy.stderr);
  }

  console.log(`Proccess exited with code ${cmdClangTidy.status}`);

  proccessError = proccessError || cmdClangTidy.status;
}

async function runCheck(dir) {
  for await (const file of getFiles(dir)) {
    runCheckFile(file);
  }
}

let checkLibs = runCheck(libsDir);
let checkApps = runCheck(path.resolve(binsDir, "app"));
let checkGlfw = runCheck(path.resolve(binsDir, "glfw"));

Promise.all([checkLibs, checkApps, checkGlfw]).then(values => {
  process.exit(proccessError);
});
