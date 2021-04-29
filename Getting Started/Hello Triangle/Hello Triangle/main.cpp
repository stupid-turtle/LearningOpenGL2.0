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
    // 初始化GLFW
    glfwInit();
    // 设定OpenGL的版本号为 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 次版本号
    // 使用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 设定窗口的宽、高、标题（剩下两个参数暂时不管）
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

    // 从GLFW中获取视口的维度
    glViewport(0, 0, 800, 600);

    // 当窗口大小改变时调用函数
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

    // 顶点缓冲对象(Vertex Buffer Objects, VBO)
    // 缓冲ID为1
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

    // glBufferData: 专门用来把用户定义的数据复制到当前绑定缓冲的函数
    // target:  目标缓冲类型
    // size:    数据大小
    // data:    实际数据
    // usage:   显卡管理数据的形式
    //      - GL_STATIC_DRAW:   数据不会或几乎不会改变
    //      - GL_DYNAMIC_DRAW:  数据会被改变很多
    //      - GL_STREAM_DRAW:   数据每次绘制时都会改变
    

    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    GLfloat vertices[] = {
         0.2f,  0.2f, 0.0f,  // 左下
         0.8f,  0.2f, 0.0f,  // 右下
         0.8f,  0.6f, 0.0f,  // 右上
         0.2f,  0.6f, 0.0f,  // 左上
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

    // 创建一个着色器，顶点着色器的类型为GL_VERTEX_SHADER
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 创建一个着色器，片段着色器的类型为GL_FRAGMENT_SHADER
    GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

    // glShaderSource: 把着色器源代码附加到着色器上
    // shader:   要编译的着色器对象
    // count:    字符串数量
    // *string:  着色器源代码
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

    // 创建一个程序对象
    GLuint shaderProgram1 = glCreateProgram();
    // 把着色器代码附加到程序上，然后链接它们
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // 激活程序对象
    glUseProgram(shaderProgram1);
    glUseProgram(shaderProgram2);

    // 激活程序对象后，删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
    // 告诉OpenGL该如何解析顶点数据
    // index:        顶点属性的位置值
    // size:         顶点属性大小
    // type:         数据类型
    // normalized:   是否希望数据被标准化
    // stride:       步长
    // *pointer:     位置数据在缓冲中起始位置的偏移量
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 启用顶点数据，参数为顶点属性位置值
    // 顶点属性默认禁用
    //glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Game Loop  保证窗口不会刚打开就被关闭
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        // 清空颜色缓冲
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

        // 双缓冲
        glfwSwapBuffers(window);
        // 检查有没有触发事件
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    // 结束时释放资源
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