#ifndef VS_BULLET_HPP
#define VS_BULLET_HPP

#include "GameObject.h"

namespace vs {
	class bullet : public game_object {
	private:

	public:
		bullet();
		~bullet();

		void			on_update(double delta_time) override;
		void			on_render(ID2D1HwndRenderTarget* render_target) override;
		void			initialize() override;
		void			handle_collision(transform_2d* collided_object) override;
	};
}

#endif //VS_BULLET_HPP