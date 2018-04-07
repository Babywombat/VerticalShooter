#ifndef VS_GAME_LOGIC_HPP
#define VS_GAME_LOGIC_HPP

#include <d2d1.h>
#include "Player.h"
#include "Quadtree.h"
#include "BulletFactory.h"
#include "EnemyFactory.h"

namespace vs {
	class game;

	class game_logic {
	private:
		player						_player;
		quadtree					_quadtree;
		std::vector<game_object*>	_objects;

		enemy_factory				_enemy_factory;
		bullet_factory				_bullet_factory;

		game*						_game;

		float						_time_since_spawn;
		float						_spawn_speed;

		int							_points;
		int							_killed_enemies;

		void						check_collisions();
		void						cleanup(bool end = false);
		void						create_enemy(enemy::E_ENEMY_TYPE type, float x, float y);
		void						on_update_spawn(const float delta);
	public:
		game_logic(game* game);
		~game_logic();

		void						initialize();

		void						on_render(ID2D1HwndRenderTarget* render_target, IDWriteTextFormat* text_format);
		bool						on_update(double delta);

		void						create_bullets(bullet::E_BULLET_TYPE type, float x, float y, transform_2d::E_LAYER layer = transform_2d::E_LAYER::player_bullet);
		game*						get_game() const;

	};
}

#endif //VS_GAME_LOGIC_HPP