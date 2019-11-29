#include "statemachine/StateHandler.hpp"
#include "statemachine/GameState.hpp"

namespace ta {
    StateHandler::~StateHandler() {
        while (!m_states.empty()) {
            m_states.back()->cleanup();
            m_states.pop_back();
        }
    }

    void StateHandler::change(ta::GameState& t_state) {
        if (!m_states.empty()) {
            m_states.back()->onExit();
            m_states.back() = &t_state;
            m_states.back()->onEntry();
        } else {
            push(t_state);
        }
    }

    void StateHandler::push(ta::GameState& t_state) {
        if (!m_states.empty()) m_states.back()->onExit();
        m_states.push_back(&t_state);
        m_states.back()->onEntry();
    }

    void StateHandler::pop() {
        m_states.back()->onExit();
        m_states.pop_back();
        if (!m_states.empty()) m_states.back()->onEntry();
    }

    void StateHandler::update(ta::graphics::Renderer& renderer) {
        m_states.back()->update(*this, renderer);
    }
} /* ta */
