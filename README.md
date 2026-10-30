<p align="center">
  <img src="sce_sys/icon0.png" width="128" alt="Datura icon">
</p>

<h1 align="center">Datura</h1>

<p align="center">
  <strong>Stream your PC's games to your PS5 at up to 4K and 120 FPS, in Nightshade's black and red.</strong>
</p>

<p align="center">
  Formerly Nightshade Stream
</p>

<p align="center">
  <a href="https://github.com/Oliv3rmoon/Datura/releases/latest"><img src="https://img.shields.io/github/v/release/Oliv3rmoon/Datura?style=for-the-badge&label=download&color=e5484d&labelColor=0d0d0f" alt="Download the latest release"></a>
  <a href="https://discord.gg/pSqgRU3YP9"><img src="https://img.shields.io/badge/discord-nightly-0d0d0f?style=for-the-badge&logo=discord&logoColor=e5484d" alt="Discord: nightly"></a>
  <a href="https://github.com/Oliv3rmoon/Datura/stargazers"><img src="https://img.shields.io/github/stars/Oliv3rmoon/Datura?style=for-the-badge&logo=github&logoColor=e5484d&color=e5484d&labelColor=0d0d0f" alt="GitHub stars"></a>
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-GPL--3.0--or--later-0d0d0f?style=for-the-badge&labelColor=0d0d0f&color=e5484d" alt="GPL-3.0-or-later"></a>
  <a href="https://buymeacoffee.com/oliv3rmoon"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-0d0d0f?style=for-the-badge&logo=buymeacoffee&logoColor=e5484d" alt="Buy me a coffee"></a>
</p>

Datura is a native game-streaming client for the PS5, and a Nightshade app by **[Oliv3rmoon](https://github.com/Oliv3rmoon)**: run Sunshine on your PC, pair once, and play your games and your desktop on the console. The current release is **01.001.001**, a full release; what changed is in the [changelog](CHANGELOG.md).

## Why Datura

- **Native PS5 video.** Hardware-decoded H.264 and HEVC, HDR10 included, at 1080p, 1440p or 4K, and at 30, 60, 90 or 120 FPS (or any rate from 30 to 120).
- **Smooth by design.** Frame pacing in three modes (Unpaced, Paced and Paced+VRR), and an optional PyroWave GPU decoder for hosts that support it.
- **Limits that were measured.** On one test setup, native 4K HEVC at 120 FPS stayed smooth up to 80 Mbps and froze above 100 Mbps. The [performance guide](docs/PERFORMANCE_GUIDE.md) has the numbers for each frame rate, and says where they stop applying.
- **Up to four DualSense controllers,** with haptics and adaptive triggers, plus a USB keyboard and mouse, an on-screen keyboard and a controller-driven mouse mode.
- **A launcher made for the couch.** Your PCs found on the network, several saved, with their application artwork, home-screen forwarders, a performance overlay and 31 languages.
- **Nightshade's look.** Black glass panels, a red accent, a near-black sky with a low red glow, and the nightshade flower with the stream going out of it on the icon and the home-screen pictures.
- **Updates from its own releases.** At the start it asks this repository for a newer release and installs it with **Update now**. Your PCs, pairing and settings carry over: it keeps the title ID (`PPSA99002`) and the data folder (`/data/prosperolight`).

## Install

You need a PS5 with a compatible homebrew environment and title loader already set up. Datura does not install or provide an exploit.

1. Close the app if it is running.
2. Download `PPSA99002.zip` from the [latest release](https://github.com/Oliv3rmoon/Datura/releases/latest) and unzip it.
3. Copy its `PPSA99002` folder over your current one (`/data/homebrew/PPSA99002`), replacing the files.

It keeps the original's title ID, so it installs over the original and your PCs, pairing and settings stay as they are. The home screen calls it **Datura**; the new icon and pictures show once the title is registered again (remove its old registration from the home screen and let your loader, such as ShadowMountPlus, register it). To go back, copy an [official release](https://github.com/blackbearreloaded/ProsperoLight/releases) over it the same way. Don't leave a `PPSA99002.exfat` or `PPSA99002.ffpfsc` mounted beside the folder.

**Then:** start Sunshine, or a compatible host, on your PC (a wired network is strongly recommended). Open Datura, choose the PC it found or add its address, and enter the pairing PIN in the host's web interface. Open **Games** and choose an app or Desktop. Hold the touchpad down until it clicks and press **L1** to end the stream and return to the launcher. The [user guide](docs/USER_GUIDE.md) covers pairing, controllers, settings and saved data.

### Updates

Once per launch Datura asks GitHub for the newest release of [Oliv3rmoon/Datura](https://github.com/Oliv3rmoon/Datura/releases) that is not a pre-release. When it is newer than the one installed and carries `PPSA99002.zip` and `SHA256SUMS`, the app offers **Update now**, **What's new** and **Skip**; **Update now** downloads the ZIP, checks it against `SHA256SUMS`, and replaces the app's files once it has closed. Your data in `/data/prosperolight` is not touched. It needs a folder installation with filesystem access for this (the console's payload loader on port 9021); otherwise update by copying the folder as above. A release ZIP built by this repository's workflow can be checked with `gh attestation verify PPSA99002.zip -R Oliv3rmoon/Datura`.

## Docs

| For | Start here |
| --- | --- |
| **Players** | [User guide](docs/USER_GUIDE.md) · [Performance guide](docs/PERFORMANCE_GUIDE.md) · [Troubleshooting](docs/TROUBLESHOOTING.md) |
| **Advanced users** | [PyroWave](docs/PYROWAVE.md) · [DualSense](docs/DUALSENSE.md) · [Frame pacing tests](docs/PACING_TEST_MATRIX.md) · [Home-screen forwarders](docs/FORWARDER.md) |
| **Developers** | [Getting started](docs/GETTING_STARTED.md) · [Architecture](docs/ARCHITECTURE.md) · [Testing](docs/TESTING.md) · [Deployment](docs/DEPLOYMENT.md) |
| **Maintainers** | [Configuration](docs/CONFIGURATION.md) · [Validation](docs/VALIDATION.md) · [Release packaging](docs/RELEASE_ZIP.md) · [Contributing](CONTRIBUTING.md) |
| **Project** | [Changelog](CHANGELOG.md) · [Roadmap](docs/ROADMAP.md) · [Third-party notices](THIRD_PARTY_NOTICES.md) |

## Requests, bugs and support

- **Ask for a fix or a feature:** [open an issue](https://github.com/Oliv3rmoon/Datura/issues/new/choose), or ask in **[nightly on Discord](https://discord.gg/pSqgRU3YP9)**.
- **Bugs in my releases:** open an issue here. Turn on **Diagnostic logs** in Settings first; the About page shows where the logs are. Leave pairing PINs, host names and addresses out.
- **If my work helps you,** you can [buy me a coffee](https://buymeacoffee.com/oliv3rmoon).

## The Nightshade family

Datura is one of seven repositories in the Nightshade family, all by [Oliv3rmoon](https://github.com/Oliv3rmoon): the same black-and-red look, one Discord.

| App | What it is |
| --- | --- |
| [**Nightshade**](https://github.com/Oliv3rmoon/Nightshade) | The Switch emulator for PS5 homebrew |
| [**Physalis**](https://github.com/Oliv3rmoon/Physalis) | Live TV, movies and Plex on the PS5 |
| **Datura** (this repo) | Game streaming from your PC to the PS5 |
| [**Mandrake**](https://github.com/Oliv3rmoon/Mandrake) | PS1 emulation, with two emulators |
| [**Dulcamara**](https://github.com/Oliv3rmoon/Dulcamara) | RPG Maker 2000 and 2003 games, and Ren'Py visual novels |
| [**Solanum**](https://github.com/Oliv3rmoon/Solanum) | A store for open-source PS5 homebrew, with its catalog [on the web](https://oliv3rmoon.github.io/Solanum-Catalog/) |
| [**Belladonna**](https://github.com/Oliv3rmoon/Belladonna) | Nightshade's PS5 Vulkan driver |

## Built on

[ProsperoLight](https://github.com/blackbearreloaded/ProsperoLight) 01.000.110 by BlackBearReloaded, a port of [Moonlight](https://moonlight-stream.org).

## Credits

- **[ProsperoLight](https://github.com/blackbearreloaded/ProsperoLight)**, by
  **BlackBearReloaded** ([GitHub](https://github.com/blackbearreloaded)), who created it and wrote
  it, with its contributors Nikita Dybov and Kris Escobar and everyone who tests it. Datura is their
  app with a new look and a new update source; the credit for it is theirs.
- **[Moonlight](https://moonlight-stream.org)** and
  [moonlight-common-c](https://github.com/moonlight-stream/moonlight-common-c) (limelight), whose
  protocol it speaks, and **[Sunshine](https://github.com/LizardByte/Sunshine)**, the host on the
  PC. All credit for the streaming protocol goes to the Moonlight developers and contributors.
- **[Nightshade](https://github.com/Oliv3rmoon/Nightshade)** and Physalis, whose palette, art
  code and GitHub update check this release reuses.
- Built with the [PS5 Payload SDK](https://github.com/ps5-payload-dev/sdk) by John Törnblom
  (ps5-payload-dev). Third-party components, authors and licenses are listed in
  [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).

## License

Datura is an unofficial release. ProsperoLight is made by BlackBearReloaded and its contributors; neither they, the Moonlight or Sunshine projects, nor Sony endorse Datura. It is free software under the GNU General Public License, version 3 or later, as ProsperoLight is ([LICENSE](LICENSE)).

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

> [!IMPORTANT]
> This is an independent homebrew project, not an official Sony, Moonlight or Sunshine product. It requires a compatible homebrew-enabled console and includes no exploits, proprietary Sony SDK, firmware, keys or game assets. Use at your own risk and only with hardware and content you are entitled to use.

## AI assistance

This project was developed with AI assistance from OpenAI and/or Anthropic tools.

## Help it grow

Like Datura? **[Star it](https://github.com/Oliv3rmoon/Datura)** and **[join the Discord](https://discord.gg/pSqgRU3YP9)**.
