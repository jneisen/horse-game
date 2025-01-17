//shader storage
const char* vertex_shader = 
"#version 330\n"
"\n"
"layout(location = 0) in vec4 coord\n"
"out vec2 texcoord;\n"
"\n"
"void main(void){\n"
"	gl_Position = vec4(coord.xy, 0, 1);\n"
"	texcoord = coord.zw;\n"
"}";

const char* fragment_shader = 
"#version 330\n"
"\n"
"in vec2 texcoord;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"\n"
"void main(void){\n"
"	gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;\n"
"}";
