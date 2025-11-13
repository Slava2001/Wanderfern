#include "shader.h"

decl_result(ShaderId, GLuint);
static ResultShaderId compile_shader(GLuint type, const char *src);

static ResultShaderId compile_shader(GLuint type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar log_buff[512];
        glGetShaderInfoLog(shader, sizeof(log_buff), NULL, log_buff);
        loge("Failed to compile shader: %s", log_buff);
        return (ResultShaderId)Err();
    }
    return (ResultShaderId)Ok(shader);
}

ResultShader shader_new(const char *vertex_src, const char *fragment_src) {
    GLuint vertex_shader = try(compile_shader(GL_VERTEX_SHADER, vertex_src),
                               (ResultShader)Err(), "Failed to compile vertex shader");
    GLuint fragment_shader = try(compile_shader(GL_FRAGMENT_SHADER, fragment_src),
                                 (ResultShader)Err(), "Failed to compile fragment shader");
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar log_buff[512];
        glGetProgramInfoLog(shader_program, sizeof(log_buff), NULL, log_buff);
        loge("Failed to link shader: %s", log_buff);
        return (ResultShader)Err();
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return (ResultShader)Ok((Shader) {
        .shader_id = shader_program
    });
}

void shader_use(const Shader *this) {
    glUseProgram(this->shader_id);
}

void shader_drop(Shader *this) {
    glDeleteProgram(this->shader_id);
    this->shader_id = 0;
}

void shader_set_mat4(Shader *this, const char *name, const Mat4 *mat) {
    glUniformMatrix4fv(glGetUniformLocation((GLuint)this->shader_id, name), 1,
                       GL_FALSE, (const GLfloat *)mat);
}
