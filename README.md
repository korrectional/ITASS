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
cargo add iroh


packages:
rustup
gcc



  Blacklist NVIDIA and Nouveau modules so the kernel never loads them
  boot.blacklistedKernelModules = [ "nouveau" "nvidia" "nvidia_drm" "nvidia_modeset" ];

  Completely cut power to the dGPU to prevent it from draining the battery
  boot.extraModprobeConfig = ''
    options nouveau modeset=0
  '';
