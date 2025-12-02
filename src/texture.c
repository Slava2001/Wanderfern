#include "texture.h"
#include "stb_image.h"

ResultTexture texture_load(const char *path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    rci(!data, (ResultTexture)Err(),
        "Failed to load texture: %s, Error: %s", path, stbi_failure_reason());
    GLint type;
    switch (channels) {
    case 3:
        type = GL_RGB;
        break;
    case 4:
        type = GL_RGBA;
        break;
    default:
        stbi_image_free(data);
        loge("Failed to load image: %s, unexpected channel count: %d", path, channels);
        return (ResultTexture)Err();
    }

    Texture *texture = (Texture *)tryc(mem_alloc(sizeof(Texture)), (ResultTexture)Err(),
                                       { stbi_image_free(data); }, "Failed to allocate memory");
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, (GLenum)type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture->texture_id = texture_id;
    return (ResultTexture)Ok(texture);
}

void texture_drop(Texture *this) {
    glDeleteTextures(1, &this->texture_id);
    mem_free(this);
}

void texture_use(const Texture *this, GLuint slot_id) {
    glActiveTexture(slot_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
}
