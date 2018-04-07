#include "EnemyFactory.h"
#include "Game.h"
#include "Utils.h"
#include "FastEnemy.h"
#include "ShootingEnemy.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
/// <param name="game">The game logic instance</param>
enemy_factory::enemy_factory(game_logic* game) :
	_triangle_geometry		(nullptr),
	_game_logic				(game){
}

/// <summary>
/// Destructor
/// </summary>
enemy_factory::~enemy_factory() = default;

/// <summary>
/// Initializes the factory
/// </summary>
void enemy_factory::initialize() {
	if (!_game_logic) return;
	const auto factory = _game_logic->get_game()->get_direct2d_factory();

	if (!factory) return;
	
	ID2D1GeometrySink* sink;

	//Create the triangle geometry
	auto hr = factory->CreatePathGeometry(&_triangle_geometry);
	if (SUCCEEDED(hr)) {
		//Write to the path geometry using the geometry sink.
		hr = _triangle_geometry->Open(&sink);

		if (SUCCEEDED(hr)) {

			sink->BeginFigure(
				D2D1::Point2F(0, 0),
				D2D1_FIGURE_BEGIN_FILLED
			);

			//Add triangle lines
			sink->AddLine(D2D1::Point2F(20, 0));
			sink->AddLine(D2D1::Point2F(10, 20));
			sink->AddLine(D2D1::Point2F(0, 0));

			sink->EndFigure(D2D1_FIGURE_END_CLOSED);

			sink->Close();
		}
		utils::safe_release(&sink);
	}

	//Create the hexagon geometry
	hr = factory->CreatePathGeometry(&_hexagon_geometry);
	if (SUCCEEDED(hr)) {
		//Write to the path geometry using the geometry sink.
		hr = _hexagon_geometry->Open(&sink);

		if (SUCCEEDED(hr)) {

			sink->BeginFigure(
				D2D1::Point2F(8, 0),
				D2D1_FIGURE_BEGIN_FILLED
			);

			//Add hexagon lines
			sink->AddLine(D2D1::Point2F(16, 0));
			sink->AddLine(D2D1::Point2F(24, 8));
			sink->AddLine(D2D1::Point2F(24, 16));
			sink->AddLine(D2D1::Point2F(16, 24));
			sink->AddLine(D2D1::Point2F(8, 24));
			sink->AddLine(D2D1::Point2F(0, 16));
			sink->AddLine(D2D1::Point2F(0, 8));
			sink->AddLine(D2D1::Point2F(8, 0));

			sink->EndFigure(D2D1_FIGURE_END_CLOSED);

			sink->Close();
		}
		utils::safe_release(&sink);
	}
	
}

/// <summary>
/// Creates a new enemy of the specified type
/// </summary>
/// <param name="type">Type of enemy</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <returns></returns>
enemy* enemy_factory::make_enemy(const enemy::E_ENEMY_TYPE type, const float x, const float y) const {
	enemy* new_enemy = nullptr;
	switch (type) {
	case enemy::normal: {
		new_enemy = new enemy();
		break;
	}
	case enemy::fast: {
		new_enemy = new fast_enemy(_triangle_geometry);
		break;
	}
	case enemy::shooting: {
		new_enemy = new shooting_enemy(_hexagon_geometry, _game_logic);
		break;
	}
	default: {
		return new_enemy;
	};
	}
	if (new_enemy) {
		new_enemy->initialize();
		new_enemy->set_position(x, y);
	}
	return new_enemy;
}
