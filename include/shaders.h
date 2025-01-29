//shader storage
const char* vertex_shader_text = 
"#version 330\n"
"\n"
"layout(location = 4) in vec4 coord;\n"
"out vec2 texcoord;\n"
"\n"
"void main(void){\n"
"	gl_Position = vec4(coord.xy, 0, 1);\n"
"	texcoord = coord.zw;\n"
"}";

const char* fragment_shader_text = 
"#version 330\n"
"\n"
"in vec2 texcoord;\n"
"uniform vec4 color;\n"
"uniform sampler2D tex;\n"
"\n"
"void main(void){\n"
"	gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;\n"
"}";
