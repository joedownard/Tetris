#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Shader.h"

struct tetrisState {
    glm::vec3 translationVector;
};

void process_input(GLFWwindow *window, struct tetrisState *tetrisState );
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader basicShader("/Users/joedownard/CLionProjects/Tetris/shaders/vertex.glsl", "/Users/joedownard/CLionProjects/Tetris/shaders/fragment.glsl");

    float vertices[] = {
            0.5f,  0.75f, 0.0f,  // top right
            0.25f, 0.75f, 0.0f, // top left
            0.25f, 0.25f, 0.0f,  // bottom left
            0.5f, 0.25f, 0.0f,  // bottom right
            0.75f,  0.25f, 0.0f,  // bottom right right
            0.75f,  0.5f, 0.0f,   // middle right right
            0.25f, 0.5f, 0.0f // middle left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,   // first triangle
            2, 3, 0,    // second triangle
            2, 4, 5,
            5, 6, 4
    };

    tetrisState tetrisState{};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        process_input(window, &tetrisState);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, tetrisState.translationVector);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        basicShader.use();
        basicShader.setMatrix4("transform", trans);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window, struct tetrisState *tetrisState) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        tetrisState->translationVector.y += 0.1f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        tetrisState->translationVector.y -= 0.1f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        tetrisState->translationVector.x += 0.1f;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        tetrisState->translationVector.x -= 0.1f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
