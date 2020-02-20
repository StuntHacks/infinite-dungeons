#include "common/graphics/Renderer.hpp"
#include "common/graphics/Drawable.hpp"
#include "common/graphics/Shader.hpp"
#include "common/graphics/ShaderProgram.hpp"
#include "common/graphics/Vertex.hpp"
#include "common/menu/TextBoxManager.hpp"
#include "common/Console.hpp"
#include "common/InputManager.hpp"
#include "opengl.hpp"

#include <string>

#ifdef __SWITCH__
    #include <switch.h>
#endif

namespace id {
    namespace graphics {
        Renderer::~Renderer() {
            clear();

            #ifdef __SWITCH__
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

            #else
                #ifdef __PC__
                    glfwTerminate();
                #endif
            #endif
        }

        void Renderer::draw2d(id::graphics::Drawable& drawable) {
            m_drawStack2d.push_back(&drawable);
        }

        void Renderer::draw3d(id::graphics::Drawable& drawable) {
            m_drawStack3d.push_back(&drawable);
        }

        void Renderer::setClearColor(id::graphics::Color color) {
            m_clearColor = color;
            glClearColor(color.getRed(), color.getGreen(), color.getBlue(), 1.0f);
        }

        id::graphics::Color Renderer::getClearColor() {
            return m_clearColor;
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
            #ifdef __SWITCH__
                if (m_context) {
            #else
            #ifdef __PC__
                if (m_window) {
            #endif
            #endif
                id::menu::TextBoxManager::getInstance().draw(*this);

                for (auto& callback: m_drawHooks) {
                    callback.second(*this);
                }

                if (clearScreen) {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                }

                // 3D
                glCullFace(GL_BACK);
                glEnable(GL_CULL_FACE);
                glEnable(GL_DEPTH_TEST);
                glDisable(GL_BLEND);
                glm::mat4 view = glm::mat4(1.0f);
                getCurrentShader().setMatrix4("projection", view);

                for (auto& drawable: m_drawStack3d) {
                    drawable->draw(*this, false);
                }

                // 2D
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                glDisable(GL_CULL_FACE);
                glDisable(GL_DEPTH_TEST);

                glm::mat4 projectionMatrix = getOrthoProjection();
                getCurrentShader().setMatrix4("projection", projectionMatrix);

                for (auto& drawable: m_drawStack2d) {
                    drawable->draw(*this, true);
                }

                if (clearScreen) {
                    clear();
                }

                #ifdef __SWITCH__
                    eglSwapBuffers(m_display, m_surface);
                #else
                    #ifdef __PC__
                        if (!glfwWindowShouldClose(m_window)) {
                            glfwSwapBuffers(m_window);
                            glfwPollEvents();
                        }
                    #endif
                #endif
            }
        }

        void Renderer::prepare() {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(id::graphics::Vertex), (void*) offsetof(id::graphics::Vertex, position));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(id::graphics::Vertex), (void*) offsetof(id::graphics::Vertex, color));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(id::graphics::Vertex), (void*) offsetof(id::graphics::Vertex, texCoords));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(id::graphics::Vertex), (void*) offsetof(id::graphics::Vertex, normals));
            glEnableVertexAttribArray(3);
        }

        bool Renderer::addShader(const id::graphics::ShaderProgram& program, const std::string& name, bool overwrite) {
            auto search = m_shaders.find(name);
            if (search == m_shaders.end()) {
                m_shaders[name] = program;
                return true;
            }

            if (overwrite) {
                m_shaders.erase(name);
                m_shaders[name] = program;
                return true;
            }

            return false;
        }

        bool Renderer::removeShader(const std::string& name) {
            if (name == m_currentShader) {
                m_defaultShader.use();
            }

            auto search = m_shaders.find(name);
            if (search != m_shaders.end()) {
                m_shaders.erase(name);
                return true;
            }

            return false;
        }

        void Renderer::clearShaders() {
            m_defaultShader.use();
            m_shaders.clear();
        }

        id::graphics::ShaderProgram& Renderer::getShader(const std::string& name) {
            return m_shaders[name];
        }

        bool Renderer::useShader(const std::string& name) {
            auto search = m_shaders.find(name);
            if (search != m_shaders.end()) {
                m_currentShader = name;
                return m_shaders[name].use();
            }

            return false;
        }

        id::graphics::ShaderProgram& Renderer::getDefaultShader() {
            return m_defaultShader;
        }

        bool Renderer::useDefaultShader() {
            m_currentShader = "";
            return m_defaultShader.use();
        }

        const std::string& Renderer::getCurrentShaderName() const {
            return m_currentShader;
        }

        id::graphics::ShaderProgram& Renderer::getCurrentShader() {
            return m_currentShader != "" ? m_shaders[m_currentShader] : m_defaultShader;
        }

        bool Renderer::addDrawHook(const std::string& name, std::function<void(id::graphics::Renderer&)> callback) {
            auto search = m_drawHooks.find(name);
            if (search == m_drawHooks.end()) {
                m_drawHooks[name] = callback;
                return true;
            }

            return false;
        }

        bool Renderer::removeDrawHook(const std::string& name) {
            auto search = m_drawHooks.find(name);
            if (search != m_drawHooks.end()) {
                m_drawHooks.erase(name);
                return true;
            }

            return false;
        }

        glm::mat4 Renderer::getOrthoProjection() {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            return glm::ortho(static_cast<float>(viewport[0]), static_cast<float>(viewport[2]), static_cast<float>(viewport[3]), static_cast<float>(viewport[1]));
        }

        // protected methods
        Renderer::Renderer() :
        m_currentShader(""),
        m_clearColor(0, 0, 0, 0)
        {
            #ifdef __SWITCH__
                if (!m_context) {
            #else
            #ifdef __PC__
                if (!m_window) {
            #endif
            #endif
                id::Console::log("Initializing screen...", "Renderer.cpp:" + std::to_string(__LINE__), id::Console::White);

                #ifdef __SWITCH__
                    // Connect to the EGL default display
                    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

                    if (!m_display) {
                        id::Console::error("EGL: Could not connect to display! error: " + eglGetError(), "Renderer.cpp:" + std::to_string(__LINE__), true);
                        return;
                    }

                    id::Console::success("EGL: Connected to display successfully!", "Renderer.cpp:" + std::to_string(__LINE__));

                    // Initialize the EGL display connection
                    eglInitialize(m_display, nullptr, nullptr);

                    // Select OpenGL (Core) as the desired graphics API
                    if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
                        id::Console::error("EGL: Could not bind OpenGL-API! error: " + eglGetError(), "Renderer.cpp:" + std::to_string(__LINE__), true);
                        eglTerminate(m_display);
                        m_display = nullptr;
                        return;
                    }

                    id::Console::success("EGL: Bound OpenGL-API successfully!", "Renderer.cpp:" + std::to_string(__LINE__));

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
                        id::Console::error("EGL: No config found! error: " + eglGetError(), "Renderer.cpp:" + std::to_string(__LINE__), true);
                        eglTerminate(m_display);
                        m_display = nullptr;
                        return;
                    }

                    id::Console::log("EGL: Configurations loaded", "Renderer.cpp:" + std::to_string(__LINE__), id::Console::White);

                    // Create an EGL window surface
                    m_surface = eglCreateWindowSurface(m_display, config, nwindowGetDefault(), nullptr);

                    if (!m_surface) {
                        id::Console::error("EGL: Surface creation failed! error: " + eglGetError(), "Renderer.cpp:" + std::to_string(__LINE__), true);
                        eglTerminate(m_display);
                        m_display = nullptr;
                        return;
                    }

                    id::Console::success("EGL: Surface created successfully!", "Renderer.cpp:" + std::to_string(__LINE__));

                    // Create an EGL rendering context
                    static const EGLint contextAttributeList[] = {
                        EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
                        EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
                        EGL_CONTEXT_MINOR_VERSION_KHR, 3,
                        EGL_NONE
                    };

                    m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttributeList);

                    if (!m_context) {
                        id::Console::error("EGL: Context creation failed! error: " + eglGetError(), "Renderer.cpp:" + std::to_string(__LINE__), true);
                        eglDestroySurface(m_display, m_surface);
                        m_surface = nullptr;
                        eglTerminate(m_display);
                        m_display = nullptr;
                        return;
                    }

                    id::Console::success("EGL: Context created successfully!", "Renderer.cpp:" + std::to_string(__LINE__));

                    // Connect the context to the surface
                    eglMakeCurrent(m_display, m_surface, m_surface, m_context);
                    gladLoadGL();
                #else
                    #ifdef __PC__
                        glfwInit();
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                        #ifdef __OSX__
                            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                        #endif

                        m_window = glfwCreateWindow(1920, 1080, "Infinite Dungeons", glfwGetPrimaryMonitor(), nullptr);

                        if (!m_window) {
                            id::Console::error("Failed to create GLFW window", "Renderer.cpp:" + std::to_string(__LINE__), true);
                            glfwTerminate();
                            return;
                        }

                        id::Console::success("Successfully created GLFW window", "Renderer.cpp:" + std::to_string(__LINE__));

                        glfwMakeContextCurrent(m_window);

                        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                            id::Console::error("Failed to initialize GLAD", "Renderer.cpp:" + std::to_string(__LINE__), true);
                            glfwTerminate();
                            return;
                        }

                        id::Console::success("Successfully initialized GLAD", "Renderer.cpp:" + std::to_string(__LINE__));

                        glfwSetKeyCallback(m_window, id::InputManager::_keyCallbackPrivate);

                        glViewport(0, 0, 1920, 1080);
                        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); });
                    #endif
                #endif

                glClearColor(m_clearColor.getRed(), m_clearColor.getGreen(), m_clearColor.getBlue(), 1.0f);

                // default shaders
                const std::string vertexShaderSource = R"text(
                    #version 430 core
                    layout (location = 0) in vec3 aPos;
                    layout (location = 1) in vec4 aColor;
                    layout (location = 2) in vec2 aTexCoords;
                    layout (location = 3) in vec3 aNormals;

                    uniform mat4 transform;
                    uniform mat4 projection;

                    out vec4 ourColor;

                    void main()
                    {
                        gl_Position = projection * transform * vec4(aPos.xyz, 1.0);
                        ourColor = aColor;
                    }
                )text";

                const std::string fragmentShaderSource = R"text(
                    #version 430 core
                    in vec4 ourColor;
                    out vec4 fragColor;

                    void main()
                    {
                        fragColor = ourColor;
                    }
                )text";

                id::graphics::Shader vsh, fsh;
                vsh.compile(vertexShaderSource, id::graphics::Shader::Type::Vertex);
                fsh.compile(fragmentShaderSource, id::graphics::Shader::Type::Fragment);

                if (!m_defaultShader.attach(vsh).attach(fsh).link()) {
                    // this should never happen
                    id::Console::error("Failed to link default shader", "Renderer.cpp:" + std::to_string(__LINE__), true);

                    #ifdef __SWITCH__
                        eglDestroyContext(m_display, m_context);
                        m_context = nullptr;

                        eglDestroySurface(m_display, m_surface);
                        m_surface = nullptr;

                        eglTerminate(m_display);
                        m_display = nullptr;
                    #else
                        #ifdef __PC__
                            glfwTerminate();
                        #endif
                    #endif
                    return;
                }

                id::Console::log("Default shader linked", "Renderer.cpp:" + std::to_string(__LINE__), id::Console::White);

                if (!m_defaultShader.use()) {
                    id::Console::error("Failed to use default shader", "Renderer.cpp:" + std::to_string(__LINE__), true);

                    #ifdef __SWITCH__
                        eglDestroyContext(m_display, m_context);
                        m_context = nullptr;

                        eglDestroySurface(m_display, m_surface);
                        m_surface = nullptr;

                        eglTerminate(m_display);
                        m_display = nullptr;
                    #else
                        #ifdef __PC__
                            glfwTerminate();
                        #endif
                    #endif
                    return;
                }

                id::Console::success("EGL: Default shader applied successfully!", "Renderer.cpp:" + std::to_string(__LINE__));

                m_defaultShader.setMatrix4("transform", glm::mat4(1.0f));

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
        }
    } /* graphics */
} /* id */
