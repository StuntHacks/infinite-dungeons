#include "statemachine/StateHandler.hpp"
#include "statemachine/GameState.hpp"

namespace id {
    StateHandler::~StateHandler() {
        while (!m_states.empty()) {
            m_states.back()->cleanup();
            m_states.pop_back();
        }
    }

    void StateHandler::change(id::GameState& state) {
        if (!m_states.empty()) {
            m_states.back()->onExit();
            m_states.back() = &state;
            m_states.back()->onEntry();
        } else {
            push(state);
        }
    }

    void StateHandler::push(id::GameState& state) {
        if (!m_states.empty()) m_states.back()->onExit();
        m_states.push_back(&state);
        m_states.back()->onEntry();
    }

    void StateHandler::pop() {
        m_states.back()->onExit();
        m_states.pop_back();
        if (!m_states.empty()) m_states.back()->onEntry();
    }

    void StateHandler::update(id::graphics::Renderer& renderer) {
        m_states.back()->update(*this, renderer);
    }
} /* id */
