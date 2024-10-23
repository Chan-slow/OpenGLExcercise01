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


    unsigned int VAO;//����VAO
    glGenVertexArrays(1, &VAO);//ע��VAO��id�����뻺���������Ǳ�����ʹ��������ʽ�������VAO���˴���ʱ����Ҫ���ʹ�����һ����
    glBindVertexArray(VAO);

    unsigned int VBO;//����VBO
    glGenBuffers(1, &VBO);//ע��VBO��id�����뻺����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�趨�������ĸ����ݴ��͵���������

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glCompileShader(vertexShader);//����shader

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//����ƬԪ��ɫ��
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glCompileShader(fragmentShader);//����shader

    //��װ������ɫ����ƬԪ��ɫ��
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //��֮ǰ�����Shader���ӵ���������ϣ�Ȼ����glLinkProgram��������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//��֪VAO��ô����VBO������
    /*
	index���ڼ������ԣ���0��ʼȡ��0��1��2��˳���Լ����壬���綥��λ�ã���������

    ����ֻ�ж���λ�ã�Ҳֻ�����۶���λ�ã�����Ϊ0

    size��һ�������������ݵĸ���������ÿ����������������������ֵ��������2

    type�������������ݵ����ͣ�����position�����е�����ȫ��Ϊfloat��������GL_FLOAT

    normalized���Ƿ���Ҫ�Կ���æ�����ݹ�һ����-1��+1���䣬���ﲻ��Ҫ����������GL_FALSE

    stride��һ������ռ�е��ܵ��ֽ���������Ϊ����float��������sizeof(float)*2

    pointer����ǰָ��ָ���vertex�ڲ���ƫ���ֽ���������Ψһ�ı�ʶ����ĳ�����Ե�ƫ����

    ������ָ���һ�����ԣ��������꣬ƫ����Ϊ0

    */
    glEnableVertexAttribArray(0);//���ö�����������
    //Render Loop
    while (!glfwWindowShouldClose(window))//���û��⵽�رոô�����ѭ��
    {
        processInput(window);

        glClearColor(0.5f, 0.3f, 0.4f, 1.0f);//����������ɫ
        glClear(GL_COLOR_BUFFER_BIT);//ָ������ĸ�buffer������ѡ�������ɫ��������

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);       //����ǰ�󻺳���
        glfwPollEvents();       //�����û�д���ʲô�¼�������������롢����ƶ��ȣ�
    }

    glfwTerminate();//��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
	
	return 0;
}