# Machina

A Linux desktop application that displays system information - CPU usage, memory
usage, running processes and OS details. Self contained with immediate-mode UI.

> **Note:** This is an **educational project**, written while learning about
> Linux interfaces (mainly `/proc` and the various system APIs behind it).
> It is not intended as a production-grade system monitor, but if you find it
> useful you are welcome to use it.

## Download

Precompiled, statically linked binaries are available on the
[Releases](../../releases) page. Each release provides:

- `machina-<version>-linux-x86_64.tar.gz` — the application binary
- `machina-<version>-linux-x86_64.tar.gz.sha256` — SHA-256 checksum

Download the archive, verify the checksum (optional) and run it:

```bash
sha256sum -c machina-*-linux-x86_64.tar.gz.sha256
tar -xzf machina-*-linux-x86_64.tar.gz
./machina
```

No installation is required. The binary targets `x86_64` Linux and supports
both X11 and Wayland.

## Build dependencies

A C++23 compiler (GCC 11+ or Clang 14+) and CMake 3.16+ are required.

[ImGui](https://github.com/ocornut/imgui) and
[GLFW](https://github.com/glfw/glfw) are vendored as git submodules and built
from source, so they are not listed below.

### Ubuntu

```bash
sudo apt-get install -y \
  build-essential \
  cmake \
  pkg-config \
  libgl1-mesa-dev \
  libx11-dev \
  libxcursor-dev \
  libxrandr-dev \
  libxi-dev \
  libxinerama-dev \
  libwayland-dev \
  libwayland-bin \
  wayland-protocols \
  libxkbcommon-dev \
  libfontconfig1-dev
```

- `build-essential` — GCC, make and friends
- `libwayland-bin` — provides the `wayland-scanner` tool (not in `libwayland-dev`)

### Fedora

```bash
sudo dnf install -y \
  gcc-c++ \
  make \
  cmake \
  pkgconf-pkg-config \
  mesa-libGL-devel \
  libX11-devel \
  libXcursor-devel \
  libXrandr-devel \
  libXi-devel \
  libXinerama-devel \
  wayland-devel \
  wayland-protocols \
  libxkbcommon-devel \
  fontconfig-devel
```

- `wayland-devel` — includes `wayland-scanner` on Fedora (no separate package needed)

### Arch

```bash
sudo pacman -S --needed \
  base-devel \
  cmake \
  pkgconf \
  mesa \
  libx11 \
  libxcursor \
  libxrandr \
  libxi \
  libxinerama \
  wayland \
  wayland-protocols \
  libxkbcommon \
  fontconfig
```

- `base-devel` — GCC, make and friends
- `wayland` — includes `wayland-scanner` on Arch (no separate package needed)

## Building

```bash
git clone --recursive https://github.com/nikelaz/machina.git
cd machina

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
```

The resulting binary is `build/machina`. Run it directly:

```bash
./build/machina
```

To build the API documentation (requires Doxygen):

```bash
cmake --build build --target docs
# output: docs/html/index.html
```

The generated API documentation is also hosted online at
<https://nikelaz.github.io/machina/>.

## License

This project is licensed under the [MIT License](LICENSE).

Third-party vendored libraries keep their own licenses (ImGui — MIT, GLFW — Zlib).
