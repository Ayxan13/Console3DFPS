//
// Created by Ayxan Haqverdili on 2021-04-22.
//

#pragma once
#include <string_view>

// Map for the character to walk in
class Map final {
private:
	static float constexpr _depth = 20.f;

	static std::wstring_view constexpr _layout =
		L"#################################################################"
		L"#...............................................................#"
		L"#...#############################################...#####...#####"
		L"#.......#...................................#...................#"
		L"#...#...#...#############################...#############...#...#"
		L"#...#...#...............................................#...#...#"
		L"#...#...#...#########################################...#...#...#"
		L"#...#...#.......#...#...............................#...#...#...#"
		L"#...#...#...#...#...#...#####################...#...#...#...#...#"
		L"#...#...#...#...#...#...#...................#...#...#...#.......#"
		L"#...#...#...#...#...#...#...#...#########...#...#...#...#...#...#"
		L"#.......#...........#...#...#.......................#.......#...#"
		L"#...#####...#...#...#...#...#...#########...#########...#####...#"
		L"#...#...#...#...#...#...#...#...............#...........#...#...#"
		L"#...#...#...#...#...#...#...............#...#...#########...#...#"
		L"#...#...#...#...#...#...#...............#...#.......#...#...#...#"
		L"#...#...#...#...#...#...#...............#...#...#...#...#...#...#"
		L"#...#...#...............#...................#...#.......#...#...#"
		L"#...#...#...#############............########...#...#...#...#####"
		L"#...#...#...#...........#...................#...#...#.......#...#"
		L"#...#...#####...#####...#...#############...#...#...#####...#...#"
		L"#...#...#...#...#.......#...................#...........#.......#"
		L"#...#...#...#...#...#...#####...#####...#############...#...#...#"
		L"#...#.......#.......#...#...............#...................#...#"
		L"#...#...#...#...#####...#########...#####...#################...#"
		L"#.......#.......#.......#...........#.......................#...#"
		L"#################...#########...#####################...#####...#"
		L"#.......................#.......................#...............#"
		L"#...#########...#####...#########...#########...#########...#...#"
		L"#...#...........................#...........................#...#"
		L"#...#...#####################...#...#########################...#"
		L"#...#...........................#...............................#"
		L"#################################################################";

	static int constexpr _width = _layout.find_first_not_of(L"#") - 1;
	static int constexpr _height = _layout.size() / _width;

public:
	[[nodiscard]] static constexpr int Width() noexcept {
		return _width;
	}

	[[nodiscard]] static constexpr int Height() noexcept {
		return _height;
	}

	[[nodiscard]] static constexpr float Depth() noexcept {
		return _depth;
	}

	[[nodiscard]] static constexpr wchar_t GetPix(int const x, int const y) noexcept {
		return _layout[y * _width + x];
	}
};