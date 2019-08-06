#ifndef SHADER_H
#define SHADER_H
#include <gl/GL.h>
class Shader
{
public:
	Shader();
	~Shader();

	

	int loadShader(const char* vertex_file_path, const char* fragment_file_path);


};
#endif//!SHADER_H
