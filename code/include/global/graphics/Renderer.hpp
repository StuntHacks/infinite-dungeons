#pragma once

#include <functional>
#include <map>
#include <vector>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <glad/glad.h>

#include "Color.hpp"
#include "ShaderProgram.hpp"

namespace id {
    namespace graphics {
        class Color;
        class Drawable;

        class Renderer {
        public:
            Renderer(bool force2d = false);
            virtual ~Renderer();

            void force2d(bool force2d) { m_force2d = force2d; }
            bool is2dForced() { return m_force2d; }

            virtual void setClearColor(id::graphics::Color color);
            id::graphics::Color getClearColor();

            virtual void draw2d(id::graphics::Drawable& drawable);
            virtual void draw3d(id::graphics::Drawable& drawable);
            virtual void clear();
            virtual void clear2d();
            virtual void clear3d();
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

            static bool addDrawHook(const std::string& name, std::function<void(id::graphics::Renderer&)> callback);
            static bool removeDrawHook(const std::string& name);

            static inline glm::mat4 getOrthoProjection() {
                return glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f);
            }

        private:
            /* data */
            bool m_force2d;
            std::string m_currentShader;
            id::graphics::Color m_clearColor;
            std::vector<id::graphics::Drawable*> m_drawStack2d, m_drawStack3d;
            id::graphics::ShaderProgram m_defaultShader;
            std::map<std::string, id::graphics::ShaderProgram> m_shaders;

            static inline std::map<std::string, std::function<void(id::graphics::Renderer&)>> m_drawHooks;

            static EGLDisplay m_display;
            static EGLContext m_context;
            static EGLSurface m_surface;
        };
    } /* graphics */
} /* id */
