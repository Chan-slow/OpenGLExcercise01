#include <iostream>
#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {                            
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };                                                          

unsigned int indices[] = {
    0,1,2,
    2,3,0
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
    GLFWwindow* window = glfwCreateWindow(800, 800, "My OpenGL Game", nullptr, nullptr);
    if (!window)
    {
        printf("Open window failed.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//表明我们上下文将使用该窗口
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr,
        io.Fonts->GetGlyphRangesChineseFull());

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    bool isEnter = true;
    float f = 0;
    glm::vec3 clear_color = glm::vec3(1, 1, 1);
    int counter = 0;


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

    glViewport(0, 0, 800, 800);//设定窗口初始坐标和大小
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//告知VAO怎么解析VBO的数据
    glEnableVertexAttribArray(0);//启用顶点属性数组
    //解析顶点色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//告知VAO怎么解析VBO的数据
    glEnableVertexAttribArray(1);//启用顶点属性数组
    //解析uv坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//告知VAO怎么解析VBO的数据
    glEnableVertexAttribArray(2);//启用顶点属性数组
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

    unsigned int texture1;//声明变量来存储id
    glGenTextures(1, &texture1);//注册tex的id，申请缓冲区
    glBindTexture(GL_TEXTURE_2D, texture1);//绑定当前的id到图片缓冲区

    stbi_set_flip_vertically_on_load(true);//加载图片前用这个来翻转y轴
    int width, height, nrChannels;
    unsigned char* data1 = stbi_load("seer.jpg", &width, &height, &nrChannels, 0);//载入图片数据
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1); // 使用后释放内存

    unsigned int texture2;//声明变量来存储id
    glGenTextures(1, &texture2);//注册tex的id，申请缓冲区
    glBindTexture(GL_TEXTURE_2D, texture2);//绑定当前的id到图片缓冲区

    stbi_set_flip_vertically_on_load(true);//加载图片前用这个来翻转y轴
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//载入图片数据
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data2); // 使用后释放内存


    //Render Loop
    while (!glfwWindowShouldClose(window))//如果没检测到关闭该窗口则循环
    {
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(0.0f, 0, 0));
        trans = glm::rotate(trans, f, glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置清屏颜色
        glClear(GL_COLOR_BUFFER_BIT);//指定清空哪个buffer，这里选择的是颜色缓冲区。

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        //float timeValue = glfwGetTime();//获取时间数值
        //float colorValue = (sin(timeValue) / 2.0) + 0.5;//使用sin函数让颜色在0.0到1.0之间改变，记得sin函数的范围是-1到1，我们需要先除2再加0.5改动范围。
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//获取shader程序中的uniform变量索引值
        //glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, 0.0, colorValue, 0.0, 1.0f);//设定uniform变量的值。
        
        testShader->use(); // 不要忘记在设置uniform变量之前激活着色器程序！
        glUniform1i(glGetUniformLocation(testShader->ID, "texture1"), 0); // 手动设置
        testShader->setInt("texture2", 1); // 或者使用着色器类设置
        testShader->setMatrix4f("Transform", trans);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用索引缓冲区的索引值进行绘制。

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("调试界面");
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &isEnter);      

            ImGui::SliderFloat("float", &f, 0.0f, 180.f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);       //交换前后缓冲器
        glfwPollEvents();       //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();//正确释放/删除之前的分配的所有资源
	
	return 0;
}