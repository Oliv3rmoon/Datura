# Datura - The community's QR code, read back as a phone does, and the card's saved state.
# Copyright (C) 2026 Oliv3rmoon
# SPDX-License-Identifier: GPL-3.0-or-later
import json
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# What the code must open, written out here rather than taken from the app.
INVITATION = "https://discord.gg/pSqgRU3YP9"
TEXTS = [
    "Join the community",
    "Get help, hear about new releases and meet other players on Discord.",
    "Our server on Discord",
    "Scan the code with your phone, or open the address.",
    "You can find it again in About.",
]

CHECK = r'''
#define INVITATION "@INVITATION@"
#include "community.hpp"
#include "launcher/community_code.hpp"
#include "qr_reader.hpp"
#include "qrcodegen.h"
#include <cstdio>
#include <cstring>
#include <set>
#include <string>

static int failures = 0;
static void expect(bool ok, const char *what)
{
    if (!ok)
    {
        ++failures;
        std::fprintf(stderr, "FAILED: %s\n", what);
    }
}

static qr_reader::Modules modules_of(const launcher::QrCode &code)
{
    qr_reader::Modules modules(code.size, std::vector<bool>(code.size, false));
    for (int y = 0; y < code.size; ++y)
        for (int x = 0; x < code.size; ++x)
            modules[y][x] = code.dark(x, y);
    return modules;
}

int main(int argc, char **argv)
{
    // The reader, on the vendored encoder's symbols: every level and mask, versions 1 to 9. A
    // module changed in the data is caught by the error correction check.
    const std::string texts[] = {"hi", INVITATION, std::string(90, 'q') + "/end",
                                 "https://example.invalid/" + std::string(150, 'z')};
    std::set<int> versions;
    for (const std::string &text : texts)
        for (int level = 0; level < 4; ++level)
            for (int mask = 0; mask < 8; ++mask)
            {
                uint8_t qr[qrcodegen_BUFFER_LEN_FOR_VERSION(9)];
                uint8_t scratch[sizeof(qr)];
                if (!qrcodegen_encodeText(text.c_str(), scratch, qr,
                                          static_cast<qrcodegen_Ecc>(level), 1, 9,
                                          static_cast<qrcodegen_Mask>(mask), false))
                    continue;
                const int size = qrcodegen_getSize(qr);
                versions.insert((size - 17) / 4);
                qr_reader::Modules modules(size, std::vector<bool>(size, false));
                for (int y = 0; y < size; ++y)
                    for (int x = 0; x < size; ++x)
                        modules[y][x] = qrcodegen_getModule(qr, x, y);
                expect(qr_reader::read(modules) == text, "the reader reads the encoder's symbol");
                modules[size - 1][size - 1] = !modules[size - 1][size - 1]; // always data
                expect(!qr_reader::read(modules), "the reader refuses a damaged symbol");
            }
    expect(versions.size() >= 5 && *versions.rbegin() == 9, "versions 1 to 9 were read");

    // The code the About page and the card draw.
    const launcher::QrCode &code = launcher::community_code();
    const auto read = qr_reader::read(modules_of(code));
    std::printf("community code: version %d, reads %s\n", (code.size - 17) / 4,
                read ? read->c_str() : "nothing");
    expect(read && *read == INVITATION, "the community code opens exactly " INVITATION);
    expect(std::strcmp(prosperolight::community::kUrl, INVITATION) == 0 &&
               std::strcmp(prosperolight::community::kLink, "discord.gg/pSqgRU3YP9") == 0 &&
               std::strcmp(prosperolight::community::kName, "nightly") == 0,
           "the name and addresses");

    // The card's state: not seen until it is closed, then saved in its own file.
    std::snprintf(storage::g_paths.config, sizeof(storage::g_paths.config), "%s/config.bin",
                  argv[1]);
    expect(!prosperolight::community::seen(), "a new install has not seen the card");
    expect(prosperolight::community::set_seen(), "closing the card is saved");
    prosperolight::community::seen_preference = -1;
    expect(prosperolight::community::seen(), "the saved state is read back");
    return failures == 0 ? 0 : 1;
}
'''


class CommunityTests(unittest.TestCase):
    def test_code_opens_the_invitation_and_the_card_is_saved(self):
        compiler = shutil.which("clang++") or shutil.which("g++")
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder)
            (path / "check.cpp").write_text(CHECK.replace("@INVITATION@", INVITATION))
            subprocess.run(
                [compiler, "-std=c++20", "-I" + str(ROOT / "include"), "-I" + str(ROOT / "src"),
                 "-I" + str(ROOT / "third_party/ps5-homebrew-ui"),
                 "-I" + str(ROOT / "third_party/qrcodegen"),
                 "-I" + str(ROOT / "tools/launcher-host"), str(path / "check.cpp"),
                 str(ROOT / "src/launcher/community_code.cpp"), "-o", str(path / "check")],
                check=True)
            result = subprocess.run([str(path / "check"), folder], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("reads " + INVITATION + "\n", result.stdout)
            saved = (path / "prosperolight-community.bin").read_bytes()
            self.assertEqual(saved, b"PLC\x01\x01")

    def test_every_language_translates_the_new_texts(self):
        for catalog in sorted((ROOT / "assets/locales").glob("*.json")):
            values = json.loads(catalog.read_text(encoding="utf-8"))
            rendered = json.loads(
                (catalog.parent / "rendered" / catalog.name).read_text(encoding="utf-8"))
            for text in TEXTS:
                self.assertTrue(values[text], (catalog.name, text))
                self.assertIn(text, rendered, (catalog.name, text))
                if catalog.stem != "en":
                    self.assertNotEqual(values[text], text, (catalog.name, text))


if __name__ == "__main__":
    unittest.main()
