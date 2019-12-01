#pragma once

namespace ta {
    namespace graphics {
        class Renderer;

        class Drawable {
        public:
            virtual ~Drawable() {};
            virtual void draw(ta::graphics::Renderer& renderer, bool is2d = false) = 0;

        protected:
            virtual float normalize(float position, float dimension, bool invert = false) {
                // shift coordinate center to the positive by 50% of the dimension
                float dimensionHalfed = dimension / 2;
                float positionShifted = position - dimensionHalfed;

                // and normalize it to [-1;1]
                float normalized = positionShifted / dimensionHalfed;

                return normalized * (invert ? 1 : 1);
            }
        };
    } /* graphics */
} /* ta */
