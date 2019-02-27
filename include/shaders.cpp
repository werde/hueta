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

    //const GLchar *VSS = "void main() \n { \n gl_Position = ftransform(); \n }\0";
    //const GLchar *FSS = "void main() \n { \n gl_FragColor = vec4(0.4,0.4,0.8,1.0); \n } \n\0";

    GLchar *VSS = (GLchar*) malloc(sizeof(GLchar)*16384);
    GLchar *FSS = (GLchar*) malloc(sizeof(GLchar)*16384);

    //readShaderFile(".\\TransformVertexShader.vertexshader", VSS);
    //readShaderFile(".\\TextureFragmentShader.fragmentshader", FSS);
    printf("Reading %s and %s.....\n", file_path_vert, file_path_frag);
    readShaderFile(file_path_vert, VSS);
    readShaderFile(file_path_frag, FSS);

    //printf("%s\n", VSS);
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
		//MessageBox(NULL, (LPCSTR)&VertexShaderErrorMessage[0],  "e", MB_ICONEXCLAMATION | MB_OK);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char FragmentShaderErrorMessage[InfoLogLength+1];
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("frag %s\n", &FragmentShaderErrorMessage[0]);
		//MessageBox(NULL, (LPCSTR)&FragmentShaderErrorMessage[0],  "e", MB_ICONEXCLAMATION | MB_OK);
	}

    glAttachShader(*sp, vertexShader);
    glAttachShader(*sp, fragmentShader);
    glLinkProgram(*sp);

	/// Check the program
	/*glGetProgramiv(sp, GL_LINK_STATUS, &Result);
	glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(sp, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}*/
}
