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
    
    // Load the theme image and font files
    char* TextureName = NULL;
    int Channels;
    
    Configuration.GetValue("general", "image", &TextureName);
    TextureID = g2LoadImage(TextureName, &TextureWidth, &TextureHeight, &Channels);
    g2Assert(TextureID > 0, "Unable to load image: %s", TextureName);
    
    Configuration.GetValue("general", "font", &TextureName);
    CharacterMapID = g2LoadImage(TextureName, &CharacterMapWidth, &CharacterMapHeight, &Channels);
    g2Assert(CharacterMapID > 0, "Unable to load image: %s", TextureName);
    
    // Get the character map image buffer
    unsigned char* CharacterImageBuffer = NULL;
    g2LoadImageBuffer(TextureName, &CharacterImageBuffer, NULL, NULL, &Channels);
    g2Assert(CharacterImageBuffer != NULL, "Unable to load image as a direct-buffer in main memory: %s", TextureName);
    g2Assert(Channels == 4, "The character bitmap must use 4 channels (RGBA): %s", TextureName);
    
    // Compute the width of each character in the character bitmap
    int CharacterWidth = CharacterMapWidth / 16;
    int CharacterHeight = CharacterMapHeight / 16;
    for(int y = 0; y < 16; y++)
    for(int x = 0; x < 16; x++)
    {
        // Default to full width
        CharacterWidths[y][x] = CharacterWidth;
        
        // Keep checking each from right to left
        for(int i = CharacterWidth - 1; i >= 0; i--)
        {
            // Keep going down
            bool CollisionFound = false;
            for(int j = 0; j < CharacterHeight; j++)
            {
                // Get the alpha value, offset needed for 3 (alpha channel, last byte)
                unsigned char alpha = CharacterImageBuffer[((y * CharacterMapHeight * CharacterWidth + x * CharacterWidth) + j * CharacterMapWidth + i) * 4 + 3];
                if(alpha > 0)
                {
                    CollisionFound = true;
                    break;
                }
            }
            
            // If there is no collision or end of character width,
            // save this width in the character map
            if(CollisionFound == true)
            {
                CharacterWidths[y][x] = i + 1;
                break;
            }
        }
    }
    
    // Done working on the character map, release the data
    g2UnloadImageBuffer(CharacterImageBuffer);
    
    // One special exception: The ' ' (space) character should be about 25% of the max character width
    CharacterWidths[2][0] = int(float(CharacterWidth) * 0.25f);
}

bool g2Theme::GetComponent(g2ThemeElement Element, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Does the component exist in the dictionary?
    if(Element < 0 || Element >= g2ThemeElement_Count)
        return false;
    
    // Does the config file have this content?
    const char* ElementName = g2ThemeElement_Names[(int)Element];
    if(!GetComponent(ElementName, tSrcX, tSrcY, tSrcWidth, tSrcHeight, width, height, textID))
        return false;
    
    // All done
    return true;
}

bool g2Theme::GetComponent(const char* ElementName, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Make sure all pointers are valid
    g2Assert(ElementName != NULL, "Given g2Theme element name is NULL.");
    
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
    if(tSrcX != NULL)
        *tSrcX = float(tX) / float(TextureWidth);
    if(tSrcY != NULL)
        *tSrcY = float(tY) / float(TextureHeight);
    if(tSrcWidth != NULL)
        *tSrcWidth = float(tWidth) / float(TextureWidth);
    if(tSrcHeight != NULL)
        *tSrcHeight = float(tHeight) / float(TextureHeight);
    
    // Post back the size and texture ID
    if(width != NULL)
        *width = tWidth;
    if(height != NULL)
        *height = tHeight;
    if(textID != NULL)
        *textID = TextureID;
    
    // All done
    return true;
}

bool g2Theme::GetComponentSize(g2ThemeElement Element, int* width, int* height)
{
    // Is this index in the list of valid
    if(Element < 0 || Element >= g2ThemeElement_Count)
        return false;
    
    // Does the config file have this content?
    const char* ElementName = g2ThemeElement_Names[(int)Element];
    return GetComponentSize(ElementName, width, height);
}

bool g2Theme::GetComponentSize(const char* ElementName, int* width, int* height)
{
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
    if(width != NULL)
        *width = tWidth;
    if(height != NULL)
        *height = tHeight;
    return true;
}

void g2Theme::GetCharacter(char character, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID)
{
    // Calculate the x and y positions
    // Low nibble is x-axis, high nibble is y axis
    // Note to self: would it be faster to do a bit-wise manipulation?
    // sourceX = (character & 0xf0) >> 4 to cast a byte's higher nibble to lower nibble
    int w, h;
    GetCharacterSize(character, &w, &h);
    if(width != NULL)
        *width = w;
    if(height != NULL)
        *height= h;
    
    if(tSrcX != NULL)
        *tSrcX = float((character % 16) * (CharacterMapWidth / 16)) / float(CharacterMapWidth);
    if(tSrcY != NULL)
        *tSrcY = float((character / 16) * (CharacterMapHeight / 16)) / float(CharacterMapHeight);
    
    if(tSrcWidth != NULL)
        *tSrcWidth = float(w) / float(CharacterMapWidth);
    if(tSrcHeight != NULL)
        *tSrcHeight = float(h) / float(CharacterMapHeight);
    
    // Set the texture to the character map
    if(textID != NULL)
        *textID = CharacterMapID;
}

void g2Theme::GetCharacterSize(char character, int* width, int* height)
{
    if(width != NULL)
        *width = CharacterWidths[character / 16][character % 16];
    if(height != NULL)
        *height = CharacterMapHeight / 16;
}

int g2Theme::GetCharacterHeight()
{
    return CharacterMapHeight / 16;
}

void g2Theme::GetTextureSize(int* Width, int* Height)
{
    if(Width != NULL)
        *Width = TextureWidth;
    if(Height != NULL)
        *Height = TextureHeight;
}

GLuint g2Theme::GetTextureID()
{
    return TextureID;
}

void g2Theme::GetCharacterMapSize(int* Width, int* Height)
{
    if(Width != NULL)
        *Width = CharacterMapWidth;
    if(Height != NULL)
        *Height = CharacterMapHeight;
}

GLuint g2Theme::GetCharacterMapID()
{
    return CharacterMapID;
}
