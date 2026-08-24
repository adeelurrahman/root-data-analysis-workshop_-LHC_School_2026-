# Installing CERN ROOT

ROOT is available as a precompiled binary and as source code. A matching precompiled binary is normally the quickest route. Build from source when you need a special feature, a nonstandard compiler, or control over build options.

These instructions were checked against the official [ROOT installation page](https://root.cern/install/), [source-build guide](https://root.cern/install/build_from_source/), and [dependency list](https://root.cern/install/dependencies/). Release numbers and platform names change, so check the official download page before copying an archive name.

## Method 1: precompiled binary

### Linux

1. Open the [ROOT installation page](https://root.cern/install/) and choose the newest stable binary matching your Linux distribution, CPU architecture, and compiler runtime.
2. Install the runtime dependencies listed for your distribution. On Ubuntu or another Debian-based system, the common required set is:

   ```bash
   sudo apt update
   sudo apt install binutils cmake dpkg-dev g++ gcc git libssl-dev \
     libx11-dev libxext-dev libxft-dev libxpm-dev python3 \
     libtbb-dev libvdt-dev libgif-dev
   ```

3. Download the selected archive. Replace the placeholder with the exact filename from the download page:

   ```bash
   curl -LO https://root.cern/download/root_v<version>.<platform>.tar.gz
   ```

4. Unpack it in a location you control:

   ```bash
   mkdir -p software/root
   tar -xzf root_v<version>.<platform>.tar.gz -C software/root --strip-components=1
   ```

5. Set up the environment in each new terminal:

   ```bash
   source software/root/bin/thisroot.sh
   ```

6. Confirm that the shell finds the intended installation:

   ```bash
   command -v root
   root-config --version
   root -l -q
   ```

If you add `source /absolute/path/to/software/root/bin/thisroot.sh` to `.bashrc`, do it only once. Mixing setup scripts from several ROOT installations is a common source of Cling and PyROOT failures.

## Method 2: build from source

The commands below create separate source, build, and installation directories. ROOT does not support building directly inside its source tree.

### 1. Install build requirements

For Ubuntu or Debian-based systems:

```bash
sudo apt update
sudo apt install binutils cmake dpkg-dev g++ gcc git libssl-dev \
  libx11-dev libxext-dev libxft-dev libxpm-dev python3 \
  libtbb-dev libvdt-dev libgif-dev
```

ROOT 6.30 and newer requires C++17 support. The official dependency page currently lists GCC 8 or newer and Clang 6 or newer as supported baselines.

### 2. Fetch the stable source

```bash
git clone --branch latest-stable --depth=1 \
  https://github.com/root-project/root.git root_src
```

For a reproducible release build, download a source distribution or check out a release tag instead of following `latest-stable`.

### 3. Configure an out-of-source build

```bash
mkdir root_build root_install
cmake -S root_src -B root_build \
  -DCMAKE_INSTALL_PREFIX="$(pwd)/root_install" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=17
```

Read the CMake summary. A missing optional package may disable a feature. Add `-Dfail-on-missing=ON` when you want configuration to stop instead.

### 4. Compile and install

Choose a sensible parallel-job count for the machine:

```bash
cmake --build root_build --target install --parallel 4
```

A ROOT build is large and can take substantial time and memory. Reduce the parallel count if the machine starts swapping or the compiler is killed.

### 5. Activate and verify

```bash
source root_install/bin/thisroot.sh
command -v root
root-config --version
root -l -q
```

## Optional build choices

Pass additional CMake options during configuration, for example:

```bash
cmake -S root_src -B root_build \
  -DCMAKE_INSTALL_PREFIX="$(pwd)/root_install" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=17 \
  -Dpyroot=ON \
  -Droofit=ON \
  -Dtmva=ON
```
