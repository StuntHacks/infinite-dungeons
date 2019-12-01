#include "global/graphics/Renderer.hpp"
#include "global/graphics/Drawable.hpp"
#include "global/graphics/Shader.hpp"
#include "global/graphics/ShaderProgram.hpp"
#include "global/graphics/Vertex.hpp"
#include "global/Console.hpp"
#include "opengl.hpp"

#include <string>
#include <switch.h>

EGLDisplay ta::graphics::Renderer::m_display;
EGLContext ta::graphics::Renderer::m_context;
EGLSurface ta::graphics::Renderer::m_surface;

namespace ta {
    namespace graphics {
        Renderer::Renderer(bool force2d) :
        m_clearColor(0, 0, 0, 0) {
            if (!m_context) {
                ta::Console::log("Initializing screen...", "Renderer.cpp:19", ta::Console::White);

                // Connect to the EGL default display
                m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

                if (!m_display) {
                    ta::Console::error("EGL: Could not connect to display! error: " + eglGetError(), "Renderer.cpp:24", true);
                    return;
                }

                ta::Console::success("EGL: Connected to display successfully!", "Renderer.cpp:24");

                // Initialize the EGL display connection
                eglInitialize(m_display, nullptr, nullptr);

                // Select OpenGL (Core) as the desired graphics API
                if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
                    ta::Console::error("EGL: Could not bind OpenGL-API! error: " + eglGetError(), "Renderer.cpp:34", true);
                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::success("EGL: Bound OpenGL-API successfully!", "Renderer.cpp:34");

                // Get an appropriate EGL framebuffer configuration
                EGLConfig config;
                EGLint numConfigs;

                static const EGLint framebufferAttributeList[] = {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
                    EGL_RED_SIZE,     8,
                    EGL_GREEN_SIZE,   8,
                    EGL_BLUE_SIZE,    8,
                    EGL_ALPHA_SIZE,   8,
                    EGL_DEPTH_SIZE,   24,
                    EGL_STENCIL_SIZE, 8,
                    EGL_NONE
                };

                eglChooseConfig(m_display, framebufferAttributeList, &config, 1, &numConfigs);

                if (numConfigs == 0) {
                    ta::Console::error("EGL: No config found! error: " + eglGetError(), "Renderer.cpp:61", true);
                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::log("EGL: Configurations loaded", "Renderer.cpp:61", ta::Console::White);

                // Create an EGL window surface
                m_surface = eglCreateWindowSurface(m_display, config, nwindowGetDefault(), nullptr);

                if (!m_surface) {
                    ta::Console::error("EGL: Surface creation failed! error: " + eglGetError(), "Renderer.cpp:73", true);
                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::success("EGL: Surface created successfully!", "Renderer.cpp:73");

                // Create an EGL rendering context
                static const EGLint contextAttributeList[] = {
                    EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
                    EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
                    EGL_CONTEXT_MINOR_VERSION_KHR, 3,
                    EGL_NONE
                };

                m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttributeList);

                if (!m_context) {
                    ta::Console::error("EGL: Context creation failed! error: " + eglGetError(), "Renderer.cpp:92", true);
                    eglDestroySurface(m_display, m_surface);
                    m_surface = nullptr;
                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::success("EGL: Context created successfully!", "Renderer.cpp:92");

                // Connect the context to the surface
                eglMakeCurrent(m_display, m_surface, m_surface, m_context);
                gladLoadGL();

                glClearColor(m_clearColor.getRed(), m_clearColor.getGreen(), m_clearColor.getBlue(), 1.0f);

                // default shaders
                const std::string vertexShaderSource = R"text(
                    #version 330 core
                    layout (location = 0) in vec3 aPos;
                    layout (location = 1) in vec4 aColor;
                    layout (location = 2) in vec2 aTexCoords;
                    layout (location = 3) in vec3 aNormals;

                    uniform mat4 transform;
                    uniform mat4 projection;

                    out vec4 ourColor;

                    void main()
                    {
                        gl_Position = transform * projection * vec4(aPos.xyz, 1.0);
                        ourColor = aColor;
                    }
                )text";

                const std::string fragmentShaderSource = R"text(
                    #version 330 core
                    in vec4 ourColor;
                    out vec4 fragColor;

                    void main()
                    {
                        fragColor = ourColor;
                    }
                )text";

                ta::graphics::Shader vsh, fsh;
                vsh.compile(vertexShaderSource, ta::graphics::Shader::Type::Vertex);
                fsh.compile(fragmentShaderSource, ta::graphics::Shader::Type::Fragment);

                if (!m_defaultShader.attach(vsh).attach(fsh).link()) {
                    // this should never happen
                    ta::Console::error("Failed to link default shader", "Renderer.cpp:146", true);

                    eglDestroyContext(m_display, m_context);
                    m_context = nullptr;

                    eglDestroySurface(m_display, m_surface);
                    m_surface = nullptr;

                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::log("Default shader linked", "Renderer.cpp:146", ta::Console::White);

                if (!m_defaultShader.use()) {
                    ta::Console::error("Failed to use default shader", "Renderer.cpp:163", true);

                    eglDestroyContext(m_display, m_context);
                    m_context = nullptr;

                    eglDestroySurface(m_display, m_surface);
                    m_surface = nullptr;

                    eglTerminate(m_display);
                    m_display = nullptr;
                    return;
                }

                ta::Console::success("EGL: Default shader applied successfully!", "Renderer.cpp:163");

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                m_force2d = force2d;
            }
        }

        Renderer::~Renderer() {
            clear();

            if (m_display) {
                eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

                if (m_context) {
                    eglDestroyContext(m_display, m_context);
                    m_context = nullptr;
                }

                if (m_surface) {
                    eglDestroySurface(m_display, m_surface);
                    m_surface = nullptr;
                }

                eglTerminate(m_display);
                m_display = nullptr;
            }
        }

        void Renderer::draw2d(ta::graphics::Drawable& drawable) {
            m_drawStack2d.push_back(&drawable);
        }

        void Renderer::draw3d(ta::graphics::Drawable& drawable) {
            m_drawStack3d.push_back(&drawable);
        }

        void Renderer::setClearColor(ta::graphics::Color color) {
            m_clearColor = color;
            glClearColor(color.getRed(), color.getGreen(), color.getBlue(), 1.0f);
        }

        ta::graphics::Color Renderer::getClearColor() {
            return m_clearColor;
        }

        ta::graphics::ShaderProgram& Renderer::getDefaultShader() {
            return m_defaultShader;
        }

        void Renderer::clear() {
            clear2d();
            clear3d();
        }

        void Renderer::clear2d() {
            m_drawStack2d.clear();
        }

        void Renderer::clear3d() {
            m_drawStack3d.clear();
        }

        void Renderer::render(bool clearScreen) {
            if (m_context) {
                if (clearScreen) {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }

                // 3D
                if (!m_force2d) {
                    glCullFace(GL_BACK);
                    glEnable(GL_CULL_FACE);
                    glEnable(GL_DEPTH_TEST);
                    glDisable(GL_BLEND);
                    glm::mat4 view = glm::mat4(1.0f);
                    m_defaultShader.setMatrix4("projection", view);

                    for (auto& drawable: m_drawStack3d) {
                        drawable->draw(*this, false);
                    }
                }

                // 2D
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                glDisable(GL_CULL_FACE);
                glDisable(GL_DEPTH_TEST);

                glm::mat4 projectionMatrix = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f);
                m_defaultShader.setMatrix4("projection", projectionMatrix);

                if (m_force2d) {
                    for (auto& drawable: m_drawStack3d) {
                        drawable->draw(*this, true);
                    }
                }

                for (auto& drawable: m_drawStack2d) {
                    drawable->draw(*this, true);
                }

                if (clearScreen) {
                    clear();
                }

                eglSwapBuffers(m_display, m_surface);
            }
        }

        void Renderer::prepare() {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ta::graphics::Vertex), (void*) offsetof(ta::graphics::Vertex, position));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ta::graphics::Vertex), (void*) offsetof(ta::graphics::Vertex, color));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ta::graphics::Vertex), (void*) offsetof(ta::graphics::Vertex, texCoords));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ta::graphics::Vertex), (void*) offsetof(ta::graphics::Vertex, normals));
            glEnableVertexAttribArray(3);
        }
    } /* graphics */
} /* ta */
