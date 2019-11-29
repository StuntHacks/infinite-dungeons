#pragma once
#include <vector>
#include "switch/switch.hpp"
#include "global/graphics/graphics.hpp"

namespace ta {
    class GameState;

    class StateHandler {
    public:
        virtual ~StateHandler();

        void change(ta::GameState& t_state);
        void push(ta::GameState& t_state);
        void pop();
        void update(ta::graphics::Renderer& renderer);

    private:
        /* data */
        std::vector<ta::GameState*> m_states;
    };
} /* ta */
