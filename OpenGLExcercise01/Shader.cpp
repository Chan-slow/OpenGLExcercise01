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
	std::ifstream ��һ�������ļ����࣬�����������ļ�������صı�־��failbit �� badbit��
	failbit����ʾ�������ʧ�ܣ�������δ�ﵽ�����������磬��ȡ�ļ�ʱ������Ч�ַ�����ʽ����ȡ�
	badbit����ʾ�ļ��������޷��ָ��Ĵ��󣬱���Ӳ�����ϡ��ļ�ϵͳ����ȡ�
	*/
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())//�������vertex�ļ���fagment�ļ�
		{
			throw std::exception("open file error");//����һ���쳣�����׳��������������쳣��Ϣ��
		}
		vertexSStream << vertexFile.rdbuf();//rdbuf() ����ֱ�ӷ��������ļ������ݣ�����ȡ��vertexSStream�ַ�������
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��,���ص���һ�����������ɫ����id��
		glShaderSource(vertex, 1, &vertexSource, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
		glCompileShader(vertex);//����shader
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);//����ƬԪ��ɫ��
		glShaderSource(fragment, 1, &fragmentSource, nullptr);//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
		glCompileShader(fragment);//����shader
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		//��װ������ɫ����ƬԪ��ɫ��
		ID = glCreateProgram();
		//��֮ǰ�����Shader���ӵ���������ϣ�Ȼ����glLinkProgram��������
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
	}
	catch (const std::exception& ex)//�������д�exception�������쳣�����쳣�������ô洢��ex�У���ex�������Լ����������
	{
		printf(ex.what());//��ӡ�쳣��Ϣ
	}
}

void Shader::use()
{
	glUseProgram(ID);
}