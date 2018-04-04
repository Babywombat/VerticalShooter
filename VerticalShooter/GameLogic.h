#ifndef VS_GAME_LOGIC_HPP
#define VS_GAME_LOGIC_HPP

#include <d2d1.h>
#include "Player.h"
#include "Quadtree.h"
#include "Enemy.h"

namespace vs {
	class game_logic {
	private:
		player					_player;
		quadtree				_quadtree;
		std::vector<enemy>		_enemies;
	public:
		game_logic();
		~game_logic();

		void initialize();

		void on_render(ID2D1HwndRenderTarget* render_target);
		bool on_update(double delta);
	};
}

#endif //VS_GAME_LOGIC_HPP