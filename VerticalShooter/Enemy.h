#ifndef VS_ENEMY_HPP
#define VS_ENEMY_HPP

#include "GameObject.h"

namespace vs {
	class player;

	class enemy : public game_object {
	public:
		enemy();
		~enemy();

		void			on_update(double delta_time) override;
		void			on_render(ID2D1HwndRenderTarget* render_target) override;
		void			initialize() override;
		void			handle_collision(transform_2d* collided_object) override;
	};
}

#endif //VS_ENEMY_HPP