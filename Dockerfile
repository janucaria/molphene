FROM nvidia/opengl:1.0-glvnd-devel-ubuntu18.04

LABEL maintainer="Januar C Andaria <janucaria@gmail.com>"

WORKDIR /tmp

RUN apt-get update \
  && apt-get install -y --no-install-recommends apt-utils dialog 2>&1 \
  && DEBIAN_FRONTEND=noninteractive \
  apt-get install -y --no-install-recommends \
  binutils-dev \
  g++ \
  git \
  gnupg2 \
  libcurl4-openssl-dev \
  libdw-dev \
  libiberty-dev \
  libssl-dev \
  make \
  pkg-config \
  python3 \
  python3-distutils \
  software-properties-common \
  wget \
  xauth \
  xorg-dev \
  zlib1g-dev \
  #
  && wget -O- https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
  && add-apt-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main" \
  && apt-get update \
  && apt-get install -y --no-install-recommends \
  clang-10 \
  clang-10-doc \
  clang-format-10 \
  clang-tidy-10 \
  clang-tools-10 \
  clangd-10 \
  libc++-10-dev \
  libc++abi-10-dev \
  libclang-10-dev \
  libclang-common-10-dev \
  libclang1-10 \
  libfuzzer-10-dev \
  libllvm-10-ocaml-dev \
  libllvm9 \
  libomp-10-dev \
  lld-10 \
  lldb-10 \
  llvm-10 \
  llvm-10-dev \
  llvm-10-doc \
  llvm-10-examples \
  llvm-10-runtime \
  #
  apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 60C317803A41BA51845E371A1E9377A2BA9EF27F \
  && add-apt-repository "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu bionic main" \
  && apt-get update \
  && apt-get install -y g++-9 \
  #
  && true

RUN git clone -b v3.17.2 https://github.com/Kitware/CMake.git \
  && cd CMake \
  && ./bootstrap \
  && make -j$(nproc) \
  && make install \
  && cd .. \
  && rm -rf CMake

RUN git clone -b boost-1.73.0 --recursive https://github.com/boostorg/boost.git \
  && cd boost \
  && ./bootstrap.sh --without-libraries=python \
  && ./b2 variant=release install \
  && cd .. \
  && rm -rf boost

RUN git clone -b 3.0.1 https://github.com/microsoft/GSL.git \
  && cmake -H./GSL -B./build \
  -DBUILD_TESTING=OFF \
  -DCMAKE_BUILD_TYPE=Release \
  -DGSL_CXX_STANDARD=17 \
  -DGSL_TEST=OFF \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build GSL

RUN git clone -b v38 https://github.com/SimonKagstrom/kcov.git \
  && cmake -H./kcov -B./build \
  -DCMAKE_BUILD_TYPE=Release \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build kcov

RUN git clone -b 6.2.1 https://github.com/fmtlib/fmt.git \
  && cmake -H./fmt -B./build \
  -DCMAKE_BUILD_TYPE=Release \
  -DFMT_DOC=OFF \
  -DFMT_INSTALL=ON \
  -DFMT_TEST=OFF \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build fmt

RUN git clone -b v3.7.3 https://github.com/nlohmann/json.git \
  && cmake -H./json -B./build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTING=OFF \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build json

RUN git clone https://github.com/emscripten-core/emsdk.git /opt/emsdk \
  && cd /opt/emsdk \
  && git pull \
  && ./emsdk install \
  -j$(nproc) \
  --build=Release \
  1.39.3 \
  && ./emsdk activate --build=Release 1.39.3 \
  && echo "source $(pwd)/emsdk_env.sh > /dev/null" >> /etc/bash.bashrc

RUN git clone -b 3.3.2 https://github.com/glfw/glfw.git \
  && cmake -H./glfw -B./build \
  -DCMAKE_BUILD_TYPE=Release \
  -DGLFW_BUILD_DOCS=OFF \
  -DGLFW_BUILD_EXAMPLES=OFF \
  -DGLFW_BUILD_TESTS=OFF \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build glfw

RUN git clone -b v0.1.33 https://github.com/Dav1dde/glad.git \
  && cmake -H./glad -B./build \
  -DCMAKE_BUILD_TYPE=Release \
  -DGLAD_INSTALL=ON \
  && cmake --build ./build --config Release --target all -- -j$(nproc) \
  && cmake --build ./build --config Release --target install -- -j$(nproc) \
  && rm -rf build glad

RUN true \
  && update-alternatives --install /usr/bin/python python /usr/bin/python3 30 \
  && update-alternatives --config python \
  #
  update-alternatives \
  --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-9 \
  && update-alternatives --config gcc \
  #
  && update-alternatives \
  --install /usr/bin/llvm-config         llvm-config         /usr/bin/llvm-config-10 100 \
  --slave   /usr/bin/llvm-PerfectShuffle llvm-PerfectShuffle /usr/bin/llvm-PerfectShuffle-10 \
  --slave   /usr/bin/llvm-addr2line      llvm-addr2line      /usr/bin/llvm-addr2line-10 \
  --slave   /usr/bin/llvm-ar             llvm-ar             /usr/bin/llvm-ar-10 \
  --slave   /usr/bin/llvm-as             llvm-as             /usr/bin/llvm-as-10 \
  --slave   /usr/bin/llvm-bcanalyzer     llvm-bcanalyzer     /usr/bin/llvm-bcanalyzer-10 \
  --slave   /usr/bin/llvm-c-test         llvm-c-test         /usr/bin/llvm-c-test-10 \
  --slave   /usr/bin/llvm-cat            llvm-cat            /usr/bin/llvm-cat-10 \
  --slave   /usr/bin/llvm-cfi-verify     llvm-cfi-verify     /usr/bin/llvm-cfi-verify-10 \
  --slave   /usr/bin/llvm-cov            llvm-cov            /usr/bin/llvm-cov-10 \
  --slave   /usr/bin/llvm-cvtres         llvm-cvtres         /usr/bin/llvm-cvtres-10 \
  --slave   /usr/bin/llvm-cxxdump        llvm-cxxdump        /usr/bin/llvm-cxxdump-10 \
  --slave   /usr/bin/llvm-cxxfilt        llvm-cxxfilt        /usr/bin/llvm-cxxfilt-10 \
  --slave   /usr/bin/llvm-diff           llvm-diff           /usr/bin/llvm-diff-10 \
  --slave   /usr/bin/llvm-dis            llvm-dis            /usr/bin/llvm-dis-10 \
  --slave   /usr/bin/llvm-dlltool        llvm-dlltool        /usr/bin/llvm-dlltool-10 \
  --slave   /usr/bin/llvm-dwarfdump      llvm-dwarfdump      /usr/bin/llvm-dwarfdump-10 \
  --slave   /usr/bin/llvm-dwp            llvm-dwp            /usr/bin/llvm-dwp-10 \
  --slave   /usr/bin/llvm-elfabi         llvm-elfabi         /usr/bin/llvm-elfabi-10 \
  --slave   /usr/bin/llvm-exegesis       llvm-exegesis       /usr/bin/llvm-exegesis-10 \
  --slave   /usr/bin/llvm-extract        llvm-extract        /usr/bin/llvm-extract-10 \
  --slave   /usr/bin/llvm-jitlink        llvm-jitlink        /usr/bin/llvm-jitlink-10 \
  --slave   /usr/bin/llvm-lib            llvm-lib            /usr/bin/llvm-lib-10 \
  --slave   /usr/bin/llvm-link           llvm-link           /usr/bin/llvm-link-10 \
  --slave   /usr/bin/llvm-lipo           llvm-lipo           /usr/bin/llvm-lipo-10 \
  --slave   /usr/bin/llvm-lto            llvm-lto            /usr/bin/llvm-lto-10 \
  --slave   /usr/bin/llvm-lto2           llvm-lto2           /usr/bin/llvm-lto2-10 \
  --slave   /usr/bin/llvm-mc             llvm-mc             /usr/bin/llvm-mc-10 \
  --slave   /usr/bin/llvm-mca            llvm-mca            /usr/bin/llvm-mca-10 \
  --slave   /usr/bin/llvm-modextract     llvm-modextract     /usr/bin/llvm-modextract-10 \
  --slave   /usr/bin/llvm-mt             llvm-mt             /usr/bin/llvm-mt-10 \
  --slave   /usr/bin/llvm-nm             llvm-nm             /usr/bin/llvm-nm-10 \
  --slave   /usr/bin/llvm-objcopy        llvm-objcopy        /usr/bin/llvm-objcopy-10 \
  --slave   /usr/bin/llvm-objdump        llvm-objdump        /usr/bin/llvm-objdump-10 \
  --slave   /usr/bin/llvm-opt-report     llvm-opt-report     /usr/bin/llvm-opt-report-10 \
  --slave   /usr/bin/llvm-pdbutil        llvm-pdbutil        /usr/bin/llvm-pdbutil-10 \
  --slave   /usr/bin/llvm-profdata       llvm-profdata       /usr/bin/llvm-profdata-10 \
  --slave   /usr/bin/llvm-ranlib         llvm-ranlib         /usr/bin/llvm-ranlib-10 \
  --slave   /usr/bin/llvm-rc             llvm-rc             /usr/bin/llvm-rc-10 \
  --slave   /usr/bin/llvm-readelf        llvm-readelf        /usr/bin/llvm-readelf-10 \
  --slave   /usr/bin/llvm-readobj        llvm-readobj        /usr/bin/llvm-readobj-10 \
  --slave   /usr/bin/llvm-rtdyld         llvm-rtdyld         /usr/bin/llvm-rtdyld-10 \
  --slave   /usr/bin/llvm-size           llvm-size           /usr/bin/llvm-size-10 \
  --slave   /usr/bin/llvm-split          llvm-split          /usr/bin/llvm-split-10 \
  --slave   /usr/bin/llvm-stress         llvm-stress         /usr/bin/llvm-stress-10 \
  --slave   /usr/bin/llvm-strip          llvm-strip          /usr/bin/llvm-strip-10 \
  --slave   /usr/bin/llvm-symbolizer     llvm-symbolizer     /usr/bin/llvm-symbolizer-10 \
  --slave   /usr/bin/llvm-tblgen         llvm-tblgen         /usr/bin/llvm-tblgen-10 \
  --slave   /usr/bin/llvm-undname        llvm-undname        /usr/bin/llvm-undname-10 \
  && update-alternatives --config llvm-config \
  && update-alternatives \
  --install /usr/bin/clang                    clang                    /usr/bin/clang-10 100 \
  --slave   /usr/bin/asan_symbolize           asan_symbolize           /usr/bin/asan_symbolize-10 \
  --slave   /usr/bin/c-index-test             c-index-test             /usr/bin/c-index-test-10 \
  --slave   /usr/bin/clang-apply-replacements clang-apply-replacements /usr/bin/clang-apply-replacements-10 \
  --slave   /usr/bin/clang-change-namespace   clang-change-namespace   /usr/bin/clang-change-namespace-10 \
  --slave   /usr/bin/clang-check              clang-check              /usr/bin/clang-check-10 \
  --slave   /usr/bin/clang-cl                 clang-cl                 /usr/bin/clang-cl-10 \
  --slave   /usr/bin/clang-cpp                clang-cpp                /usr/bin/clang-cpp-10 \
  --slave   /usr/bin/clang-doc                clang-doc                /usr/bin/clang-doc-10 \
  --slave   /usr/bin/clang-extdef-mapping     clang-extdef-mapping     /usr/bin/clang-extdef-mapping-10 \
  --slave   /usr/bin/clang-format             clang-format             /usr/bin/clang-format-10 \
  --slave   /usr/bin/clang-format-diff        clang-format-diff        /usr/bin/clang-format-diff-10 \
  --slave   /usr/bin/clang-import-test        clang-import-test        /usr/bin/clang-import-test-10 \
  --slave   /usr/bin/clang-include-fixer      clang-include-fixer      /usr/bin/clang-include-fixer-10 \
  --slave   /usr/bin/clang-offload-bundler    clang-offload-bundler    /usr/bin/clang-offload-bundler-10 \
  --slave   /usr/bin/clang-query              clang-query              /usr/bin/clang-query-10 \
  --slave   /usr/bin/clang-refactor           clang-refactor           /usr/bin/clang-refactor-10 \
  --slave   /usr/bin/clang-rename             clang-rename             /usr/bin/clang-rename-10 \
  --slave   /usr/bin/clang-reorder-fields     clang-reorder-fields     /usr/bin/clang-reorder-fields-10 \
  --slave   /usr/bin/clang-scan-deps          clang-scan-deps          /usr/bin/clang-scan-deps-10 \
  --slave   /usr/bin/clang-tidy               clang-tidy               /usr/bin/clang-tidy-10 \
  --slave   /usr/bin/clang++                  clang++                  /usr/bin/clang++-10  \
  --slave   /usr/bin/clangd                   clangd                   /usr/bin/clangd-10 \
  --slave   /usr/bin/lld                      lld                      /usr/bin/lld-10 \
  --slave   /usr/bin/lld-link                 lldb-link                /usr/bin/lld-link-10 \
  --slave   /usr/bin/lldb                     lldb                     /usr/bin/lldb-10 \
  --slave   /usr/bin/lldb-argdumper           lldb-argdumper           /usr/bin/lldb-argdumper-10 \
  --slave   /usr/bin/lldb-instr               lldb-instr               /usr/bin/lldb-instr-10 \
  --slave   /usr/bin/lldb-server              lldb-server              /usr/bin/lldb-server-10 \
  --slave   /usr/bin/lldb-vscode              lldb-vscode              /usr/bin/lldb-vscode-10 \
  && update-alternatives --config clang \
  #
  && true

WORKDIR /app
