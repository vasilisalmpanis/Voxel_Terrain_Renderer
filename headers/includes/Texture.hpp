#ifndef TEXTURE_HPP
#define TEXTURE_HPP
# include "Shader.hpp"
# include <glad/glad.h>

# include <iostream>

class Texture {
    public:
        Texture(std::string fileName, GLenum format);
        Texture(const Texture &other);
        Texture &operator=(const Texture &other);
        ~Texture(void);

        // Getters
        unsigned int    getID(void) const;

        // Public
        void            bind(unsigned int index) const;
        void            unbind(void) const;
        void            del(void) const;
    private:
        unsigned int    m_ID;
        int             m_width;
        int             m_height;
        int             m_nrChannels;
};

#endif