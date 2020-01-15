#pragma once

#include <vector>
#include "global/graphics/Vertex.hpp"
#include "global/graphics/drawables/menu/TextBox.hpp"

namespace id {
    namespace menu {
        class TransparentTextBox: public TextBox {
        public:
            static id::menu::TransparentTextBox& getInstance();
            virtual ~TransparentTextBox();
            virtual void draw(id::graphics::Renderer& renderer, bool);

        protected:
            TransparentTextBox();
        private:
            /* data */
            std::vector<id::graphics::Vertex> m_vertices;
            unsigned int m_vao, m_vbo;
        };
    } /* menu */
} /* id */
