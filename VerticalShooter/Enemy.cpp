#include "Enemy.h"
#include "Player.h"
#include <cmath>

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
enemy::enemy(): 
	actor	(0, 0, 25, 25) {
	
}

/// <summary>
/// Destructor
/// </summary>
enemy::~enemy() = default;

/// <summary>
/// Updates the enemy
/// </summary>
/// <param name="delta_time">Time since last frame</param>
void enemy::on_update(double delta_time) {
	const auto current_change = _speed * static_cast<float>(delta_time);

	if(_player != nullptr) {
		const auto diff_x = static_cast<int>(_player->get_x()) - static_cast<int>(_x);
		const auto diff_y = static_cast<int>(_player->get_y()) - static_cast<int>(_y);

		const auto length = sqrt(diff_x * diff_x + diff_y * diff_y);
		_x += current_change * static_cast<float>(diff_x) / length;
		_y += current_change * static_cast<float>(diff_y) / length;
	}
}

/// <summary>
/// Renders the enemies visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
void enemy::on_render(ID2D1HwndRenderTarget* render_target) {
	if (!render_target) return;

	//Drawing the player's visuals
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(_color, &brush);

	//Calculate points for the visuals
	const auto center = D2D1::Point2F(_x + _width / 2, _y - _height / 2);

	//Draw the lines
	render_target->FillEllipse(D2D1::Ellipse(center, _width / 2, _height / 2), brush);
	render_target->DrawRectangle(get_aabb(), brush);

	brush->Release();
}

/// <summary>
/// Initializes the enemy
/// </summary>
void enemy::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::Red, 1.0f);
	_speed = 20.0f;
	_health = 1;
}

/// <summary>
/// Sets the player of this enemy
/// </summary>
/// <param name="player">Player to set</param>
void enemy::set_player(player* player) {
	_player = player;
}
