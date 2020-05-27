#pragma once

#include <vector>
#include "common/Singleton.hpp"
#include "common/graphics/Vertex.hpp"
#include "common/graphics/drawables/menu/TextBox.hpp"

namespace id {
    namespace menu {
        class TransparentTextBox: public TextBox, public id::Singleton<TransparentTextBox> {
        friend class id::Singleton<TransparentTextBox>;
        public:
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
