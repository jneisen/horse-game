#include <glad/gl.h>
#include <glad/gl.c>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>

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
}
