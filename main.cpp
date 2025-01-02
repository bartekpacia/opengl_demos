#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, const int key, int scancode, const int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Vertices coordinates
  const GLfloat vertices[] = {
      -0.5f, -0.5f * std::sqrt(3.0f) / 3, 0.0f, // Lower left corner
      0.5f, -0.5f * std::sqrt(3.0f) / 3, 0.0f, // Lower right corner
      0.0f, 0.5f * std::sqrt(3.0f) * 2 / 3, 0.0f, // Upper corner
      -0.5f / 2, 0.5f * std::sqrt(3.0f) / 6, 0.0f, // Inner left
      0.5f / 2, 0.5f * std::sqrt(3.0f) / 6, 0.0f, // Inner right
      0.0f, -0.5f * std::sqrt(3.0f) / 3, 0.0f, // Inner down
  };

  const GLuint indices[] = {
      0, 3, 5, // Lower left triangle
      3, 2, 4, // Lower right triangle
      5, 4, 1, // Upper triangle
  };

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

  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  const GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLuint VAO, VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}