#ifndef MSHADER_HPP
#define MSHADER_HPP

#include "json.hpp"

#include <GL/gl3w.h>

struct MUniform
{
    std::string name;
	int position;
	GLenum type;

	void assertType(GLenum type) const
	{
		if(this->type != type)
			throw std::runtime_error("uniform type mismatch!");
	}
};

struct MShader
{
	GLuint program;
    std::map<std::string, MUniform> uniforms;

	MShader();
	explicit MShader(nlohmann::json const & data);
};

#endif // MSHADER_HPP
