#pragma once
#include "StateHandler.hpp"
#include "global/graphics/graphics.hpp"

namespace ta {
    class GameState {
    public:
        /**
         * @brief Gets called on destruction
         */
        virtual void cleanup() = 0;

        /**
         * @brief Gets called on entry
         */
        virtual void onEntry() = 0;

        /**
         * @brief Gets called on exit
         */
        virtual void onExit() = 0;

        virtual void update(ta::StateHandler& handler, ta::graphics::Renderer& renderer) = 0;
    };
} /* ta */
