# ifndef STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_IMPLEMENTATION
# include <includes/stb_image.h>
#endif
#include <includes/Texture.hpp>

Texture::Texture(std::string fileName, GLenum format) : m_ID(0), m_width(0), m_height(0), m_nrChannels(0)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    // Configure the wrapping/filtering options (on the bound texture object)
    // S and T are the X and Y coordinates of textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    // Minifying and magnifying filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// GL_NEAREST, GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// GL_NEAREST, GL_LINEAR
    // Generate the texture from image
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically
    unsigned char *data = stbi_load(fileName.c_str(), &m_width, &m_height, &m_nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(EXIT_FAILURE) ;
    }
    // Free the image memory
    stbi_image_free(data);
}   

Texture::Texture(const Texture &other) : m_ID(0), m_width(0), m_height(0), m_nrChannels(0)
{
    *this = other;
}

Texture &Texture::operator=(const Texture &other)
{
    if (this != &other)
    {
        m_ID = other.m_ID;
        m_width = other.m_width;
        m_height = other.m_height;
        m_nrChannels = other.m_nrChannels;
    }
    return (*this);
}

Texture::~Texture(void) {}



// Getters

unsigned int    Texture::getID(void) const
{
    return (m_ID);
}


// Public

void    Texture::bind(unsigned int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void    Texture::unbind(void) const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void    Texture::del(void) const
{
    glDeleteTextures(1, &m_ID);
}