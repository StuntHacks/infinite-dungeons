#pragma once
#include "StateHandler.hpp"
#include "global/Singleton.hpp"
#include "global/graphics/graphics.hpp"

namespace id {
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

        virtual void update(id::StateHandler& handler, id::graphics::Renderer& renderer) = 0;
    };
} /* id */
