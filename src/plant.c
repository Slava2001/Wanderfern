#include "plant.h"

#define _USE_MATH_DEFINES
#include <math.h>

decl_result(SharedShaderPtr, Shader*);
static ResultSharedShaderPtr shared_shader_get(void);
static void shared_shader_drop(void);

ResultPlant plant_new(Vec2 pos) {
    Plant plant;
    Transform t = transform_new();
    plant.transform = transform_translate(&t, vec3(pos.x, 0, pos.y));
    plant.buff[0].start_radius = 1.0f;
    plant.buff[0].start_color = vec3(0.6f, 0.3f, 0.0f);
    plant.buff[0].end_radius = 1.0f;
    plant.buff[0].end_color = vec3(0.6f, 0.3f, 0.0f);
    plant.buff[0].len = 1.0f;
    plant.buff[0].next_cnt = 1;
    plant.buff[0].next = NULL;
    plant.shader = try(shared_shader_get(), (ResultPlant)Err(), "Failed to get shader");

    const GLfloat vertices[] = {
         0.2f, 0.0f,  0.2f, 0.6f, 0.3f, 0.0f,
         0.2f, 0.0f, -0.2f, 0.6f, 0.3f, 0.0f,
        -0.2f, 0.0f, -0.2f, 0.6f, 0.3f, 0.0f,
        -0.2f, 0.0f,  0.2f, 0.6f, 0.3f, 0.0f,
         0.2f, 1.0f,  0.2f, 0.6f, 0.3f, 0.0f,
         0.2f, 1.0f, -0.2f, 0.6f, 0.3f, 0.0f,
        -0.2f, 1.0f, -0.2f, 0.6f, 0.3f, 0.0f,
        -0.2f, 1.0f,  0.2f, 0.6f, 0.3f, 0.0f
    };

    const GLuint indices[] = {
        0, 1, 4,
        4, 5, 1,
        1, 2, 5,
        5, 6, 2,
        2, 3, 6,
        6, 7, 3,
        3, 0, 7,
        7, 4, 0,
    };
    plant.index_cnt = sizeof(indices) / sizeof(*indices);
    GLuint vbo, vao, ibo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    plant.vertex_buff = vbo;
    plant.vertex_arrays = vao;
    plant.index_buff = ibo;
    return (ResultPlant)Ok(plant);
}

void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform) {
    (void)dctx;
    shader_use(this->shader);
    Mat4 mvp = transform_get_mvp(transform, &this->transform);
    shader_set_mat4(this->shader, "mvp", &mvp);
    glBindVertexArray(this->vertex_arrays);
    glDrawElements(GL_TRIANGLES, this->index_cnt, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void plant_drop(Plant *this) {
    glDeleteVertexArrays(1, &this->vertex_arrays);
    glDeleteBuffers(1, &this->vertex_buff);
    glDeleteBuffers(1, &this->index_buff);
    this->vertex_arrays = 0;
    this->vertex_buff = 0;
    this->index_buff = 0;
    this->shader = NULL;
    shared_shader_drop();
}

static Shader shared_shader;
static unsigned shared_shader_user_count = 0;
static bool shared_shader_ready = false;

static ResultSharedShaderPtr shared_shader_get() {
    if (!shared_shader_ready) {
        shared_shader = try(shader_new(
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "uniform mat4 mvp;\n"
        "out vec3 frag_color;\n"
        "void main() {\n"
            "gl_Position = mvp * vec4(aPos, 1.0);\n"
            "frag_color = aColor;\n"
        "}",
        "#version 330 core\n"
        "in vec3 frag_color;\n"
        "out vec4 color;\n"
        "void main() {\n"
            "color = vec4(frag_color, 1.0);\n"
        "}"
        ),
        (ResultSharedShaderPtr)Err(), "Failed to init sprite shared shader");
        shared_shader_ready = true;
    }
    shared_shader_user_count++;
    return (ResultSharedShaderPtr)Ok(&shared_shader);
}

static void shared_shader_drop() {
    shared_shader_user_count--;
    if (!shared_shader_user_count) {
        shader_drop(&shared_shader);
        shared_shader_ready = false;
    }
}
