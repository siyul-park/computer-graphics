#ifndef OPENGLBOILERPLATE_TEXTURE2D_INC_H
#define OPENGLBOILERPLATE_TEXTURE2D_INC_H

#include "texture2d.h"
#include "type.h"

template<class T>
gl::Texture2d<T>::Texture2d(T *data, Texture2dSize size, int bind_type) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, bind_type, size.x, size.y, 0, GL_RGBA, GL_FLOAT, getType<T>());
}

template<class T>
gl::Texture2d<T>::~Texture2d() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

#endif //OPENGLBOILERPLATE_TEXTURE2D_INC_H
