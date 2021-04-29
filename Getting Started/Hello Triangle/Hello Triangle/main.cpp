// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void check_shader_compile_success(GLuint shader);
void check_program_link_success(GLuint program);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\nvoid main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"\nvoid main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"\nvoid main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

    GLfloat triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
    };

    GLfloat firstTriangle[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
    };
       
    GLfloat secondTriangle[] = {
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
    };

    GLuint VAOs[2];
    glGenVertexArrays(2, VAOs);

    // ���㻺�����(Vertex Buffer Objects, VBO)
    // ����IDΪ1
    GLuint VBOs[2];
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    // glBufferData: ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ���
    // target:  Ŀ�껺������
    // size:    ���ݴ�С
    // data:    ʵ������
    // usage:   �Կ��������ݵ���ʽ
    //      - GL_STATIC_DRAW:   ���ݲ���򼸺�����ı�
    //      - GL_DYNAMIC_DRAW:  ���ݻᱻ�ı�ܶ�
    //      - GL_STREAM_DRAW:   ����ÿ�λ���ʱ����ı�
    

    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    GLfloat vertices[] = {
         0.2f,  0.2f, 0.0f,  // ����
         0.8f,  0.2f, 0.0f,  // ����
         0.8f,  0.6f, 0.0f,  // ����
         0.2f,  0.6f, 0.0f,  // ����
        -0.8f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
        -0.4f,  0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6
    };

    //GLuint EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ����һ����ɫ����������ɫ��������ΪGL_VERTEX_SHADER
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // ����һ����ɫ����Ƭ����ɫ��������ΪGL_FRAGMENT_SHADER
    GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

    // glShaderSource: ����ɫ��Դ���븽�ӵ���ɫ����
    // shader:   Ҫ�������ɫ������
    // count:    �ַ�������
    // *string:  ��ɫ��Դ����
    // *length:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compile_success(vertexShader);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    check_shader_compile_success(fragmentShader1);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    check_shader_compile_success(fragmentShader2);

    // ����һ���������
    GLuint shaderProgram1 = glCreateProgram();
    // ����ɫ�����븽�ӵ������ϣ�Ȼ����������
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // ����������
    glUseProgram(shaderProgram1);
    glUseProgram(shaderProgram2);

    // �����������ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
    // ����OpenGL����ν�����������
    // index:        �������Ե�λ��ֵ
    // size:         �������Դ�С
    // type:         ��������
    // normalized:   �Ƿ�ϣ�����ݱ���׼��
    // stride:       ����
    // *pointer:     λ�������ڻ�������ʼλ�õ�ƫ����
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // ���ö������ݣ�����Ϊ��������λ��ֵ
    // ��������Ĭ�Ͻ���
    //glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Game Loop  ��֤���ڲ���մ򿪾ͱ��ر�
    while (!glfwWindowShouldClose(window))
    {
        // ����
        processInput(window);

        // ��Ⱦ
        // �����ɫ����
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        // ˫����
        glfwSwapBuffers(window);
        // �����û�д����¼�
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
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
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}


void check_shader_compile_success(GLuint shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void check_program_link_success(GLuint program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}