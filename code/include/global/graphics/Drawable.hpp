#pragma once

namespace id {
    namespace graphics {
        class Renderer;

        class Drawable {
        public:
            virtual ~Drawable() {};
            virtual void draw(id::graphics::Renderer& renderer, bool is2d = false) = 0;
        };
    } /* graphics */
} /* id */
