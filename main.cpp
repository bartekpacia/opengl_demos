#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "sample_01.cpp"
#include "sample_02.cpp"
#include "sample_03.cpp"

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, const int key, int scancode, const int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[]) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int major;
  int minor;
  int rev;
  glfwGetVersion(&major, &minor, &rev);
  std::cout << "OpenGL version: " << major << "." << minor << "." << rev << std::endl;

  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    std::cerr << "Failed to open GLFW window" << std::endl;
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  gladLoadGL();

  const GLubyte* vendor = glGetString(GL_VENDOR);
  std::cout << "Vendor: " << vendor << std::endl;
  const GLubyte* renderer = glGetString(GL_RENDERER);
  std::cout << "Renderer: " << renderer << std::endl;

  glViewport(0, 0, 640, 480);

  using namespace std::literals;
  if (argc == 0) {
    sample_01(window);
  } else if (argv[1] == "1"sv) {
    sample_01(window);
  } else if (argv[1] == "2"sv) {
    sample_02(window);
  } else if (argv[1] == "3"sv) {
    sample_03(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}