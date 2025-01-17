#include <glad/gl.h>
#include <glad/gl.c>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>

#include <shaders.h>

void render_text(const char *text, float x, float y, float sx, float sy){

}

void main(){
	FT_Library ft;
	if(FT_Init_FreeType(&ft)){
		fprintf(stderr, "Could not init freetype library\n");
		return 1;
	}
	
	FT_Face face;

	if(FT_New_Face(ft, "FreeSans.ttf", 0, &face)){
		fprintf(stderr, "Could not open font\n");
		return 1;
	}
	
	FT_Set_Pixel_Sizes(face, 0, 24);
	
	if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)){
		fprintf(stderr, "Could not load character 'X'\n");
		return 1;
	}

	FT_GlyphSlot g = face->glyph;
	//unneeded for current project probably
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//unclear whether or not uniform_tex has to be defined (or is automatic)
	glUniform1i(uniform_tex, 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//disable 4 byte allignment restrictions
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
