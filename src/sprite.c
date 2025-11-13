#include "sprite.h"
#include "mat.h"
#include "math.h"

decl_result(SharedShaderPtr, Shader*);
static ResultSharedShaderPtr sprite_shared_shader_get(void);
static void sprite_shared_shader_drop(void);

ResultSprite sprite_new(const Texture *texture, Rect rect) {
    const GLfloat vertices[] = {
    //  positions           texture coords
         0.5f,  0.5f, 0.0f, rect.x + rect.w, rect.y,          // top right
         0.5f, -0.5f, 0.0f, rect.x + rect.w, rect.y - rect.h, // bottom right
        -0.5f, -0.5f, 0.0f, rect.x,          rect.y - rect.h, // bottom left
        -0.5f,  0.5f, 0.0f, rect.x,          rect.y           // top left
    };
    const GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    GLuint vbo, vao, ibo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return (ResultSprite)Ok(((Sprite) {
        .transform = transform_new(),
        .texture = texture,
        .shader = try(sprite_shared_shader_get(),
                      (ResultSprite)Err(), "Failed to get shared shader"),
        .vertex_buff = vbo,
        .vertex_arrays = vao,
        .index_buff = ibo
    }));
}

void sprite_draw(Sprite *this, const SceneDrawCtx *dctx, const Transform *transform) {
    (void)dctx;
    shader_use(this->shader);
    Transform t = transform_mul(&this->transform, transform);
    shader_set_mat4(this->shader, "mvp", transform_get_mat4(&t));
    glBindVertexArray(this->vertex_arrays);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void sprite_drop(Sprite *this) {
    glDeleteVertexArrays(1, &this->vertex_arrays);
    glDeleteBuffers(1, &this->vertex_buff);
    glDeleteBuffers(1, &this->index_buff);
    this->vertex_arrays = 0;
    this->vertex_buff = 0;
    this->index_buff = 0;
    this->shader = NULL;
    sprite_shared_shader_drop();
}

static Shader shared_shader;
static unsigned shared_shader_user_count = 0;
static bool shared_shader_ready = false;

static ResultSharedShaderPtr sprite_shared_shader_get() {
    if (!shared_shader_ready) {
        shared_shader = try(shader_new(
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "uniform mat4 mvp;\n"
        "out vec2 TexCoord;\n"
        "void main() {\n"
            "gl_Position = mvp * vec4(aPos, 1.0);\n"
            "TexCoord = aTexCoord;\n"
        "}",
        "#version 330 core\n"
        "in vec2 TexCoord;\n"
        "out vec4 color;\n"
        "uniform sampler2D texture1;\n"
        "void main() {\n"
            "color = texture(texture1, TexCoord);\n"
        "}"
        ),
        (ResultSharedShaderPtr)Err(), "Failed to init sprite shared shader");
        shared_shader_ready = true;
    }
    shared_shader_user_count++;
    return (ResultSharedShaderPtr)Ok(&shared_shader);
}

static void sprite_shared_shader_drop() {
    shared_shader_user_count--;
    if (!shared_shader_user_count) {
        shader_drop(&shared_shader);
        shared_shader_ready = false;
    }
}
