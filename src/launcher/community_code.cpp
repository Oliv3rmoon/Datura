/*
 * Datura - The community's QR code, which the About page and the card draw.
 * Copyright (C) 2026 Oliv3rmoon
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "launcher/community_code.hpp"

#include "community.hpp"
// The vendored encoder (MIT, third_party/qrcodegen), compiled with the launcher.
#include "qrcodegen.c"

namespace launcher
{

QrCode make_qr_code(const std::string &text)
{
    QrCode code;
    uint8_t qr[qrcodegen_BUFFER_LEN_FOR_VERSION(5)];
    uint8_t scratch[sizeof(qr)];
    if (text.empty() || !qrcodegen_encodeText(text.c_str(), scratch, qr, qrcodegen_Ecc_MEDIUM, 1, 5,
                                              qrcodegen_Mask_AUTO, true))
        return code;
    code.size = qrcodegen_getSize(qr);
    for (int y = 0; y < code.size; ++y)
        for (int x = 0; x < code.size; ++x)
            code.modules.push_back(qrcodegen_getModule(qr, x, y));
    return code;
}

const QrCode &community_code()
{
    static const QrCode code = make_qr_code(prosperolight::community::kUrl);
    return code;
}

} // namespace launcher
