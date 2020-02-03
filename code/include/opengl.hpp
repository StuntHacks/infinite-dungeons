#ifdef __SWITCH__
    #include <EGL/egl.h>
    #include <EGL/eglext.h>
    #include <glad/glad.h>
#else
    #ifdef __PC__
        #include <GLFW/glfw3.h>
    #endif
#endif

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
