/**
 * @file common/graphics/Drawable.hpp
 * @brief Defines the Drawable base-class
 */
#pragma once

namespace id {
    namespace graphics {
        class Renderer;

        /**
         * @brief The base class for all drawable classes.
         *
         * To create your own drawable class, create a child class of this one and implement the draw()-method.
         */
        class Drawable {
        public:
            /**
             * @brief Destructor
             */
            virtual ~Drawable() {};

            /**
             * @brief Draws the drawable object
             * @param renderer The Renderer-instance to use
             * @param is2d     Whether the current rendering-process is done in 2D
             *
             * Implement this function in your own class to draw stuff on the screen using OpenGL-functions.
             */
            virtual void draw(id::graphics::Renderer& renderer, bool is2d = false) = 0;
        };
    } /* graphics */
} /* id */
