#pragma once

namespace ta {
    namespace graphics {
        /**
         * @brief Can be used to render something without directly displaying it on screen
         */
        class RenderTarget {
        public:
            /**
             * @brief Creates the rendertarget
             */
            RenderTarget();

            /**
             * @brief Destructs the rendertarget
             */
            ~RenderTarget();

            /**
             * @brief Binds the rendertarget
             *
             * This causes all rendering to be redirected to this rendertarget
             */
            void bind();

        private:
            /* data */
            unsigned int m_framebuffer;
        };
    } /* graphics */
} /* ta */
