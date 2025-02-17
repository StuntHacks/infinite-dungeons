#pragma once

#include <functional>
#include <map>
#include <vector>
#include "opengl.hpp"

#include "Color.hpp"
#include "ShaderProgram.hpp"
#include "common/Singleton.hpp"

namespace id {
    class Application;

    /**
     * @brief Contains anything graphics-related
     */
    namespace graphics {
        class Color;
        class Drawable;

        class Renderer: public id::Singleton<Renderer> {
        friend class id::Singleton<Renderer>;
        friend class id::Application;
        public:
            virtual ~Renderer();

            virtual void setClearColor(id::graphics::Color color);
            id::graphics::Color getClearColor();

            virtual void draw2d(id::graphics::Drawable& drawable);
            virtual void draw3d(id::graphics::Drawable& drawable);
            virtual void clear();
            virtual void clear2d();
            virtual void clear3d();

            /**
             * @brief Renders the current drawstacks
             * @param clearScreen Whether to clear the screen from the last frame
             */
            virtual void render(bool clearScreen = true);

            static void prepare();

            bool addShader(const id::graphics::ShaderProgram& program, const std::string& name, bool overwrite = false);
            bool removeShader(const std::string& name);
            void clearShaders();
            id::graphics::ShaderProgram& getShader(const std::string& name);
            bool useShader(const std::string& name);
            id::graphics::ShaderProgram& getDefaultShader();
            bool useDefaultShader();
            const std::string& getCurrentShaderName() const;
            id::graphics::ShaderProgram& getCurrentShader();

            bool addDrawHook(const std::string& name, std::function<void(id::graphics::Renderer&)> callback);
            bool removeDrawHook(const std::string& name);

            static glm::mat4 getOrthoProjection();

            #ifdef __PC__
            GLFWwindow& getGLFWWindow() const;
            #endif

        private:
            Renderer();
            /* data */
            std::string m_currentShader;
            id::graphics::Color m_clearColor;
            std::vector<id::graphics::Drawable*> m_drawStack2d, m_drawStack3d;
            id::graphics::ShaderProgram m_defaultShader;
            std::map<std::string, id::graphics::ShaderProgram> m_shaders;

            std::map<std::string, std::function<void(id::graphics::Renderer&)>> m_drawHooks;

            #ifdef __SWITCH__
                EGLDisplay m_display;
                EGLContext m_context;
                EGLSurface m_surface;
            #else
                #ifdef __PC__
                    GLFWwindow* m_window;
                #endif
            #endif
        };
    } /* graphics */
} /* id */
