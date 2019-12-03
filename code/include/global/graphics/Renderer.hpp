#pragma once

#include <vector>
#include <map>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <glad/glad.h>

#include "Color.hpp"
#include "ShaderProgram.hpp"

namespace ta {
    namespace graphics {
        class Color;
        class Drawable;

        class Renderer {
        public:
            Renderer(bool force2d = false);
            virtual ~Renderer();

            void force2d(bool force2d) { m_force2d = force2d; }
            bool is2dForced() { return m_force2d; }

            virtual void setClearColor(ta::graphics::Color color);
            ta::graphics::Color getClearColor();

            virtual void draw2d(ta::graphics::Drawable& drawable);
            virtual void draw3d(ta::graphics::Drawable& drawable);
            virtual void clear();
            virtual void clear2d();
            virtual void clear3d();
            virtual void render(bool clearScreen = true);

            static void prepare();

            bool addShader(const ta::graphics::ShaderProgram& program, const std::string& name, bool overwrite = false);
            bool removeShader(const std::string& name);
            void clearShaders();
            ta::graphics::ShaderProgram& getShader(const std::string& name);
            bool useShader(const std::string& name);
            ta::graphics::ShaderProgram& getDefaultShader();
            bool useDefaultShader();
            const std::string& getCurrentShaderName() const;
            ta::graphics::ShaderProgram& getCurrentShader();

        private:
            /* data */
            bool m_force2d;
            std::string m_currentShader;
            ta::graphics::Color m_clearColor;
            std::vector<ta::graphics::Drawable*> m_drawStack2d, m_drawStack3d;
            ta::graphics::ShaderProgram m_defaultShader;
            std::map<std::string, ta::graphics::ShaderProgram> m_shaders;

            static EGLDisplay m_display;
            static EGLContext m_context;
            static EGLSurface m_surface;
        };
    } /* graphics */
} /* ta */
