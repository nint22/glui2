/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
***************************************************************/

#include "g2Theme.h"

g2Theme::g2Theme()
{
    // Do nothing...
}

g2Theme::~g2Theme()
{
    // Release nothing...
}

void g2Theme::Load(const char* ThemeFile)
{
    // Attempt to load
    g2Assert(ThemeFile != NULL, "Give theme file is null");
    Configuration.LoadFile(ThemeFile);
    
    // Load both image and character map
    for(int i = 0; i < 2; i++)
    {
        // Get the texture name
        char* TextureName = NULL;
        if(i == 0)
            Configuration.GetValue("general", "image", &TextureName);
        else if(i == 1)
            Configuration.GetValue("general", "font", &TextureName);
        
        // Load the texture itself into memory
        // Attempt to load the texture via soil (Noe the multiply_alpha flag is critial)
        int TextureID = SOIL_load_OGL_texture(TextureName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);
        
        // Make sure the loaded image is valid
        g2Assert(TextureID > 0, "Unable to load image: %s", TextureName);
        
        // Initialize texture
        glEnable(GL_TEXTURE_2D); // Enable 2D texturing
        glBindTexture(GL_TEXTURE_2D, TextureID); // Set as the current texture
        
        // Get the current texture size
        if(i == 0)
        {
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &TextureWidth);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &TextureHeight);
        }
        else if(i == 1)
        {
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &CharacterMapWidth);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &CharacterMapHeight);
        }
        
        // Set certain properties of texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // Remove edge lines
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // Done setting image parameters
        glDisable(GL_TEXTURE_2D);
        
        // Save texture ID
        if(i == 0)
            this->TextureID = TextureID;
        else if(i == 1)
            this->CharacterMapID = TextureID;
    }
}

bool g2Theme::GetComponent(g2ThemeElement Element, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Is this index in the list of valid
    if((int)Element < 0 || (int)Element >= g2ThemeElement_Count)
        return false;
    
    // Make sure all pointers are valid
    g2Assert(tSrcX != NULL && tSrcY != NULL && tSrcWidth != NULL && tSrcHeight != NULL && width != NULL && height != NULL && textID, "Given texture coordinates, texture size, and/or texture IDs are null.");
    
    // Does the component exist in the dictionary?
    if((int)Element < 0 || (int)Element >= g2ThemeElement_Count)
        return false;
    
    // Does the config file have theis content?
    const char* ElementName = g2ThemeElement_Names[(int)Element];
    if(!GetComponent(ElementName, tSrcX, tSrcY, tSrcWidth, tSrcHeight, width, height, textID))
        return false;
    
    // All done
    return true;
}

bool g2Theme::GetComponent(const char* ElementName, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Make sure all pointers are valid
    g2Assert(tSrcX != NULL && tSrcY != NULL && tSrcWidth != NULL && tSrcHeight != NULL && width != NULL && height != NULL && textID, "Given texture coordinates, texture size, and/or texture IDs are null.");
    
    // Create the needed point buffer and size buffer key-names
    char* PointBuffer = NULL;
    char* SizeBuffer = NULL;
    
    // Get the tuple-pair values for each
    if(Configuration.GetValue(ElementName, "point", &PointBuffer) == false)
        return false;
    if(Configuration.GetValue(ElementName, "size", &SizeBuffer) == false)
        return false;
    
    // Convert to points and size (if possible)
    int tX, tY, tWidth, tHeight;
    if(sscanf(PointBuffer, "%d %d", &tX, &tY) != 2)
        return false;
    if(sscanf(SizeBuffer, "%d %d", &tWidth, &tHeight) != 2)
        return false;
    
    // Convert and post-back to normalized
    *tSrcX = float(tX) / float(TextureWidth);
    *tSrcY = float(tY) / float(TextureHeight);
    *tSrcWidth = float(tWidth) / float(TextureWidth);
    *tSrcHeight = float(tHeight) / float(TextureHeight);
    
    // Post back the size and texture ID
    *width = tWidth;
    *height = tHeight;
    *textID = TextureID;
    
    // All done
    return true;
}

bool g2Theme::GetComponentSize(g2ThemeElement Element, int* width, int* height)
{
    // Check buffers
    g2Assert(width != NULL && height != NULL, "Given width and/or height buffers are NULL.");
    
    // Is this index in the list of valid
    if((int)Element < 0 || (int)Element >= g2ThemeElement_Count)
        return false;
    
    // Does the config file have this content?
    const char* ElementName = g2ThemeElement_Names[(int)Element];
    return GetComponentSize(ElementName, width, height);
}

bool g2Theme::GetComponentSize(const char* ElementName, int* width, int* height)
{
    // Check buffers
    g2Assert(width != NULL && height != NULL, "Given width and/or height buffers are NULL.");
    
    // Create the needed point buffer and size buffer key-names
    char* SizeBuffer = NULL;
    
    // Get the tuple-pair values for each
    if(Configuration.GetValue(ElementName, "size", &SizeBuffer) == false)
        return false;
    
    // Convert to points and size (if possible)
    int tWidth, tHeight;
    if(sscanf(SizeBuffer, "%d %d", &tWidth, &tHeight) != 2)
        return false;
    
    // Save and post-back
    *width = tWidth;
    *height = tHeight;
    return true;
}

void g2Theme::GetCharacter(char character, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Check buffers
    g2Assert(tSrcX != NULL && tSrcY != NULL && tSrcWidth != NULL && tSrcHeight != NULL && width != NULL && height != NULL && textID != NULL, "Given width and/or height buffers are NULL.");
    
    // Calculate the x and y positions
    // Low nibble is x-axis, high nibble is y axis
    // Note to self: would it be faster to do a bit-wise manipulation?
    // sourceX = (character & 0xf0) >> 4 to cast a byte's higher nibble to lower nibble
    int w = *width = CharacterMapWidth / 16;
    int h = *height = CharacterMapHeight / 16;
    
    *tSrcX = float((character % 16) * w) / float(CharacterMapWidth);
    *tSrcY = float((character / 16) * h) / float(CharacterMapHeight);
    
    *tSrcWidth = float(w) / float(CharacterMapWidth);
    *tSrcHeight = float(h) / float(CharacterMapHeight);
    
    // Set the texture to the character map
    *textID = CharacterMapID;
}

void g2Theme::GetCharacterSize(int* width, int* height)
{
    // Check buffers
    g2Assert(width != NULL && height != NULL, "Given width and/or height buffers are NULL.");
    
    *width = CharacterMapWidth / 16;
    *height = CharacterMapHeight / 16;
}
