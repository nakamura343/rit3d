#include "pch.h"
#include "GLProgram.h"

GLProgram* GLProgram::Create(const RString& _name, const RString& vertexPath, const RString& fragmentPath, const RString& defines, const RString& geometryPath) {
	return new GLProgram(_name, vertexPath, fragmentPath, defines, geometryPath);
}
void GLProgram::Destroy(GLProgram* _shader) {
	delete _shader;
	_shader = nullptr;
}

void GLProgram::_destroy() {

}

GLProgram::GLProgram(const RString& _name, const RString& vertexPath, const RString& fragmentPath, const RString& defines, const RString& geometryPath) : m_name(_name) {
	//���ļ�·����ȡ���㡢Ƭ����ɫ��
	RString vertexCode;
	RString fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//��֤ifstream��������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//���ļ�
		vShaderFile.open(vertexPath.c_str());
		fShaderFile.open(fragmentPath.c_str());
		std::stringstream vShaderStream, fShaderStream;
		//��ȡ�ļ��Ļ������ݵ���������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//�ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();
		//ת����������string
		vertexCode = defines + vShaderStream.str();
		fragmentCode = defines + fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		cout << "shader file read failed" << endl;
	}
	const RChar* vShaderCode = vertexCode.c_str();
	const RChar* fShaderCode = fragmentCode.c_str();

	//������ɫ��
	RUInt vertex, fragment, geometry;
	RInt success;
	RChar infoLog[512];

	//������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "vertex shader compilation failed\n" << infoLog << endl;
	}
	//ƬԴ��ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "fragment shader compilation failed\n" << infoLog << endl;
	}

	//��������ɫ��
	if (geometryPath != "") {
		//���ļ�·����ȡ������ɫ��
		RString geometryCode;
		std::ifstream gShaderFile;
		//��֤ifstream��������׳��쳣
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//���ļ�
			gShaderFile.open(geometryPath.c_str());
			std::stringstream gShaderStream;
			//��ȡ�ļ��Ļ������ݵ���������
			gShaderStream << gShaderFile.rdbuf();
			//�ر��ļ�������
			gShaderFile.close();
			//ת����������string
			geometryCode = defines + gShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			cout << "shader file read failed" << endl;
		}
		const RChar* gShaderCode = geometryCode.c_str();

		//������ɫ��
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			cout << "geometry shader compilation failed\n" << infoLog << endl;
		}
	}
	//��ɫ������
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	if (geometryPath != "") {
		glAttachShader(ID, geometry);
	}
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cout << "program linking failed\n" << infoLog << endl;
	}

	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != "") {
		glDeleteShader(geometry);
	}
}

GLProgram::~GLProgram() {
	_destroy();
}

void GLProgram::use() {
	glUseProgram(ID);
}

void GLProgram::setBool(const RString &name, RBool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void GLProgram::setInt(const RString &name, RInt value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void GLProgram::setFloat(const RString &name, RFloat value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void GLProgram::setVec3(const RString &name, RFloat x, RFloat y, RFloat z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void GLProgram::setVec3(const RString &name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void GLProgram::setMat4(const RString &name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}