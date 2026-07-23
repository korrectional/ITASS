This is I.T.A.S.S, pronounced eet-ass, also known as the Internet Transmitted Activity Surveillance System.

commands
cargo install espup
espup install
cargo install espflash
cargo install cargo-generate

Linux
. $HOME/export-esp.sh
Windows
. $env:USERPROFILE\export-esp.ps1
Atode:
cargo generate esp-rs/esp-idf-template
cargo build



packages:
  rustup
  # Core Compilers and Build Tools
  gcc
  gnumake
  binutils
  coreutils

  # Headers & Libraries
  glibc
  glibc.dev

  # Common Build Automations
  pkg-config
  autoconf
  automake
  libtool
  cmake

  # Essential Utilities
  git
  wget


  Blacklist NVIDIA and Nouveau modules so the kernel never loads them
  boot.blacklistedKernelModules = [ "nouveau" "nvidia" "nvidia_drm" "nvidia_modeset" ];

  Completely cut power to the dGPU to prevent it from draining the battery
  boot.extraModprobeConfig = ''
    options nouveau modeset=0
  '';
