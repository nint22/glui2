/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
***************************************************************/

#include "g2Images.h"

// Internal allocations of images
std::map<std::string, __g2Image> __g2ImageList;
typedef std::map<std::string, __g2Image>::iterator __g2ImagesListIt;

// Load any given image
GLuint g2LoadImage(const char* ImagePath, int* Width, int* Height, int* Channels, bool Wrap)
{
    // Does the image already exist in the dictionary?
    __g2ImagesListIt Result = __g2ImageList.find(std::string(ImagePath));
    
    // If nothing is found...
    if(Result == __g2ImageList.end())
    {
        // Create a new image instance
        __g2Image Image;
        strcpy(Image.FileName, ImagePath);
        
        // Allocate image; fail out on error
        unsigned char* DataBuffer = stbi_load(ImagePath, &Image.Width, &Image.Height, &Image.Channels, 4);
        if(DataBuffer == NULL)
            return -1;
        
        // Allocate an OpenGL texture
        glGenTextures(1, &Image.GlTextureID);
        glBindTexture(GL_TEXTURE_2D, Image.GlTextureID);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.Width, Image.Height, Image.Channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, DataBuffer);
        
        // Release internal buffer
        stbi_image_free(DataBuffer);
        
        // Set certain properties of texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
        // Wrap texture around
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap ? GL_REPEAT : GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap ? GL_REPEAT : GL_CLAMP);
        
        // Done setting image parameters
        glDisable(GL_TEXTURE_2D);
        
        // Place in post-back as desired
        if(Width != NULL)
            *Width = Image.Width;
        if(Height != NULL)
            *Height = Image.Height;
        if(Channels != NULL)
            *Channels = Image.Channels;
        
        // Save to dictionary
        __g2ImageList.insert(std::pair<std::string, __g2Image>(std::string(Image.FileName), Image));
        return Image.GlTextureID;
    }
    
    // Return what was already known
    return Result->second.GlTextureID;
}

void g2LoadImageBuffer(const char* ImagePath, unsigned char** OutBuffer, int* Width, int* Height, int* Channels)
{
    // Create temporary retainers
    int TempWidth, TempHeight, TempChannels;
    
    // Allocate image; fail out on error
    *OutBuffer = stbi_load(ImagePath, &TempWidth, &TempHeight, &TempChannels, 4);
    if(Width != NULL)
        *Width = TempWidth;
    if(Height != NULL)
        *Height = TempHeight;
    if(Channels != NULL)
        *Channels = TempChannels;
}

void g2UnloadImageBuffer(unsigned char* OutBuffer)
{
    stbi_image_free(OutBuffer);
}
