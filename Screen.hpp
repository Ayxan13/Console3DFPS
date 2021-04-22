//
// Created by Ayxan Haqverdili on 2021-04-22.
//

#pragma once
#include <memory>

class Screen final {
private:
    static int constexpr _width = 600;
    static int constexpr _height = 200;
    std::unique_ptr<wchar_t[]> const _buffer{ new wchar_t[_width * _height] };

    [[nodiscard]] static constexpr int Index(int const x, int const y) noexcept {
        return y * _width + x;
    }

public:
    Screen() {
        _buffer[_height * _width - 1] = '\0';
    }

    [[nodiscard]] constexpr static int Width() noexcept {
        return _width;
    }

    [[nodiscard]] constexpr static int Height() noexcept {
        return _height;
    }

    [[nodiscard]] constexpr static int Area() noexcept {
        return _width * _height;
    }

    [[nodiscard]] wchar_t GetPix(int const x, int const y) const noexcept {
        return _buffer[Index(x, y)];
    }

    void SetPix(int const x, int const y, wchar_t const val) noexcept {
        _buffer[Index(x, y)] = val;
    }

    [[nodiscard]] wchar_t* Buffer() noexcept {
        return _buffer.get();
    }

    [[nodiscard]] wchar_t const* Buffer() const noexcept {
        return _buffer.get();
    }
};