#ifndef VS_GAME_LOGIC_HPP
#define VS_GAME_LOGIC_HPP

#include <d2d1.h>
#include "Player.h"
#include "Quadtree.h"
#include "BulletFactory.h"
#include "EnemyFactory.h"

namespace vs {
	class game_logic {
	private:
		player						_player;
		quadtree					_quadtree;
		std::vector<game_object*>	_objects;

		enemy_factory				_enemy_factory;
		bullet_factory				_bullet_factory;

		float						_time_since_spawn;
		float						_spawn_speed;

		int							_killed_enemies;

		void						check_collisions();
		void						cleanup(bool end = false);
		void						create_enemy(enemy_factory::E_ENEMY_TYPE type, float x, float y);
	public:
		game_logic();
		~game_logic();

		void						initialize();

		void						on_render(ID2D1HwndRenderTarget* render_target, IDWriteTextFormat* text_format);
		bool						on_update(double delta);

		void						create_bullet(bullet_factory::E_BULLET_TYPE type, float x, float y);

	};
}

#endif //VS_GAME_LOGIC_HPP