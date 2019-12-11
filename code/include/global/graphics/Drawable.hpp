#pragma once

namespace ta {
    namespace graphics {
        class Renderer;

        class Drawable {
        public:
            virtual ~Drawable() {};
            virtual void draw(ta::graphics::Renderer& renderer, bool is2d = false) = 0;
        };
    } /* graphics */
} /* ta */
