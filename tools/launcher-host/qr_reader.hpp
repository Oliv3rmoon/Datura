/*
 * Datura - A QR code read back from what the launcher draws, as a phone's reader does.
 * Copyright (C) 2026 Oliv3rmoon
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// Enough of a reader (ISO/IEC 18004) for the codes the launcher draws: versions 1 to 9, any
// error correction level and mask, byte-mode segments. Every block's error correction is
// checked, as a reader checks before it trusts the data; nothing is repaired. It knows nothing
// of the encoder in third_party/qrcodegen: tests/test_community.py checks it on that encoder's
// symbols, and the launcher check reads the About page and the community card with it.

#pragma once

#include "gfx/draw_list.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace qr_reader
{

using Modules = std::vector<std::vector<bool>>; // [row][column], true: dark

// Multiplication in GF(256) modulo x^8 + x^4 + x^3 + x^2 + 1.
inline std::uint8_t gf_multiply(std::uint8_t a, std::uint8_t b)
{
    unsigned product = 0;
    for (int bit = 7; bit >= 0; --bit)
    {
        product = ((product << 1) ^ ((product >> 7) * 0x11du)) & 0xffu;
        if ((b >> bit) & 1u)
            product ^= a;
    }
    return static_cast<std::uint8_t>(product);
}

// A block (its data, then its error correction) is a code word when its polynomial is zero at
// the first `ecc` powers of 2.
inline bool whole_block(const std::vector<std::uint8_t> &block, int ecc)
{
    std::uint8_t power = 1;
    for (int i = 0; i < ecc; ++i)
    {
        std::uint8_t value = 0;
        for (const std::uint8_t byte : block)
            value = static_cast<std::uint8_t>(gf_multiply(value, power) ^ byte);
        if (value != 0)
            return false;
        power = gf_multiply(power, 2);
    }
    return true;
}

// The 15 format bits of a level (as the symbol writes it: M 0, L 1, H 2, Q 3) and a mask.
inline int format_bits(int level, int mask)
{
    const int data = level << 3 | mask;
    int remainder = data;
    for (int i = 0; i < 10; ++i)
        remainder = (remainder << 1) ^ ((remainder >> 9) * 0x537);
    return (data << 10 | remainder) ^ 0x5412;
}

inline int bit_count(int value)
{
    int count = 0;
    for (; value != 0; value &= value - 1)
        ++count;
    return count;
}

inline bool masked(int mask, int i, int j) // i: row, j: column
{
    switch (mask)
    {
    case 0:
        return (i + j) % 2 == 0;
    case 1:
        return i % 2 == 0;
    case 2:
        return j % 3 == 0;
    case 3:
        return (i + j) % 3 == 0;
    case 4:
        return (i / 2 + j / 3) % 2 == 0;
    case 5:
        return (i * j) % 2 + (i * j) % 3 == 0;
    case 6:
        return ((i * j) % 2 + (i * j) % 3) % 2 == 0;
    default:
        return ((i * j) % 3 + (i + j) % 2) % 2 == 0;
    }
}

// The text a QR code holds, or nothing when it cannot be read.
inline std::optional<std::string> read(const Modules &m)
{
    // The standard's tables for versions 1 to 9, by level as the format bits number it.
    static constexpr int kCodewords[10] = {0, 26, 44, 70, 100, 134, 172, 196, 242, 292};
    static constexpr int kBlocks[4][10] = {{0, 1, 1, 1, 2, 2, 4, 4, 4, 5},
                                           {0, 1, 1, 1, 1, 1, 2, 2, 2, 2},
                                           {0, 1, 1, 2, 4, 4, 4, 5, 6, 8},
                                           {0, 1, 1, 2, 2, 4, 4, 6, 6, 8}};
    static constexpr int kBlockEcc[4][10] = {{0, 10, 16, 26, 18, 24, 16, 18, 22, 22},
                                             {0, 7, 10, 15, 20, 26, 18, 20, 24, 30},
                                             {0, 17, 28, 22, 16, 22, 28, 26, 26, 24},
                                             {0, 13, 22, 18, 26, 18, 24, 18, 22, 20}};
    // Where the alignment patterns' centres are, row and column alike (Annex E).
    static const std::vector<int> kAlignment[10] = {
        {}, {}, {6, 18}, {6, 22}, {6, 26}, {6, 30}, {6, 34}, {6, 22, 38}, {6, 24, 42}, {6, 26, 46}};

    const int size = static_cast<int>(m.size());
    const int version = (size - 17) / 4;
    if (size < 21 || (size - 17) % 4 != 0 || version > 9)
        return std::nullopt;
    for (const auto &row : m)
        if (static_cast<int>(row.size()) != size)
            return std::nullopt;

    // The format, from whichever copy is nearer a valid one.
    int first = 0, second = 0;
    for (int i = 0; i <= 5; ++i)
        first |= m[i][8] << i;
    first |= m[7][8] << 6 | m[8][8] << 7 | m[8][7] << 8;
    for (int i = 9; i < 15; ++i)
        first |= m[8][14 - i] << i;
    for (int i = 0; i < 8; ++i)
        second |= m[8][size - 1 - i] << i;
    for (int i = 8; i < 15; ++i)
        second |= m[size - 15 + i][8] << i;
    int level = -1, mask = -1, best = 99;
    for (int l = 0; l < 4; ++l)
        for (int k = 0; k < 8; ++k)
            for (const int read_bits : {first, second})
                if (const int distance = bit_count(read_bits ^ format_bits(l, k)); distance < best)
                {
                    best = distance;
                    level = l;
                    mask = k;
                }
    if (best > 3)
        return std::nullopt;

    // Which modules are the symbol's own patterns, not data.
    std::vector<std::vector<bool>> fixed(size, std::vector<bool>(size, false));
    const auto mark = [&](int top, int left, int rows, int columns)
    {
        for (int r = std::max(0, top); r < std::min(size, top + rows); ++r)
            for (int c = std::max(0, left); c < std::min(size, left + columns); ++c)
                fixed[r][c] = true;
    };
    mark(0, 0, 9, 9);        // finder, separator and format at the top left
    mark(0, size - 8, 9, 8); // at the top right
    mark(size - 8, 0, 8, 9); // at the bottom left, with the dark module
    mark(6, 0, 1, size);     // timing
    mark(0, 6, size, 1);
    const std::vector<int> &centres = kAlignment[version];
    for (const int r : centres)
        for (const int c : centres)
        {
            const int last = centres.back();
            if ((r == 6 && c == 6) || (r == 6 && c == last) || (r == last && c == 6))
                continue;
            mark(r - 2, c - 2, 5, 5);
        }
    if (version >= 7)
    {
        mark(0, size - 11, 6, 3);
        mark(size - 11, 0, 3, 6);
    }

    // The data, two columns at a time from the bottom right, up and down in turn.
    std::vector<std::uint8_t> codewords(static_cast<std::size_t>(kCodewords[version]), 0);
    std::size_t bit = 0;
    for (int right = size - 1; right >= 1; right -= 2)
    {
        if (right == 6)
            right = 5;
        const bool upward = ((right + 1) & 2) == 0;
        for (int step = 0; step < size; ++step)
            for (int j = 0; j < 2; ++j)
            {
                const int column = right - j;
                const int row = upward ? size - 1 - step : step;
                if (fixed[row][column] || bit >= codewords.size() * 8)
                    continue;
                if (m[row][column] != masked(mask, row, column))
                    codewords[bit / 8] |= static_cast<std::uint8_t>(0x80u >> (bit % 8));
                ++bit;
            }
    }

    // The blocks, interleaved: their data first, then their error correction.
    const int blocks = kBlocks[level][version];
    const int ecc = kBlockEcc[level][version];
    const int total = kCodewords[version];
    const int short_blocks = blocks - total % blocks;
    const int short_data = total / blocks - ecc;
    std::vector<std::vector<std::uint8_t>> data(static_cast<std::size_t>(blocks));
    std::vector<std::vector<std::uint8_t>> parity(static_cast<std::size_t>(blocks));
    std::size_t at = 0;
    for (int i = 0; i <= short_data; ++i)
        for (int b = 0; b < blocks; ++b)
            if (i < short_data + (b >= short_blocks ? 1 : 0))
                data[b].push_back(codewords[at++]);
    for (int i = 0; i < ecc; ++i)
        for (int b = 0; b < blocks; ++b)
            parity[b].push_back(codewords[at++]);
    std::vector<std::uint8_t> stream;
    for (int b = 0; b < blocks; ++b)
    {
        std::vector<std::uint8_t> block = data[b];
        block.insert(block.end(), parity[b].begin(), parity[b].end());
        if (!whole_block(block, ecc))
            return std::nullopt;
        stream.insert(stream.end(), data[b].begin(), data[b].end());
    }

    // The segments: byte mode only, as the launcher writes an address.
    std::size_t read_at = 0;
    const auto take = [&](int count)
    {
        int value = 0;
        for (int i = 0; i < count; ++i, ++read_at)
            value = value << 1 | ((stream[read_at / 8] >> (7 - read_at % 8)) & 1);
        return value;
    };
    std::string text;
    while (read_at + 4 <= stream.size() * 8)
    {
        const int mode = take(4);
        if (mode == 0)
            break;
        if (mode != 4 || read_at + 8 > stream.size() * 8)
            return std::nullopt;
        const int length = take(8);
        if (read_at + static_cast<std::size_t>(length) * 8 > stream.size() * 8)
            return std::nullopt;
        for (int i = 0; i < length; ++i)
            text += static_cast<char>(take(8));
    }
    return text;
}

// ---- what a draw list draws ----

inline bool colour_is(const float *colour, float value)
{
    return std::abs(colour[0] - value) < 0.01f && std::abs(colour[1] - value) < 0.01f &&
           std::abs(colour[2] - value) < 0.01f && colour[3] > 0.99f;
}

inline bool square(const hui::gfx::Instance &instance)
{
    return static_cast<int>(instance.params[3] + 0.5f) ==
               static_cast<int>(hui::gfx::Shape::rounded_rect) &&
           std::abs(instance.rect[2] - instance.rect[3]) < 0.01f;
}

// The QR code a list draws, module by module: the white square of its quiet zone and the dark
// squares inside it. Empty when the list draws none.
inline Modules drawn(const hui::gfx::DrawList &list)
{
    const auto &all = list.instances();
    for (const hui::gfx::Instance &quiet : all)
    {
        if (!square(quiet) || !colour_is(quiet.color_top, 1.0f) || quiet.rect[2] < 80.0f)
            continue;
        std::vector<const hui::gfx::Instance *> dark;
        float cell = quiet.rect[2];
        for (const hui::gfx::Instance &module : all)
            if (square(module) && colour_is(module.color_top, 0.0f) &&
                module.rect[0] >= quiet.rect[0] && module.rect[1] >= quiet.rect[1] &&
                module.rect[0] + module.rect[2] <= quiet.rect[0] + quiet.rect[2] + 0.01f &&
                module.rect[1] + module.rect[3] <= quiet.rect[1] + quiet.rect[3] + 0.01f)
            {
                dark.push_back(&module);
                cell = std::min(cell, module.rect[2]);
            }
        if (dark.empty())
            continue;
        const int size = static_cast<int>(std::lround(quiet.rect[2] / cell)) - 8;
        if (size < 21)
            continue;
        Modules modules(size, std::vector<bool>(size, false));
        for (const hui::gfx::Instance *module : dark)
        {
            const long column = std::lround((module->rect[0] - quiet.rect[0]) / cell) - 4;
            const long row = std::lround((module->rect[1] - quiet.rect[1]) / cell) - 4;
            if (column >= 0 && column < size && row >= 0 && row < size)
                modules[row][column] = true;
        }
        return modules;
    }
    return {};
}

} // namespace qr_reader
