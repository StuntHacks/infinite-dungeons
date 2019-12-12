#pragma once

#include <vector>
#include "global/graphics/Vertex.hpp"
#include "global/graphics/drawables/menu/TextBox.hpp"

namespace ta {
    namespace menu {
        class TransparentTextBox: public TextBox {
        public:
            static ta::menu::TransparentTextBox& getInstance();
            virtual ~TransparentTextBox();
            virtual void draw(ta::graphics::Renderer& renderer, bool);

        protected:
            TransparentTextBox();
        private:
            /* data */
            std::vector<ta::graphics::Vertex> m_vertices;
            unsigned int m_vao, m_vbo;
        };
    } /* menu */
} /* ta */
