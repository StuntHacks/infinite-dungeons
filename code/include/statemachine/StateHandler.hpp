#pragma once
#include <vector>
#include "switch/switch.hpp"
#include "common/graphics/graphics.hpp"

namespace id {
    class GameState;

    class StateHandler {
    public:
        virtual ~StateHandler();

        void change(id::GameState& t_state);
        void push(id::GameState& t_state);
        void pop();
        void update(id::graphics::Renderer& renderer);

    private:
        /* data */
        std::vector<id::GameState*> m_states;
    };
} /* id */
