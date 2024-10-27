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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)//����˳���esc�Ƿ񱻰���
    {
        glfwSetWindowShouldClose(window, true);//�趨����Ϊ�ر�״̬
    }
}

int main() 
{

	
    glfwInit(); //����glfwInit��������ʼ��GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //MAJOR���汾Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//MINOR�ΰ汾Ϊ3��Ҳ����ʹ�õ�GLΪ3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)

    //��GLFW����
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", nullptr, nullptr);
    if (!window)
    {
        printf("Open window failed.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//�������������Ľ�ʹ�øô���

    //��ʼ��glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed.");
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);//�趨���ڳ�ʼ����ʹ�С
    //glEnable(GL_CULL_FACE);//�������޳�ģʽ
    //glCullFace(GL_BACK);//�޳�����
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//ѡ�����ģʽ������ʹ���߿�

    //unsigned int VAO;//����VAO
    //glGenVertexArrays(1, &VAO);//ע��VAO��id�����뻺���������Ǳ�����ʹ��������ʽ�������VAO���˴���ʱ����Ҫ���ʹ�����һ����
    //glBindVertexArray(VAO);
    //
    //unsigned int VBO;//����VBO
    //glGenBuffers(1, &VBO);//ע��VBO��id�����뻺����
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�趨�������ĸ����ݴ��͵���������

    unsigned int VAO[2],VBO[2];//����
    glGenVertexArrays(2, VAO);//ע��VAO��id�����뻺����
    glGenBuffers(2, VBO);//ע��VBO��id�����뻺����
    
    glBindVertexArray(VAO[0]);//������Ϊ��ǰ������VAO��֮���������й��ڶ������ݵ����ã���������ʹ�õ�VBO���󣬶�����������õ���Ϣ���ᱻ�洢��VAO֮�У�
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);//������Ϊ��ǰ������VAO��֮���������й��ڶ������ݵ����ã���������ʹ�õ�VBO���󣬶�����������õ���Ϣ���ᱻ�洢��VAO֮�У�
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);//ע��EBO������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//�󶨻�����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glCompileShader(vertexShader);//����shader

    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);//����ƬԪ��ɫ��
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glCompileShader(fragmentShader1);//����shader

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);//����ƬԪ��ɫ��
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glCompileShader(fragmentShader2);//����shader

    //��װ������ɫ����ƬԪ��ɫ��
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    //��֮ǰ�����Shader���ӵ���������ϣ�Ȼ����glLinkProgram��������
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
    while (!glfwWindowShouldClose(window))//���û��⵽�رոô�����ѭ��
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//����������ɫ
        glClear(GL_COLOR_BUFFER_BIT);//ָ������ĸ�buffer������ѡ�������ɫ��������

        //glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//ʹ������������������ֵ���л��ơ�

        glfwSwapBuffers(window);       //����ǰ�󻺳���
        glfwPollEvents();       //�����û�д���ʲô�¼�������������롢����ƶ��ȣ�
    }

    glfwTerminate();//��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
	
	return 0;
}