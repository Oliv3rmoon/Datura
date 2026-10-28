<p align="center">
  <img src="sce_sys/icon0.png" width="128" alt="Nightshade Stream icon">
</p>

<h1 align="center">Nightshade Stream</h1>

<p align="center">
  <strong>Moonlight game streaming for PS5 homebrew, by Oliv3rmoon: everything in ProsperoLight, in Nightshade's black and red, updated from its own releases.</strong>
</p>

<p align="center">
  <a href="https://github.com/Oliv3rmoon/Nightshade-Stream/releases/latest"><img src="https://img.shields.io/github/v/release/Oliv3rmoon/Nightshade-Stream?style=for-the-badge&label=download&color=e5484d&labelColor=0d0d0f" alt="Download the latest release"></a>
  <a href="https://discord.gg/pSqgRU3YP9"><img src="https://img.shields.io/badge/discord-nightly-0d0d0f?style=for-the-badge&logo=discord&logoColor=e5484d" alt="Discord: nightly"></a>
  <a href="https://buymeacoffee.com/oliv3rmoon"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-0d0d0f?style=for-the-badge&logo=buymeacoffee&logoColor=e5484d" alt="Buy me a coffee"></a>
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-GPL--3.0--or--later-0d0d0f?style=for-the-badge&labelColor=0d0d0f&color=e5484d" alt="GPL-3.0-or-later"></a>
</p>

Nightshade Stream is Oliv3rmoon's release of ProsperoLight by BlackBearReloaded, a port of
Moonlight. It is [ProsperoLight](https://github.com/blackbearreloaded/ProsperoLight) 01.000.110,
the native Moonlight client for PS5 homebrew that streams games and the desktop from a
Sunshine-compatible PC, with the look of [Nightshade](https://github.com/Oliv3rmoon/Nightshade) and
updates from this repository. The current release is **01.001.000**; what changed is in the
[changelog](CHANGELOG.md).

## What you get

- **Everything in ProsperoLight.** Hardware H.264 and HEVC (HDR10 included) at up to 4K and 120 FPS,
  frame pacing and VRR, PyroWave, up to four DualSense controllers with haptics and adaptive
  triggers, keyboard and mouse, home-screen forwarders and a launcher in 31 languages. Nothing is
  taken out, and it streams with ProsperoLight 01.000.110's measured build settings.
- **Nightshade's look.** Black and red, clean and dark: black glass panels, a red accent, a
  near-black sky with a low red glow, and the nightshade flower with the stream going out of it as
  the mark, on the icon and the home-screen pictures.
- **Updates from its own releases.** At the start it asks
  [Oliv3rmoon/Nightshade-Stream](https://github.com/Oliv3rmoon/Nightshade-Stream/releases) for a
  newer release, shows its notes, and installs it with **Update now**. It never offers
  ProsperoLight's own releases, which would put the old look back.
- **Your PCs stay paired.** It keeps ProsperoLight's title ID and data folder, so saved PCs,
  pairing and settings carry over.

## Install

1. Close ProsperoLight (or Nightshade Stream).
2. Download `PPSA99002.zip` from the [latest release](https://github.com/Oliv3rmoon/Nightshade-Stream/releases/latest)
   and unzip it.
3. Copy its `PPSA99002` folder over your current one (`/data/homebrew/PPSA99002`), replacing the
   files.

It keeps ProsperoLight's title ID, so it replaces ProsperoLight, and your PCs, pairing and settings
stay as they are (they live in `/data/prosperolight`). The home screen calls it
**Nightshade Stream**; the new icon and pictures show once the title is registered again (remove
its old registration from the home screen and let your loader, such as ShadowMountPlus, register
it). To go back, copy an
[official release](https://github.com/blackbearreloaded/ProsperoLight/releases) over it the same
way. Don't leave a `PPSA99002.exfat` or `PPSA99002.ffpfsc` mounted beside the folder.

## Updates

Once per launch Nightshade Stream asks GitHub for the newest release of
[Oliv3rmoon/Nightshade-Stream](https://github.com/Oliv3rmoon/Nightshade-Stream/releases) that is
not a pre-release. When it is newer than the one installed and carries `PPSA99002.zip` and
`SHA256SUMS`, the app offers **Update now**, **What's new** and **Skip**; **Update now** downloads
the ZIP, checks it against `SHA256SUMS`, and replaces the app's files once it has closed. Your data
in `/data/prosperolight` is not touched. Like ProsperoLight, it needs a folder installation with
filesystem access for this (the console's payload loader on port 9021); otherwise update by
copying the folder as above. A release ZIP built by this repository's workflow can be checked with
`gh attestation verify PPSA99002.zip -R Oliv3rmoon/Nightshade-Stream`.

## Requests, bugs and support

- **Ask for a fix or a feature:** [open an issue](https://github.com/Oliv3rmoon/Nightshade-Stream/issues/new/choose),
  or ask in **[nightly on Discord](https://discord.gg/pSqgRU3YP9)**.
- **Bugs in my releases:** open an issue here. Turn on **Diagnostic logs** in Settings first; the
  About page shows where the logs are. Leave pairing PINs, host names and addresses out.
- **If my work helps you,** you can [buy me a coffee](https://buymeacoffee.com/oliv3rmoon).

## Credits

- **[ProsperoLight](https://github.com/blackbearreloaded/ProsperoLight)**, by
  **BlackBearReloaded** ([GitHub](https://github.com/blackbearreloaded)), who created it and wrote
  it, with its contributors Nikita Dybov and Kris Escobar and everyone who tests it. Nightshade
  Stream is their app with a new look and a new update source; the credit for it is theirs.
- **[Moonlight](https://moonlight-stream.org)** and
  [moonlight-common-c](https://github.com/moonlight-stream/moonlight-common-c) (limelight), whose
  protocol it speaks, and **[Sunshine](https://github.com/LizardByte/Sunshine)**, the host on the
  PC. All credit for the streaming protocol goes to the Moonlight developers and contributors.
- **[Nightshade](https://github.com/Oliv3rmoon/Nightshade)** and Nightshade TV, whose palette, art
  code and GitHub update check this release reuses.

Nightshade Stream is an unofficial release. ProsperoLight is made by BlackBearReloaded and its
contributors; neither they, the Moonlight or Sunshine projects, nor Sony endorse Nightshade Stream.
It is free software under the GNU General Public License, version 3 or later, as ProsperoLight is
([LICENSE](LICENSE)). Everything below is the official README.

---

<p align="center">
  <img src="sce_sys/icon0.png" width="128" alt="ProsperoLight icon">
</p>

<h1 align="center">ProsperoLight</h1>

<p align="center">
  <strong>Moonlight game streaming, natively on PlayStation 5.</strong><br>
  Stream games and your desktop from a Sunshine-compatible PC to a homebrew-enabled PS5.
</p>

<p align="center">
  <img src="docs/images/prosperolight.png" alt="ProsperoLight launcher showing a paired PC">
</p>

Features and fixes in the `main` branch may not be available in the [latest published release](https://github.com/blackbearreloaded/ProsperoLight/releases). Check the [changelog](CHANGELOG.md) and the release notes before updating.

## Features

- **Native PS5 video:** hardware-accelerated H.264 and HEVC (including HDR10) through VideoDec2 and AGC, with 1080p, 1440p and 4K stream options.
- **High-refresh streaming:** 30, 60, 90 and 120 FPS presets, plus Custom 30–120 FPS. Actual performance depends on codec, bitrate and hardware.
- **Frame pacing and VRR:** Unpaced, fixed-refresh Paced and adaptive Paced+VRR modes. Current source builds include Low Latency, Balanced and Smooth VRR timing profiles and low-FPS frame repetition.
- **PyroWave:** an optional Vulkan GPU decoder with SDR/HDR and 4:2:0/4:4:4 profiles, requiring a compatible Vibepollo/Vibeshine host.
- **Controllers and input:** up to four DualSense controllers, supported haptics/adaptive triggers, USB keyboard and mouse, plus on-screen keyboard and controller-driven mouse mode.
- **Audio:** selectable stereo or 5.1-channel Opus playback.
- **A console-first launcher:** automatic LAN discovery, multiple saved PCs, application artwork, persistent settings, and a UI available in 31 languages.
- **Updates and diagnostics:** in-app update support for compatible folder installations, performance overlay, and optional timing/log capture.



## Get started

1. **Prepare your PS5.** You need a console with a compatible homebrew environment and title loader already configured. ProsperoLight does not install or provide an exploit.
2. **Install ProsperoLight.** Get `PPSA99002.zip` from [Releases](https://github.com/blackbearreloaded/ProsperoLight/releases), extract it, and copy the complete `PPSA99002/` folder to `/data/homebrew/`. Close the app before replacing an older installation; refresh your homebrew loader's title registration.
3. **Start Sunshine** (or a compatible host) on your PC. A wired local network is strongly recommended.
4. **Pair and play.** Open ProsperoLight, select a discovered PC or add its address, and enter the pairing PIN in your host's web interface. Open **Games** and choose an app or Desktop.

Press **Touchpad + L1** to end the stream and return to the launcher. Pairings and settings normally remain in `/data/prosperolight` when updating the app.

**[Full user guide →](docs/USER_GUIDE.md)** — installation, pairing, updates, controllers, settings and saved data.

## Controls


| During streaming        | Action                            |
| ----------------------- | --------------------------------- |
| **Touchpad + L1**       | Return to ProsperoLight           |
| **Touchpad + R1**       | Toggle performance overlay        |
| **Touchpad + Square**   | Toggle controller/mouse mode      |
| **Touchpad + Triangle** | Open/close the on-screen keyboard |


Touchpad means pressing the touchpad **until it clicks**. See the [complete controls reference](docs/USER_GUIDE.md#controls), including the host Back/Guide shortcuts and multi-controller behavior.

## Video quality and compatibility



### Bitrate limits

**H.264/HEVC decoding and PyroWave have different performance characteristics.** In measured native 4K HEVC sessions, bitrates above roughly 80 Mbps at 120 FPS can exceed the PS5 decoder's real-time budget. Increasing bitrate is not always an improvement. PyroWave has different host and network requirements.

### VRR and frame timing

VRR support depends on the console, firmware, TV and actual output mode; a successful VideoOut API call does **not** prove physical HDMI VRR or a particular latency improvement. For a starting point, try a wired network, native HEVC, and conservative bitrate before experimenting with higher refresh rates.

**[Performance and video guide →](docs/PERFORMANCE_GUIDE.md)** — codec selection, measured bitrate limits, pacing modes and VRR caveats.

## Documentation


| For                | Start here                                                                                                                                             |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Players**        | [User guide](docs/USER_GUIDE.md) · [Performance guide](docs/PERFORMANCE_GUIDE.md) · [Troubleshooting](docs/TROUBLESHOOTING.md)                         |
| **Advanced users** | [PyroWave](docs/PYROWAVE.md) · [DualSense](docs/DUALSENSE.md) · [Frame pacing tests](docs/PACING_TEST_MATRIX.md) · [Home-screen forwarders](docs/FORWARDER.md)                                       |
| **Developers**     | [Getting started](docs/GETTING_STARTED.md) · [Architecture](docs/ARCHITECTURE.md) · [Testing](docs/TESTING.md) · [Deployment](docs/DEPLOYMENT.md)      |
| **Maintainers**    | [Configuration](docs/CONFIGURATION.md) · [Validation](docs/VALIDATION.md) · [Release packaging](docs/RELEASE_ZIP.md) · [Contributing](CONTRIBUTING.md) |
| **Project**        | [Changelog](CHANGELOG.md) · [Roadmap / ideas](docs/ROADMAP.md) · [Third-party notices](THIRD_PARTY_NOTICES.md)                                         |




## Build from source

See [Getting started](docs/GETTING_STARTED.md) for Linux/WSL prerequisites and reproducible dependencies. Once set up:

```bash
git submodule update --init --recursive
make doctor
make check
```

The build produces a complete `dist/PPSA99002/` app directory. For the safe FTP deployment workflow, see [Deployment](docs/DEPLOYMENT.md).

## Support and contributions

Found a bug? [Open an issue](https://github.com/blackbearreloaded/ProsperoLight/issues) with your PS5 firmware, host version, codec/settings and reproduction steps. For stream problems, enable **Diagnostic logs** and attach relevant logs after reviewing [Troubleshooting](docs/TROUBLESHOOTING.md). Logs can contain local host addresses and app names; review them before sharing.

Contributions and testing across different TVs, firmwares and network setups are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md).

> [!IMPORTANT]
> This is an independent homebrew project, not an official Sony, Moonlight or Sunshine product. It requires a compatible homebrew-enabled console and includes no exploits, proprietary Sony SDK, firmware, keys or game assets. Use at your own risk and only with hardware and content you are entitled to use.


## Credits

Built with the [PS5 Payload SDK](https://github.com/ps5-payload-dev/sdk) by John Törnblom (ps5-payload-dev).
Third-party components, authors and licenses are listed in
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).

## License

Copyright © 2026 BlackBearReloaded. Licensed under GPL-3.0-or-later; see [LICENSE](LICENSE). Third-party components keep their own licenses. Binary releases are built from the tagged source in this repository.

## Disclaimer

- **No affiliation.** This is an independent homebrew project. It is not
affiliated with, endorsed by, or sponsored by Sony Interactive Entertainment.
"PlayStation", "PS5" and related marks are trademarks of Sony Interactive
Entertainment Inc. This project is not affiliated with or endorsed by the Moonlight or Sunshine projects.
- **No proprietary material.** No Sony SDK, firmware, encryption keys or
decrypted system modules are included.
- **No warranty.** This project is provided "as is", without warranty of any
kind, to the extent permitted by law. See sections 15 and 16 of the GPL.
- **Use at your own risk.** Running homebrew requires a modified console, which
may void its warranty, breach the platform's terms of service, or cause data
loss.
- **Legal use only.** Use it only with hardware, accounts and content you own.
This project does not support or enable piracy.



## AI assistance

This project was developed with AI assistance from OpenAI and/or Anthropic tools.

