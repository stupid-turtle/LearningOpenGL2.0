// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // ��ʼ��GLFW
    glfwInit();
    // �趨OpenGL�İ汾��Ϊ 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // ���汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // �ΰ汾��
    // ʹ�ú���ģʽ
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �趨���ڵĿ��ߡ����⣨ʣ������������ʱ���ܣ�
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Fail to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // ��GLFW�л�ȡ�ӿڵ�ά��
    glViewport(0, 0, 800, 600);

    // �����ڴ�С�ı�ʱ���ú���
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Game Loop  ��֤���ڲ���մ򿪾ͱ��ر�
    while (!glfwWindowShouldClose(window))
    {
        // ����
        processInput(window);

        // ��Ⱦ
        // �����ɫ����
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ˫����
        glfwSwapBuffers(window);
        // �����û�д����¼�
        glfwPollEvents();
    }

    // ����ʱ�ͷ���Դ
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}