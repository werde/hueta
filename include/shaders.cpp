#include "shaders.h"

#include "../__trash.h"

void readShaderFile(const char* file_path, const GLchar* pShaderCode)
{
    std::ifstream input(file_path, std::ios::in | std::ios::binary);
    char c;
    char*  ptr = pShaderCode;
    while (input.get(c)) {
        //printf("%c", c);
        *ptr = c;
        ptr++;
    }
    *ptr='\0';
}

void compileShaderProgramm(GLuint* sp, const char* file_path_vert, const char* file_path_frag)
{
    GLchar *VSS = (GLchar*) malloc(sizeof(GLchar)*16384);
    GLchar *FSS = (GLchar*) malloc(sizeof(GLchar)*16384);

    //printf("Reading %s and %s.....\n", file_path_vert, file_path_frag);
    readShaderFile(file_path_vert, VSS);
    readShaderFile(file_path_frag, FSS);

    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &VSS, NULL);
    glShaderSource(fragmentShader, 1, &FSS, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    ///*Error check
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char VertexShaderErrorMessage[InfoLogLength+1];
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("vert %s\n", &VertexShaderErrorMessage[0]);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char FragmentShaderErrorMessage[InfoLogLength+1];
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("frag %s\n", &FragmentShaderErrorMessage[0]);
	}

    glAttachShader(*sp, vertexShader);
    glAttachShader(*sp, fragmentShader);
    glLinkProgram(*sp);
}
