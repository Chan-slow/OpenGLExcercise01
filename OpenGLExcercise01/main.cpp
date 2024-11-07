#include <iostream>
#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,//1
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//2
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,//3
     0.8f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f //4
    };                                                    

unsigned int indices[] = {
    0,1,2,
    2,1,3
};


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

    /*//初始化glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed.");
        glfwTerminate();
        return -1;
    }*/
    //初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);//设定窗口初始坐标和大小
    //glEnable(GL_CULL_FACE);//开启面剔除模式
    //glCullFace(GL_BACK);//剔除背面
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//选择绘制模式。这里使用线框
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//恢复默认绘制模式

    Shader* testShader = new Shader("Shader/vertexSource.txt", "Shader/fragmentSource.txt");

    unsigned int VAO;//创建VAO
    glGenVertexArrays(1, &VAO);//注册VAO的id，申请缓冲区，我们本可以使用数组形式创建多个VAO，此处暂时不需要，就创建了一个。
    glBindVertexArray(VAO);

    unsigned int VBO;//创建VBO
    glGenBuffers(1, &VBO);//注册VBO的id，申请缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设定将具体哪个数据传送到缓冲区内

    unsigned int EBO;
    glGenBuffers(1, &EBO);//注册EBO缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定缓冲区
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //unsigned int vertexShader;
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器,返回的是一个创建完的着色器的id。
    //glShaderSource(vertexShader, 1, &testShader->vertexSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    //glCompileShader(vertexShader);//编译shader
    //
    //unsigned int fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建片元着色器
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    //glCompileShader(fragmentShader);//编译shader
    //
    ////组装顶点着色器和片元着色器
    //unsigned int shaderProgram;
    //shaderProgram = glCreateProgram();
    ////把之前编译的Shader附加到程序对象上，然后用glLinkProgram连接他们
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    //
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);
    
    //解析顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//告知VAO怎么解析VBO的数据
    glEnableVertexAttribArray(0);//启用顶点属性数组
    //解析顶点色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//告知VAO怎么解析VBO的数据
    glEnableVertexAttribArray(1);//启用顶点属性数组
    /*
	index：第几个属性，从0开始取，0，1，2，顺序自己定义，例如顶点位置，纹理，法线

    这里只有顶点位置，也只能讨论顶点位置，所以为0

    size：一个顶点所有数据的个数，这里每个顶点又3个浮点数属性值，所以是3

    type：顶点描述数据的类型，这里position数组中的数据全部为float，所以是GL_FLOAT

    normalized：是否需要显卡帮忙把数据归一化到-1到+1区间，这里不需要，所以设置GL_FALSE

    stride：一个顶点占有的总的字节数，这里为3个float，所以是sizeof(float)*3

    pointer：当前指针指向的vertex内部的偏离字节数，可以唯一的标识顶点某个属性的偏移量

    这里是指向第一个属性，顶点坐标，偏移量为0

    */

    //Render Loop
    while (!glfwWindowShouldClose(window))//如果没检测到关闭该窗口则循环
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置清屏颜色
        glClear(GL_COLOR_BUFFER_BIT);//指定清空哪个buffer，这里选择的是颜色缓冲区。

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        //float timeValue = glfwGetTime();//获取时间数值
        //float colorValue = (sin(timeValue) / 2.0) + 0.5;//使用sin函数让颜色在0.0到1.0之间改变，记得sin函数的范围是-1到1，我们需要先除2再加0.5改动范围。
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//获取shader程序中的uniform变量索引值
        //glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, 0.0, colorValue, 0.0, 1.0f);//设定uniform变量的值。
        
        testShader->use();
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);//使用索引缓冲区的索引值进行绘制。

        glfwSwapBuffers(window);       //交换前后缓冲器
        glfwPollEvents();       //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
    }

    glfwTerminate();//正确释放/删除之前的分配的所有资源
	
	return 0;
}