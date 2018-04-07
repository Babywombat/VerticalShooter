#ifndef VS_ENEMY_FACTORY
#define VS_ENEMY_FACTORY
#include "Enemy.h"

namespace vs {
	class game_logic;

	class enemy_factory {
	private:
		ID2D1PathGeometry *				_triangle_geometry;
		ID2D1PathGeometry *				_hexagon_geometry;
		game_logic*						_game_logic;
	public:

		enemy_factory(game_logic* game);
		~enemy_factory();

		enemy*							make_enemy(enemy::E_ENEMY_TYPE type, float x, float y) const;
		void							initialize();
	};
}

#endif //VS_ENEMY_FACTORY