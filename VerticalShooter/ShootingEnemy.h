#ifndef VS_SHOOTING_ENEMY_HPP
#define VS_SHOOTING_ENEMY_HPP
#include "Enemy.h"

namespace vs {
	class game_logic;

	class shooting_enemy : public enemy {
		ID2D1PathGeometry*					_geometry;
		game_logic*							_game_logic;

		int									_current_direction;
		float								_time_since_bullet;
		float								_shooting_speed;

	public:
		shooting_enemy(ID2D1PathGeometry* geometry, game_logic* logic);
		~shooting_enemy();

		void								on_update(double delta_time) override;
		void								on_render(ID2D1HwndRenderTarget* render_target) override;
		void								initialize() override;
		E_ENEMY_TYPE						get_type() const override;
	};
}

#endif //VS_SHOOTING_ENEMY_HPP
