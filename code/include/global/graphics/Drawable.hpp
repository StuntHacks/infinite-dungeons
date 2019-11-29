#pragma once

namespace ta {
    namespace graphics {
        class Renderer;

        class Drawable {
        public:
            virtual ~Drawable() {};
            virtual void draw(ta::graphics::Renderer& renderer, bool force2d = false) = 0;
        private:
            /* data */
        };
    } /* graphics */
} /* ta */
