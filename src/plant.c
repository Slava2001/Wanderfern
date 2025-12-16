#include "plant.h"
#include "vec.h"

#define _USE_MATH_DEFINES
#include <math.h>

decl_result(SharedShaderPtr, Shader*);
static ResultSharedShaderPtr shared_shader_get(void);
static void shared_shader_drop(void);

int create_plant_vertices_array(
    const Transform *transform,
    Vec *dst_data,
    Vec *dst_indices,
    const PlantEdge *edge
);

int create_plant_vertices_array(
    const Transform *transform,
    Vec *dst_data, // data format poz x, y, x; color r, g, b; normal x, y, z;
    Vec *dst_indices,
    const PlantEdge *edge
) {
    #define FLOATS_PER_POS    3
    #define FLOATS_PER_COLOR  3
    #define FLOATS_PER_NORMAL 3
    #define FLOATS_PER_VERTEX (FLOATS_PER_POS + FLOATS_PER_COLOR + FLOATS_PER_NORMAL)

    const Vec3 vertices[] = {
        vec3( edge->start_radius, 0.0f,       edge->start_radius),
        vec3( edge->start_radius, 0.0f,      -edge->start_radius),
        vec3( edge->end_radius,   edge->len,  edge->end_radius  ),
        vec3( edge->end_radius,   edge->len, -edge->end_radius  ),

        vec3( edge->start_radius, 0.0f,      -edge->start_radius),
        vec3(-edge->start_radius, 0.0f,      -edge->start_radius),
        vec3( edge->end_radius,   edge->len, -edge->end_radius  ),
        vec3(-edge->end_radius,   edge->len, -edge->end_radius  ),

        vec3(-edge->start_radius, 0.0f,      -edge->start_radius),
        vec3(-edge->start_radius, 0.0f,       edge->start_radius),
        vec3(-edge->end_radius,   edge->len, -edge->end_radius  ),
        vec3(-edge->end_radius,   edge->len,  edge->end_radius  ),

        vec3(-edge->start_radius, 0.0f,       edge->start_radius),
        vec3( edge->start_radius, 0.0f,       edge->start_radius),
        vec3(-edge->end_radius,   edge->len,  edge->end_radius  ),
        vec3( edge->end_radius,   edge->len,  edge->end_radius  ),
    };
    const Vec3 colors[] = {
        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),

        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),

        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),

        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->start_color.x, edge->start_color.y, edge->start_color.z),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  ),
        vec3(edge->end_color.x,   edge->end_color.y,   edge->end_color.z  )
    };
    const size_t neighbors_vertices[][2] = {
        {1 +  0, 2 +  0},
        {2 +  0, 0 +  0},
        {0 +  0, 1 +  0},
        {2 +  0, 1 +  0},

        {1 +  4, 2 +  4},
        {2 +  4, 0 +  4},
        {0 +  4, 1 +  4},
        {2 +  4, 1 +  4},

        {1 +  8, 2 +  8},
        {2 +  8, 0 +  8},
        {0 +  8, 1 +  8},
        {2 +  8, 1 +  8},

        {1 + 12, 2 + 12},
        {2 + 12, 0 + 12},
        {0 + 12, 1 + 12},
        {2 + 12, 1 + 12}
    };
    const const GLuint indices[] = {
        0 +  0, 1 +  0, 2 +  0,
        1 +  0, 2 +  0, 3 +  0,

        0 +  4, 1 +  4, 2 +  4,
        1 +  4, 2 +  4, 3 +  4,

        0 +  8, 1 +  8, 2 +  8,
        1 +  8, 2 +  8, 3 +  8,

        0 + 12, 1 + 12, 2 + 12,
        1 + 12, 2 + 12, 3 + 12
    };

    const int vertex_cnt = sizeof(vertices) / sizeof(*vertices);
    GLuint ix_base = (GLuint)vec_len(dst_data) / FLOATS_PER_VERTEX;
    for (int i = 0; i < vertex_cnt; i++) {
        Vec3 points[3];
        points[0] = transform_point(transform, vertices[i]);
        points[1] = transform_point(transform, vertices[neighbors_vertices[i][0]]);
        points[2] = transform_point(transform, vertices[neighbors_vertices[i][1]]);

        Vec3 vec_a = vec3_sub(points[1], points[0]);
        Vec3 vec_b = vec3_sub(points[2], points[0]);
        Vec3 normal = vec3_normalize(vec3_cross(vec_a, vec_b));

        reci(vec_push(dst_data, &points[0].x), "Failed to add point x" );
        reci(vec_push(dst_data, &points[0].y), "Failed to add point y" );
        reci(vec_push(dst_data, &points[0].z), "Failed to add point z" );
        reci(vec_push(dst_data, &colors[i].x), "Failed to add color r" );
        reci(vec_push(dst_data, &colors[i].y), "Failed to add color g" );
        reci(vec_push(dst_data, &colors[i].z), "Failed to add color b" );
        reci(vec_push(dst_data, &normal.x   ), "Failed to add normal x");
        reci(vec_push(dst_data, &normal.y   ), "Failed to add normal y");
        reci(vec_push(dst_data, &normal.z   ), "Failed to add normal z");
    }
    const int indices_cnt = sizeof(indices) / sizeof(*indices);
    for (int i = 0; i < indices_cnt; i++) {
        GLuint ix = indices[i] + ix_base;
        reci(vec_push(dst_indices, &ix), "Failed to add index");
    }

    for (size_t i = 0; i < edge->next_cnt; i++) {
        Transform t = transform_translate(transform, vec3(0, edge->len, 0));
        reci(create_plant_vertices_array(&t, dst_data, dst_indices, &edge->next[i]),
             "Failed to add next edge");
    }
    return 0;
}

ResultPlant plant_new(Vec2 pos) {
    Plant plant;

    PlantEdge edge_buff[3];
    edge_buff[0].start_radius = 0.1f;
    edge_buff[0].start_color = vec3(0.6f, 0.3f, 0.0f);
    edge_buff[0].end_radius = 0.1f;
    edge_buff[0].end_color = vec3(0.65f, 0.35f, 0.0f);
    edge_buff[0].len = 1.0f;
    edge_buff[0].next_cnt = 1;
    edge_buff[0].next = &edge_buff[1];

    edge_buff[1].start_radius = 0.2f;
    edge_buff[1].start_color = vec3(0.0f, 1.0f, 0.0f);
    edge_buff[1].end_radius = 0.5f;
    edge_buff[1].end_color = vec3(0.0f, 1.0f, 0.0f);
    edge_buff[1].len = 0.5f;
    edge_buff[1].next_cnt = 1;
    edge_buff[1].next = &edge_buff[2];

    edge_buff[2].start_radius = 0.5f;
    edge_buff[2].start_color = vec3(0.0f, 1.0f, 0.0f);
    edge_buff[2].end_radius = 0.2f;
    edge_buff[2].end_color = vec3(0.0f, 1.0f, 0.0f);
    edge_buff[2].len = 0.5f;
    edge_buff[2].next_cnt = 0;
    edge_buff[2].next = NULL;

    Transform t = transform_new();
    plant.transform = transform_translate(&t, vec3(pos.x, 0, pos.y));
    plant.shader = try(shared_shader_get(), (ResultPlant)Err(), "Failed to get shader");

    GLfloat data_buff[1024];
    Vec data = vec_from_static(sizeof(*data_buff), data_buff,
                               sizeof(data_buff) / sizeof(*data_buff));
    GLuint indices_buff[1024];
    Vec indices = vec_from_static(sizeof(*indices_buff), indices_buff,
                                       sizeof(indices_buff) / sizeof(*indices_buff));

    rci(create_plant_vertices_array(&t, &data, &indices, edge_buff),
        (ResultPlant)Err(), "Failed to create plant drawing data");

    GLuint vbo, vao, ibo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei)vec_size_bytes(&data), vec_get(&data, 0),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)vec_size_bytes(&indices), vec_get(&indices, 0),
                 GL_STATIC_DRAW);

    GLsizei data_step = 9 * sizeof(GLfloat);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data_step, (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data_step, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, data_step, (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    plant.vertex_buff = vbo;
    plant.vertex_arrays = vao;
    plant.index_buff = ibo;
    plant.index_cnt = (GLsizei)vec_len(&indices);
    return (ResultPlant)Ok(plant);
}

void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform) {
    (void)dctx;
    this->transform = transform_rotate(&this->transform, 0.01f, vec3(0, 1, 0));
    shader_use(this->shader);
    Mat4 mvp = transform_get_mvp(transform, &this->transform);
    Mat4 model = transform_to_mat(&this->transform);
    shader_set_mat4(this->shader, "mvp", &mvp);
    shader_set_mat4(this->shader, "model", &model);
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
        "layout (location = 2) in vec3 aNormal;\n"
        "uniform mat4 mvp;\n"
        "uniform mat4 model;\n"
        "out vec3 FragColor;\n"
        "out vec3 Normal;\n"
        "out vec3 FragPos;\n"
        "void main() {\n"
            "gl_Position = mvp * vec4(aPos, 1.0);\n"
            "FragPos = vec3(model * vec4(aPos, 1.0));\n"
            "FragColor = aColor;\n"
            "Normal = (model * vec4(aNormal, 0.0)).xyz;\n"
        "}",
        "#version 330 core\n"
        "in vec3 FragColor;\n"
        "in vec3 Normal;\n"
        "in vec3 FragPos;\n"
        "out vec4 color;\n"
        "void main() {\n"
            "vec3 light_pos = vec3(-100, 10, 0);\n"
            "vec3 light_color = vec3(0.5, 0.5, 0.5);\n"
            "vec3 embedded = vec3(0.5, 0.5, 0.5);\n"
            "\n"
            "vec3 norm = normalize(Normal);\n"
            "vec3 lightDir = normalize(light_pos - FragPos);\n"
            "float diff = max(dot(norm, lightDir), 0.0);\n"
            "vec3 diffuse = diff * light_color;\n"
            "vec3 result = (embedded + diffuse) * FragColor.rgb;\n"
            "color = vec4(result, 1.0);\n"
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
