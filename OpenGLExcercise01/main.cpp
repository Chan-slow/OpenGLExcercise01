#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//float vertices[] = {
//    -0.5f, -0.5f, 0.0f,//1
//     0.5f, -0.5f, 0.0f,//2
//     0.0f,  0.5f, 0.0f,//3
//   //0.5f, -0.5f, 0.0f,
//   //0.0f,  0.5f, 0.0f,
//     0.8f,  0.8f, 0.0f //4
//    };                                                    
//
float vertices1[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
float vertices2[] = {
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
    0.8f,  0.8f, 0.0f 
};
unsigned int indices[] = {
    0,1,2,
    2,1,3
};

const char* vertexShaderSource =
"#version 330 core                                         \n   "
"layout(location = 0) in vec3 aPos;                        \n   "
"                                                          \n   "
"void main()                                               \n   "
"{                                                         \n   "
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);      \n   "
"}                                                         \n   ";

const char* fragmentShaderSource1 =
"#version 330 core                                  \n  "
"out vec4 FragColor;                                \n  "
"                                                   \n  "
"void main()                                        \n  "
"{                                                  \n  "
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);      \n  "
"}                                                  \n  ";

const char* fragmentShaderSource2 =
"#version 330 core                                  \n  "
"out vec4 FragColor;                                \n  "
"                                                   \n  "
"void main()                                        \n  "
"{                                                  \n  "
"    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);      \n  "
"}                                                  \n  ";

void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)//检测退出键esc是否被按下
    {
        glfwSetWindowShouldClose(window, true);//设定窗口为关闭状态
    }
}

int main() 
{

	
    glfwInit(); //调用glfwInit函数来初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //MAJOR主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//MINOR次版本为3，也就是使用的GL为3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//告诉GLFW我们使用的是核心模式(Core-profile)

    //开GLFW窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", nullptr, nullptr);
    if (!window)
    {
        printf("Open window failed.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//表明我们上下文将使用该窗口

    //初始化glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed.");
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);//设定窗口初始坐标和大小
    //glEnable(GL_CULL_FACE);//开启面剔除模式
    //glCullFace(GL_BACK);//剔除背面
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//选择绘制模式。这里使用线框

    //unsigned int VAO;//创建VAO
    //glGenVertexArrays(1, &VAO);//注册VAO的id，申请缓冲区，我们本可以使用数组形式创建多个VAO，此处暂时不需要，就创建了一个。
    //glBindVertexArray(VAO);
    //
    //unsigned int VBO;//创建VBO
    //glGenBuffers(1, &VBO);//注册VBO的id，申请缓冲区
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设定将具体哪个数据传送到缓冲区内

    unsigned int VAO[2],VBO[2];//创建
    glGenVertexArrays(2, VAO);//注册VAO的id，申请缓冲区
    glGenBuffers(2, VBO);//注册VBO的id，申请缓冲区
    
    glBindVertexArray(VAO[0]);//设置它为当前操作的VAO，之后我们所有关于顶点数据的设置（包括数据使用的VBO对象，顶点的属性设置的信息都会被存储在VAO之中）
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);//设置它为当前操作的VAO，之后我们所有关于顶点数据的设置（包括数据使用的VBO对象，顶点的属性设置的信息都会被存储在VAO之中）
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);//注册EBO缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定缓冲区
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glCompileShader(vertexShader);//编译shader

    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);//创建片元着色器
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glCompileShader(fragmentShader1);//编译shader

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);//创建片元着色器
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glCompileShader(fragmentShader2);//编译shader

    //组装顶点着色器和片元着色器
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    //把之前编译的Shader附加到程序对象上，然后用glLinkProgram连接他们
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);

    
    //Render Loop
    while (!glfwWindowShouldClose(window))//如果没检测到关闭该窗口则循环
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置清屏颜色
        glClear(GL_COLOR_BUFFER_BIT);//指定清空哪个buffer，这里选择的是颜色缓冲区。

        //glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用索引缓冲区的索引值进行绘制。

        glfwSwapBuffers(window);       //交换前后缓冲器
        glfwPollEvents();       //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
    }

    glfwTerminate();//正确释放/删除之前的分配的所有资源
	
	return 0;
}