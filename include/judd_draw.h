#ifndef JUDD_DRAW_H
#define JUDD_DRAW_h
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <stdint.h>
#include <math.h>
typedef struct JUDD_TEXTURE_STRUCT{
    int w, h;
    char *data;
    GLuint tex;
} judd_texture_t;


typedef struct JUDD_SHADER_STRUCT{
    char *vert, *frag;
    GLuint id;
} judd_shader_t;

enum {
    JUDD_DTYPE_FILL,
    JUDD_DTYPE_TEX,
    JUDD_DTYPE_OUTLINE
};
enum {
    JUDD_IMGTYPE_RGB888,
    JUDD_IMGTYPE_BGR888,
    JUDD_IMGTYPE_RGBA8888,
    JUDD_IMGTYPE_RGB555,
    JUDD_IMGTYPE_RGBA4444
};
judd_texture_t *judd_create_texture(char *data, int w, int h, int imgtype);
judd_shader_t *judd_load_shader(char *vertex, char *fragment);
judd_shader_t *judd_create_shader(char *vertex, char *fragment);
void judd_draw_rect(int dtype, int x0, int y0, int x1, int y1, ...);
void judd_draw_line(int dtype, int x0, int y0, int x1, int y1, ...);
void judd_draw_triangle(int dtype, int x0, int y0, int x1, int y1, int x2, int y2, ...);
void judd_draw_circle(int dtype, int xc, int yc, int rad, ...);
void judd_draw_shape(int dtype, int nvert, ...);

#endif
#ifdef JUDD_DRAW_IMPL
#undef JUDD_DRAW_IMPL
judd_texture_t *judd_create_texture(char *data, int w, int h, int imgtype){
    judd_texture_t *tex = malloc(sizeof(judd_texture_t));
    *tex = (judd_texture_t){.w = w, .h = h, data = data};
    int internalformat, format;
    if(imgtype == JUDD_IMGTYPE_RGBA4444){
       internalformat = GL_RGBA;
       format =  GL_RGBA4;
    }
    if(imgtype == JUDD_IMGTYPE_RGB555){
       internalformat = GL_RGB;
       format = GL_RGB5;
    }
    if(imgtype == JUDD_IMGTYPE_RGB888){
       internalformat = GL_RGB;
       format = GL_RGB;
    }
    if(imgtype == JUDD_IMGTYPE_BGR888){
       internalformat = GL_RGB;
       format = GL_BGR;
    }
    glGenTextures(1, &(tex->tex));
    glBindTexture(GL_TEXTURE_2D, tex->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return tex;
}
judd_shader_t *judd_create_shader(char *vertex, char *fragment){
    char const *VertexSourcePointer = vertex;
    char const *FragmentSourcePointer = fragment;
    int success;
    char infoLog[512];
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint ProgramID;
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    }
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    }
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        puts(vertex);
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", infoLog);
    }
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    judd_shader_t *shader = malloc(sizeof(judd_shader_t));
    *shader = (judd_shader_t){.id = ProgramID, .vert = vertex, .frag = fragment};
    return shader;
}
judd_shader_t *judd_load_shader(char *vertex, char *fragment){
    FILE *frag = fopen(fragment, "r");
    FILE *vert = fopen(vertex, "r");
    fseek(frag, 0, SEEK_END);
    fseek(vert, 0, SEEK_END);
    int fragsize = ftell(frag);
    int vertsize = ftell(vert);
    rewind(frag);
    rewind(vert);
    char *bufferfrag = malloc((fragsize + 1) * sizeof(char));
    char *buffervert = malloc((vertsize + 1) * sizeof(char));
    fread(bufferfrag, fragsize, 1, frag);
    fread(buffervert, vertsize, 1, vert);
    bufferfrag[fragsize] = '\0';
    buffervert[vertsize] = '\0';
    return judd_create_shader(buffervert, bufferfrag);
}

void judd_draw_rect(int dtype, int x0, int y0, int x1, int y1, ...){
    va_list va_ptr;
    va_start(va_ptr, y1);
    if(dtype == JUDD_DTYPE_FILL){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        judd_draw_shape(dtype, 4, x0, y1, r, g, b, x0, y0, r, g, b, x1, y1, r, g, b, x1, y0, r, g, b);
    }
    if(dtype == JUDD_DTYPE_OUTLINE){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        int s = va_arg(va_ptr, int);
        judd_draw_shape(dtype, 4, x0, y1, r, g, b, x0, y0, r, g, b, x1, y1, r, g, b, x1, y0, r, g, b, s);
    }
    va_end(va_ptr);
}

void judd_draw_circle(int dtype, int xc, int yc, int rad, ...){
    va_list va_ptr;
    va_start(va_ptr, rad);
    int i;
    if(dtype == JUDD_DTYPE_FILL){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        int x[23], y[23];
        for(i = 0; i < 23; i++){
            x[i] = xc + cos(i*18*(M_PI/180))*rad;
            y[i] = yc + sin(i*18*(M_PI/180))*rad;
        }
        judd_draw_shape(dtype, 32,
        x[0], y[0], r, g, b, x[1], y[1], r, g, b, xc, yc, r, g, b,
        x[2], y[2], r, g, b, x[3], y[3], r, g, b, xc, yc, r, g, b,
        x[4], y[4], r, g, b, x[5], y[5], r, g, b, xc, yc, r, g, b,
        x[6], y[6], r, g, b, x[7], y[7], r, g, b, xc, yc, r, g, b,
        x[8], y[8], r, g, b, x[9], y[9], r, g, b, xc, yc, r, g, b,
        x[10], y[10], r, g, b, x[11], y[11], r, g, b, xc, yc, r, g, b,
        x[12], y[12], r, g, b, x[13], y[13], r, g, b, xc, yc, r, g, b,
        x[14], y[14], r, g, b, x[15], y[15], r, g, b, xc, yc, r, g, b,
        x[16], y[16], r, g, b, x[17], y[17], r, g, b, xc, yc, r, g, b,
        x[18], y[18], r, g, b, x[19], y[19], r, g, b, xc, yc, r, g, b,
        x[20], y[20], r, g, b, x[21], y[21], r, g, b, xc, yc, r, g, b,
        x[22], y[22], r, g, b, x[0], y[0], r, g, b, xc, yc, r, g, b
        );
//        judd_draw_shape(dtype, 20, x0, y1, r, g, b, x0, y0, r, g, b, x1, y1, r, g, b, x1, y0, r, g, b);
    }
    if(dtype == JUDD_DTYPE_OUTLINE){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        int s = va_arg(va_ptr, int);
        int x[20], y[20];
        for(i = 0; i < 20; i++){
            x[i] = xc + cos(i*18*(M_PI/180))*rad;
            y[i] = yc + sin(i*18*(M_PI/180))*rad;
        }
        judd_draw_shape(dtype, 20,
        x[0], y[0], r, g, b, x[1], y[1], r, g, b, x[2], y[2], r, g, b,
        x[3], y[3], r, g, b, x[4], y[4], r, g, b, x[5], y[5], r, g, b,
        x[6], y[6], r, g, b, x[7], y[7], r, g, b, x[8], y[8], r, g, b,
        x[9], y[9], r, g, b, x[10], y[10], r, g, b, x[11], y[11], r, g, b,
        x[12], y[12], r, g, b, x[13], y[13], r, g, b, x[14], y[14], r, g, b,
        x[15], y[15], r, g, b, x[16], y[16], r, g, b, x[17], y[17], r, g, b,
        x[18], y[18], r, g, b, x[19], y[19], r, g, b,
        s);
   }
   if(dtype == JUDD_DTYPE_TEX){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        judd_texture_t *tex = va_arg(va_ptr, judd_texture_t*);
        int tx = va_arg(va_ptr, int);
        int ty = va_arg(va_ptr, int);
        int x[20], y[20], txs[20], tys[20];
        for(i = 0; i < 20; i++){
            x[i] = xc + cos(i*18*(M_PI/180))*rad;
            y[i] = yc + sin(i*18*(M_PI/180))*rad;
            txs[i] = tx - (xc - x[i]);
            tys[i] = ty - (yc - y[i]);
        }
        judd_draw_shape(dtype, 32,
        x[0], y[0], txs[0], tys[0], x[1], y[1], txs[1], tys[1], xc, yc, tx, ty,
        x[2], y[2], txs[2], tys[2], x[3], y[3], txs[3], tys[3], xc, yc, tx, ty,
        x[4], y[4], txs[4], tys[4], x[5], y[5], txs[5], tys[5], xc, yc, tx, ty,
        x[6], y[6], txs[6], tys[6], x[7], y[7], txs[7], tys[7], xc, yc, tx, ty,
        x[8], y[8], txs[8], tys[8], x[9], y[9], txs[9], tys[9], xc, yc, tx, ty,
        x[10], y[10], txs[10], tys[10], x[11], y[11], txs[11], tys[11], xc, yc, tx, ty,
        x[12], y[12], txs[12], tys[12], x[13], y[13], txs[13], tys[13], xc, yc, tx, ty,
        x[14], y[14], txs[14], tys[14], x[15], y[15], txs[15], tys[15], xc, yc, tx, ty,
        x[16], y[16], txs[16], tys[16], x[17], y[17], txs[17], tys[17], xc, yc, tx, ty,
        x[18], y[18], txs[18], tys[18], x[19], y[19], txs[19], tys[19], xc, yc, tx, ty,
        x[20], y[20], txs[20], tys[20], x[21], y[21], txs[21], tys[21], xc, yc, tx, ty,
        x[22], y[22], txs[22], tys[22], x[0], y[0], txs[0], tys[0], xc, yc, tx, ty,
        tex);
   }

   va_end(va_ptr);
}
void judd_draw_triangle(int dtype, int x0, int y0, int x1, int y1, int x2, int y2, ...){
    va_list va_ptr;
    va_start(va_ptr, y2);
    if(dtype == JUDD_DTYPE_FILL){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        judd_draw_shape(dtype, 4, x0, y0, r, g, b, x1, y1, r, g, b, x2, y2, r, g, b);
    }
    if(dtype == JUDD_DTYPE_OUTLINE){
        int r = va_arg(va_ptr, int);
        int g = va_arg(va_ptr, int);
        int b = va_arg(va_ptr, int);
        int s = va_arg(va_ptr, int);
        judd_draw_shape(dtype, 3, x0, x0, r, g, b, x0, x1, r, g, b, x2, x2, r, g, b, s);
    }
    va_end(va_ptr);
}
void judd_draw_shape(int dtype, int nvert, ...){
    int w, h;
    int i;
    int *viewport = malloc(sizeof(int) * 4);
    judd_shader_t *shader = malloc(sizeof(judd_shader_t));
    GLuint vbo, ebo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    shader->id = 0;
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM,&id);
    if(id == 0){
        if( dtype == JUDD_DTYPE_FILL || dtype == JUDD_DTYPE_OUTLINE){
            shader = judd_create_shader(
                "#version 330 core\n"
                "layout(location = 0) in vec3 vertexPosition;\n"
                "layout(location = 1) in vec3 vertexColor;\n"
                "out vec3 fragmentColor;\n"
                "out vec3 fragmentPos;\n"
                "void main(){\n"
                "fragmentColor = vertexColor;\n"
                "fragmentPos = vertexPosition;\n"
                "gl_Position.xyz = vertexPosition;\n"
                "gl_Position.w = 1.0;\n"
                "}",
                "#version 330 core\n"
                "in vec3 fragmentColor;\n"
                "in vec3 fragmentPos;\n"
                "out vec3 color;\n"
                "void main(){color = fragmentColor;}"
            );
        } else{
            shader = judd_create_shader(
                "#version 330 core\n"\
                "layout(location = 0) in vec3 vertexPosition;\n"
                "layout(location = 1) in vec2 vertexTexCoord;\n"
                "out vec3 fragmentPos;\n"
                "out vec2 fragmentTexCoord;\n"
                "void main(){\n"
                "\nfragmentTexCoord = vertexTexCoord;\n"
                "gl_Position.xyz = vertexPosition;\n"
                "gl_Position.w = 1.0;\n"
                "}",
                "#version 330 core\n"
                "in vec3 fragmentPos;\n"
                "in vec2 fragmentTexCoord;\n"
                "uniform sampler2D tex;\n"
                "out vec3 color;\n"
                "void main(){\n"
                "color = texture(tex, fragmentTexCoord).rgb;\n"
                "}"
            );
        }
        glUseProgram(shader->id);
    }
    glGetIntegerv(GL_VIEWPORT, viewport);
    w = viewport[2];
    h = viewport[3];

    va_list va_ptr;
    va_start(va_ptr, nvert);

    if(dtype == JUDD_DTYPE_OUTLINE){
        GLfloat *vbo_data = malloc(sizeof(GLfloat) * nvert * 6);
        unsigned *ebo_data = malloc(sizeof(unsigned) * (nvert * 2 + 1));
        for(i = 0; i < nvert * 6; i+=6){
            vbo_data[i] = (((float)va_arg(va_ptr, int))/((float)w)*2.0f)-1.0f;
            vbo_data[i+1] = 2.0f-(((float)va_arg(va_ptr, int))/((float)h)*2.0f)-1.0f;
            vbo_data[i+2] = 0;
            vbo_data[i+3] = (float)va_arg(va_ptr, int);
            vbo_data[i+4] = (float)va_arg(va_ptr, int);
            vbo_data[i+5] = (float)va_arg(va_ptr, int);
        }
        int s = va_arg(va_ptr, int);
        for(i = 0; i < (nvert-1)*2; i+=2){
            ebo_data[i] = i/2;
            ebo_data[i+1] = i/2+1;
        }
        ebo_data[nvert*2-2] = nvert-1;
        ebo_data[nvert*2-1] = 0;
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, nvert * 6 * sizeof(GLfloat), vbo_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nvert * 2 * sizeof(unsigned), ebo_data, GL_STATIC_DRAW);
        glLineWidth(((float)s));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, nvert*2+2, GL_UNSIGNED_INT, 0);
    } else if(dtype == JUDD_DTYPE_FILL){
        GLfloat *vbo_data = malloc(sizeof(GLfloat) * nvert * 6);
        unsigned *ebo_data = malloc(sizeof(unsigned) * nvert * 3);
        for(i = 0; i < nvert * 6; i+=6){
            vbo_data[i] = (((float)va_arg(va_ptr, int))/((float)w)*2.0f)-1.0f;
            vbo_data[i+1] = 2.0f-(((float)va_arg(va_ptr, int))/((float)h)*2.0f)-1.0f;
            vbo_data[i+2] = 0;
            vbo_data[i+3] = (float)va_arg(va_ptr, int);
            vbo_data[i+4] = (float)va_arg(va_ptr, int);
            vbo_data[i+5] = (float)va_arg(va_ptr, int);
        }
        for(i = 0; i < (nvert-2)*3; i+=3){
            ebo_data[i] = i/3;
            ebo_data[i+1] = i/3+1;
            ebo_data[i+2] = i/3+2;
        }
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, nvert * 6 * sizeof(GLfloat), vbo_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nvert * 3 * sizeof(unsigned), ebo_data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, (nvert-2)*3, GL_UNSIGNED_INT, 0);
     } else {
        GLfloat *vbo_data = malloc(sizeof(GLfloat) * nvert * 5);
        unsigned *ebo_data = malloc(sizeof(unsigned) * nvert * 3);
        judd_texture_t *tex = va_arg(va_ptr, judd_texture_t*);
        for(i = 0; i < nvert * 5; i+=5){
            vbo_data[i] = (((float)va_arg(va_ptr, int))/((float)w)*2.0f)-1.0f;
            vbo_data[i+1] = 2.0f-(((float)va_arg(va_ptr, int))/((float)h)*2.0f)-1.0f;
            vbo_data[i+2] = 0;
            vbo_data[i+3] = ((float)va_arg(va_ptr, int)/tex->w);
            vbo_data[i+4] = ((float)va_arg(va_ptr, int)/tex->h);
        }
        for(i = 0; i < (nvert-2)*3; i+=3){
            ebo_data[i] = i/3;
            ebo_data[i+1] = i/3+1;
            ebo_data[i+2] = i/3+2;
        }
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, nvert * 5 * sizeof(GLfloat), vbo_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (nvert-2) * 3 * sizeof(unsigned), ebo_data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, tex->tex);
        glDrawElements(GL_TRIANGLES, (nvert-2)*3, GL_UNSIGNED_INT, 0);
    }
    glGetIntegerv(GL_CURRENT_PROGRAM,&id);
    if(id == shader->id){
         glUseProgram(0);
    }
}
#endif

