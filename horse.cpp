#include <stdio.h>
#include <stdlib.h>

#include <glad/gl.h>
#include <glad/gl.c>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>
#include <vector>

#include <shaders.h>

GLFWwindow* window;

int width, height;

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

GLuint vbo;

FT_Library ft;
FT_Face face;
FT_GlyphSlot g;

const char *fontfilename;

void display();
void render_text(const char *text, float x, float y, float sx, float sy);

void render_text(const char *text, float x, float y, float sx, float sy){
	const char *p;

	for(p = text; *p; p++){
		if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
		
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{x2,     -y2    , 0, 0},
			{x2 + w, -y2    , 1, 0},
			{x2,     -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1}
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x/64) * sx;
		y += (g->advance.y/64) * sy;
	}
}

int main(){
	//regular OpenGL stuff

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	window = glfwCreateWindow(640, 480, "Horse Game", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);
	
	//compile shaders
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	GLint success = 0;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE){
		std::cout << "Vertex shader no compile\n";
	}

	GLint logSize = 0;
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &logSize);
	std::vector<GLchar> errorLog(logSize);
	glGetShaderInfoLog(fragment_shader, logSize, NULL, &errorLog[0]);
	for(int i = 0; i < errorLog.size(); i++)
		std::cout << errorLog[i];

	//link program
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glUseProgram(program);

	//get attributes/uniforms
	attribute_coord = glGetAttribLocation(program, "coord");
	uniform_tex = glGetUniformLocation(program, "texer");
	uniform_color = glGetUniformLocation(program, "color");

	//make VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//make vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(attribute_coord);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	//freetype library stuff
	if(FT_Init_FreeType(&ft)){
		std::cout << "Could not init freetype library\n";
	}
	
	if(FT_New_Face(ft, "include/OpenSans-Regular.ttf", 0, &face)){
		std::cout << "Could not open font\n";
	}
	
	FT_Set_Pixel_Sizes(face, 0, 24);
	g = face->glyph;
	//unneeded for current project probably
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint tex;
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glUniform1i(uniform_tex, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//disable 4 byte allignment restrictions
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	

	while(!glfwWindowShouldClose(window)){
		display();
	}


	glDeleteProgram(program);
	return 0;
}

void display(){
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat white[4] = {1, 1, 1, 1};
	glUniform4fv(uniform_color, 1, white);
	
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glUseProgram(program);

	float sx = 2.0 / width;
	float sy = 2.0 / height;

	render_text("The Quick brown fox jumps over the lazy dog", -1 + 8 * sx, 1 - 50 * sy, sx, sy);

	glfwSwapBuffers(window);
	glfwPollEvents();

}
