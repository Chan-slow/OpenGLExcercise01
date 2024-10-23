#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };                                                    

const char* vertexShaderSource =
"#version 330 core                                         \n   "
"layout(location = 0) in vec3 aPos;                        \n   "
"                                                          \n   "
"void main()                                               \n   "
"{                                                         \n   "
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);      \n   "
"}                                                         \n   ";

const char* fragmentShaderSource =
"#version 330 core                                  \n  "
"out vec4 FragColor;                                \n  "
"                                                   \n  "
"void main()                                        \n  "
"{                                                  \n  "
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);      \n  "
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


    unsigned int VAO;//创建VAO
    glGenVertexArrays(1, &VAO);//注册VAO的id，申请缓冲区，我们本可以使用数组形式创建多个VAO，此处暂时不需要，就创建了一个。
    glBindVertexArray(VAO);

    unsigned int VBO;//创建VBO
    glGenBuffers(1, &VBO);//注册VBO的id，申请缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设定将具体哪个数据传送到缓冲区内

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glCompileShader(vertexShader);//编译shader

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建片元着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glCompileShader(fragmentShader);//编译shader

    //组装顶点着色器和片元着色器
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //把之前编译的Shader附加到程序对象上，然后用glLinkProgram连接他们
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告知VAO怎么解析VBO的数据
    /*
	index：第几个属性，从0开始取，0，1，2，顺序自己定义，例如顶点位置，纹理，法线

    这里只有顶点位置，也只能讨论顶点位置，所以为0

    size：一个顶点所有数据的个数，这里每个顶点又两个浮点数属性值，所以是2

    type：顶点描述数据的类型，这里position数组中的数据全部为float，所以是GL_FLOAT

    normalized：是否需要显卡帮忙把数据归一化到-1到+1区间，这里不需要，所以设置GL_FALSE

    stride：一个顶点占有的总的字节数，这里为两个float，所以是sizeof(float)*2

    pointer：当前指针指向的vertex内部的偏离字节数，可以唯一的标识顶点某个属性的偏移量

    这里是指向第一个属性，顶点坐标，偏移量为0

    */
    glEnableVertexAttribArray(0);//启用顶点属性数组
    //Render Loop
    while (!glfwWindowShouldClose(window))//如果没检测到关闭该窗口则循环
    {
        processInput(window);

        glClearColor(0.5f, 0.3f, 0.4f, 1.0f);//设置清屏颜色
        glClear(GL_COLOR_BUFFER_BIT);//指定清空哪个buffer，这里选择的是颜色缓冲区。

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);       //交换前后缓冲器
        glfwPollEvents();       //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
    }

    glfwTerminate();//正确释放/删除之前的分配的所有资源
	
	return 0;
}