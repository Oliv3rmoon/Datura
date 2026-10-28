#!/usr/bin/env python3
# Nightshade Stream - The update check against GitHub releases, built and run on the host.
# Copyright (C) 2026 Oliv3rmoon
# SPDX-License-Identifier: GPL-3.0-or-later
"""Builds tests/github_release_check.cc with the update kit's files it tests (update_check.c
without its network side, github_release.c, self_update.c, self_update_sha256.c) under the
address and undefined-behaviour sanitizers, warnings as errors, and runs it. CC and CXX name other
compilers (default: clang, clang++). As Nightshade TV's tests/test_github_release.py."""

import os
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KIT = ROOT / "third_party/update-check"
CHECK = ROOT / "tests/github_release_check.cc"
FLAGS = ["-O1", "-g", "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
         "-fno-omit-frame-pointer", "-Wall", "-Wextra", "-Werror",
         "-DUPDATE_CHECK_NO_NETWORK=1", "-UNDEBUG"]


class GitHubReleaseTest(unittest.TestCase):
    def test_update_check_asks_only_the_repositorys_releases(self):
        cc = os.environ.get("CC", "clang")
        cxx = os.environ.get("CXX", "clang++")
        if not shutil.which(cc) or not shutil.which(cxx):
            self.skipTest(f"needs {cc} and {cxx}")
        with tempfile.TemporaryDirectory() as directory:
            objects = []
            for name in ("update_check", "github_release", "self_update", "self_update_sha256"):
                objects.append(str(Path(directory) / f"{name}.o"))
                subprocess.run([cc, "-std=c11", *FLAGS, "-c", str(KIT / f"{name}.c"),
                                "-o", objects[-1]], check=True)
            executable = Path(directory) / "github-release-check"
            subprocess.run([cxx, "-std=c++20", "-pthread", *FLAGS, "-I" + str(KIT), str(CHECK),
                            *objects, "-o", str(executable)], check=True)
            result = subprocess.run([str(executable)], capture_output=True, text=True,
                                    timeout=120, check=False)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr[-3000:])
        self.assertIn("PASS", result.stdout)

    def test_the_app_asks_nightshade_streams_repository(self):
        launcher = (ROOT / "src/launcher/launcher_ps5.cpp").read_text(encoding="utf-8")
        self.assertIn('constexpr const char *kUpdateRepository = "Oliv3rmoon/Nightshade-Stream";',
                      launcher)
        self.assertIn('constexpr const char *kAppName = "Nightshade Stream";', launcher)
        # The catalog lists ProsperoLight's own releases: the app never asks it.
        self.assertNotIn("self_update_check(", launcher)
        self.assertNotIn("self_update_check_self(", launcher)
        self.assertIn("self_update_check_self_from(kUpdateRepository, kAppName", launcher)
        # ProsperoLight's own repositories are refused when the app is built.
        self.assertIn("static_assert(!ProsperoLightRepository(kUpdateRepository)", launcher)
        for refused in ("blackbearreloaded/prosperolight", "ledybacer/prosperolight"):
            self.assertIn(f'"{refused}"', launcher)


if __name__ == "__main__":
    unittest.main()
