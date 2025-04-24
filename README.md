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


# Build on ubuntu

git clone https://github.com/yourusername/ubuntu-image-tool.git
cd ubuntu-image-tool
mkdir build && cd build
cmake ..
cmake --build .

## No test on windows, and mac systems.


##Usage
./ubuntu_tool [OPTIONS]

./ubuntu_tool --list
./ubuntu_tool --lts
./ubuntu_tool --sha256 jammy


