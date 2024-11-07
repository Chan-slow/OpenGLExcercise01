#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	/*
	std::ifstream 是一个输入文件流类，它有两个与文件错误相关的标志：failbit 和 badbit。
	failbit：表示输入操作失败，但流并未达到致命错误。例如，读取文件时遇到无效字符、格式问题等。
	badbit：表示文件流遇到无法恢复的错误，比如硬件故障、文件系统错误等。
	*/
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())//如果不打开vertex文件或fagment文件
		{
			throw std::exception("open file error");//创建一个异常对象并抛出，别忘了设置异常信息，
		}
		vertexSStream << vertexFile.rdbuf();//rdbuf() 可以直接访问整个文件的内容，并读取到vertexSStream字符串流中
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器,返回的是一个创建完的着色器的id。
		glShaderSource(vertex, 1, &vertexSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
		glCompileShader(vertex);//编译shader
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);//创建片元着色器
		glShaderSource(fragment, 1, &fragmentSource, nullptr);//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
		glCompileShader(fragment);//编译shader
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		//组装顶点着色器和片元着色器
		ID = glCreateProgram();
		//把之前编译的Shader附加到程序对象上，然后用glLinkProgram连接他们
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
	}
	catch (const std::exception& ex)//捕获所有从exception派生的异常并将异常对象引用存储在ex中，这ex是咱们自己定义的名字
	{
		printf(ex.what());//打印异常信息
	}
}

void Shader::use()
{
	glUseProgram(ID);
}