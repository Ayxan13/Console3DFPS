//
// Created by Ayxan Haqverdili on 2021-04-22.
//

#pragma once
#include "Map.hpp"
#include <numbers>

class Player final {
private:
	float _x = Map::Width() / 2.f;
	float _y = Map::Height() / 2.f;
	float _angle = 0.f;
	static float constexpr _fieldOfView = std::numbers::pi_v<float> / 4.f;

	static float constexpr _turnCoefficient = 2.f;
	static float constexpr _walkCoefficient = 5.f;
public:

	[[nodiscard]] float& X() noexcept { return _x; }
	[[nodiscard]] float const& X() const noexcept { return _x; }
	[[nodiscard]] float& Y() noexcept { return _y; }
	[[nodiscard]] float const& Y() const noexcept { return _y; }
	[[nodiscard]] float& Angle() noexcept { return _angle; }
	[[nodiscard]] float const& Angle() const noexcept { return _angle; }
	[[nodiscard]] static constexpr float FieldOfView() noexcept { return _fieldOfView; }

	void TurnCounterClockWise(float const elapsedTime) noexcept {
		_angle -= elapsedTime * _turnCoefficient;
	}

	void TurnClockWise(float const elapsedTime) noexcept {
		_angle += elapsedTime * _turnCoefficient;
	}

	void WalkForward(float const elapsedTime) noexcept {
		_x += sinf(_angle) * _walkCoefficient * elapsedTime;
		_y += cosf(_angle) * _walkCoefficient * elapsedTime;
	}

	void WalkBackward(float const elapsedTime) noexcept {
		_x -= sinf(_angle) * _walkCoefficient * elapsedTime;
		_y -= cosf(_angle) * _walkCoefficient * elapsedTime;
	}
};