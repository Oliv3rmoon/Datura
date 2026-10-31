/*
 * Datura - The community's QR code, which the About page and the card draw.
 * Copyright (C) 2026 Oliv3rmoon
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <string>
#include <vector>

namespace launcher
{

// A QR code: its modules row by row (true: dark), size by size. Empty when the text does not fit.
struct QrCode
{
    int size = 0;
    std::vector<bool> modules;

    bool dark(int x, int y) const
    {
        return modules[static_cast<std::size_t>(y * size + x)];
    }
};

// The code of `text` (version 5 at most, the vendored QR Code generator's, third_party/qrcodegen).
QrCode make_qr_code(const std::string &text);

// The code of the community's invitation (community.hpp), made once.
const QrCode &community_code();

} // namespace launcher
