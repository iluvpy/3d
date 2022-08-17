#include "Shader.hpp"


void Shader::init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {

    std::string vertSource = readShader(vertexShaderPath);
    std::string fragSource = readShader(fragmentShaderPath);
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);   
    compileShader(vertexShader, vertSource.c_str());

    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragSource.c_str());

    m_program = glCreateProgram();

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);


    int  success;
    char infoLog[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        throw std::runtime_error("failed to link shader program!\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

void Shader::bind() {
    glUseProgram(m_program);
}

void Shader::unbind() {
    glUseProgram(0);
}

GLint Shader::getUniformLocation(const std::string& name) {
    auto it = m_uLocations.find(name);
    if (it != m_uLocations.end()) {
        return it->second;
    }
    GLint location = glGetUniformLocation(m_program, name.c_str());
    m_uLocations.insert(std::make_pair(name, location));
    return location;
}


void Shader::setInt(const std::string& name, int i) {
    glUniform1i(getUniformLocation(name), i);
}

void Shader::setMatf4(const std::string& name, glm::mat4 mat) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}


std::string Shader::readShader(const std::string &path) {
    // Read from the text file
    std::ifstream shaderFile(path);
    std::string line;
    std::string content = "";
    
    while (getline(shaderFile, line)) {
        content.append(line);    
        content.append("\n");    
    }
    return content;
}

void Shader::compileShader(GLuint shader, const char *shaderSrc) {
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);  

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "info log: \n" << infoLog << std::endl;
        std::cout << "source: " << shaderSrc << std::endl;
        throw std::runtime_error("ERROR::SHADER::COMPILATION_FAILED\n");
    }
}


Shader::~Shader() {

}


