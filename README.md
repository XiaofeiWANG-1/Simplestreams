# Ubuntu Image Tool

A simple command-line utility to interact with [Ubuntu Simplestreams](https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json) metadata and query supported Ubuntu cloud images for the `amd64` architecture.

This tool extracts:
- All supported Ubuntu releases
- Current LTS release
- SHA256 hash for `disk1.img` of a given release


# Requirements

- C++17
- CMake ≥ 3.14
- `libcurl`
- [`nlohmann_json`](https://github.com/nlohmann/json)

# Install dependencies (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libcurl4-openssl-dev nlohmann-json3-dev cmake g++
```

# Build on ubuntu
```bash
git clone https://github.com/XiaofeiWANG-1/Simplestreams.git
cd Simplestreams
mkdir build && cd build
cmake ..
make
```

# Usage

./ubuntu_tool [OPTIONS]

./ubuntu_tool --list
./ubuntu_tool --lts
./ubuntu_tool --sha256 jammy

## No test on windows, and mac systems.



