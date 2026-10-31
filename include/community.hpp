/*
 * Datura - The community: its Discord server, on the About page and on a card shown once.
 * Copyright (C) 2026 Oliv3rmoon
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#pragma once
#include "app_storage.hpp"
#include <cstdio>
namespace prosperolight::community
{
// The server's name, its invitation as a player would type it, and the address its QR code
// holds. Not translated: a name and an address are the same in every language.
inline constexpr const char *kName = "nightly";
inline constexpr const char *kLink = "discord.gg/pSqgRU3YP9";
inline constexpr const char *kUrl = "https://discord.gg/pSqgRU3YP9";

// The card that names the server was closed, and is not shown again: kept beside the other
// launcher preferences, in its own file.
inline int seen_preference = -1;
inline bool seen()
{
    if (seen_preference < 0)
    {
        seen_preference = 0;
        if (FILE *file = std::fopen(storage::setting_file("prosperolight-community.bin").c_str(),
                                    "rb"))
        {
            unsigned char bytes[5]{};
            if (std::fread(bytes, 1, sizeof(bytes), file) == sizeof(bytes) && bytes[0] == 'P' &&
                bytes[1] == 'L' && bytes[2] == 'C' && bytes[3] == 1 && bytes[4] <= 1)
                seen_preference = bytes[4];
            std::fclose(file);
        }
    }
    return seen_preference != 0;
}
inline bool set_seen()
{
    // Remembered for this run even when the file cannot be written: the card comes back at a
    // later start, and not before.
    seen_preference = 1;
    const auto path = storage::setting_file("prosperolight-community.bin");
    const auto temporary = path + ".tmp";
    FILE *file = std::fopen(temporary.c_str(), "wb");
    if (!file)
        return false;
    const unsigned char bytes[] = {'P', 'L', 'C', 1, 1};
    const bool written = std::fwrite(bytes, 1, sizeof(bytes), file) == sizeof(bytes);
    const int closed = std::fclose(file);
    if (!written || closed || std::rename(temporary.c_str(), path.c_str()) != 0)
    {
        std::remove(temporary.c_str());
        return false;
    }
    return true;
}
} // namespace prosperolight::community
