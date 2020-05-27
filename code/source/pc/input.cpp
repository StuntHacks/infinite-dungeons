#include "pc/input.hpp"
#include "opengl.hpp"

namespace id {
    namespace pc {
        void Input::scanInput() {
            glfwPollEvents();
        }
    } /* pc */
} /* id */
