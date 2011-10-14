/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Controller.h"

g2Controller::g2Controller(g2Controller* Parent, g2Theme* MainTheme)
{
    // Initialize to visible, white, no alpha
    Alpha = 1.0f;
    R = G = B = 1.0f;
    IsVisible = true;
    ControllerState = g2ControllerState_None;
    IsDisabled = false;
    
    // Default position to the origin relative to the parent
    pX = pY = 0;
    
    // Save parent and theme
    ParentObject = Parent;
    ParentTheme = MainTheme;
    
    // Default to no callback
    PressedCallback = 0;
    
    // Nothing is active by default
    IsActive = false;
    
    // Add self to parent
    if(Parent != NULL)
        Parent->ChildObjects.push(this);
}

g2Controller::~g2Controller()
{
    // Release each child
    while(!ChildObjects.empty())
    {
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        delete Child;
    }
    
    // No need to release self if we are the root
    if(ParentObject == NULL)
        return;
    
    // Release self from parent
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Is this its own class, if so leave it popped and stop
        if(Child == this)
            break;
        
        // Put back
        ChildObjects.push(Child);
    }
    
    // All done with releasing self from parent
}

void g2Controller::SetVisibility(bool Visible)
{
    IsVisible = Visible;
}

bool g2Controller::GetVisibility()
{
    return IsVisible;
}

void g2Controller::SetColor(float r, float g, float b, float a)
{
    // Min/max bounds to [0.0, 1.0]
    R = fmax(fmin(r, 1.0f), 0.0f);
    G = fmax(fmin(g, 1.0f), 0.0f);
    B = fmax(fmin(b, 1.0f), 0.0f);
    Alpha = fmax(fmin(a, 1.0f), 0.0f);
}

void g2Controller::GetColor(float* r, float* g, float* b, float* a)
{
    if(r != NULL)
        *r = R;
    if(g != NULL)
        *g = G;
    if(b != NULL)
        *b = B;
    if(a != NULL)
        *a = Alpha;
}

void g2Controller::SetDisabled(bool Disabled)
{
    IsDisabled = Disabled;
}

bool g2Controller::GetDisabled()
{
    return IsDisabled;
}

void g2Controller::SetPos(int x, int y)
{
    // Save the new offset
    pX = x;
    pY = y;
}

void g2Controller::GetPos(int* x, int* y)
{
    // Post local offsets
    if(x != NULL)
        *x = pX;
    if(y != NULL)
        *y = pY;
}

bool g2Controller::GetActive()
{
    return IsActive;
}

g2Controller* g2Controller::GetController(int x, int y)
{
    // Assume nothing intersects
    g2Controller* ActiveController = NULL;
    
    // Check all children, do we interest?
    // We go through all of them as we don't want to change
    // the ordering which is important to rendering
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Check but stop once at least one is found
        if(ActiveController == NULL)
            ActiveController = Child->GetController(x, y);
        
        // Put back
        ChildObjects.push(Child);
    }
    
    // No children have an intersection, as the parent do we intersect?
    if(ActiveController == NULL && InController(x, y))
        ActiveController = this;
    
    // All done
    return ActiveController;
}

void g2Controller::SetCallback(__g2CallBack(PressedCallback))
{
    this->PressedCallback = PressedCallback;
}

void g2Controller::Update(float dT)
{
    // Allow the user to overload as needed...
    
    // Suppress warning
    dT = dT;
}

void g2Controller::Render(int x, int y)
{
    // Allow the user to overload as needed...
}

bool g2Controller::InController(int x, int y)
{
    // Suppress warning
    y = x = y;
    
    // Allow the user to overload as needed...
    return false;
}

void g2Controller::WindowResizeEvent(int NewWidth, int NewHeight)
{
    // Suppress warning
    NewHeight = NewWidth = NewHeight;
    
    // Allow the user to overload as needed...
}

void g2Controller::KeyEvent(unsigned char key, bool IsSpecial)
{
    // Suppress warning
    key = key;
    IsSpecial = IsSpecial;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Suppress warning
    button = g2MouseButton_Left;
    state = g2MouseClick_Down;
    x = y;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseHover(int x, int y)
{
    // Suppress warning
    x = y;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseDrag(int x, int y)
{
    // Suppress warning
    x = y;
    
    // Allow the user to overload as needed...
}

g2Theme* g2Controller::GetTheme()
{
    return ParentTheme;
}

g2Controller* g2Controller::GetParent()
{
    return ParentObject;
}

g2ControllerState g2Controller::GetControllerState()
{
    return ControllerState;
}

void g2Controller::DrawComponent(int DestX, int DestY, g2ThemeElement ElementType)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // Get the texture points and default component size
    float tx, ty, tw, th;
    int width, height;
    GLuint textID;
    bool IsFound = GetTheme()->GetComponent(ElementType, &tx, &ty, &tw, &th, &width, &height, &textID);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", (int)ElementType);
    
    // Draw
    DrawComponent(DestX, DestY, width, height, tx, ty, tw, th, textID);
}

void g2Controller::DrawComponent(int DestX, int DestY, int DestW, int DestH, g2ThemeElement ElementType)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // Get the texture points and default component size
    float tx, ty, tw, th;
    GLuint textID;
    bool IsFound = GetTheme()->GetComponent(ElementType, &tx, &ty, &tw, &th, NULL, NULL, &textID);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", (int)ElementType);
    
    // Draw
    DrawComponent(DestX, DestY, DestW, DestH, tx, ty, tw, th, textID);
}

void g2Controller::DrawComponent(int DestX, int DestY, const char* ElementName)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // Get the texture points and default component size
    float tx, ty, tw, th;
    int width, height;
    bool IsFound = GetTheme()->GetComponent(ElementName, &tx, &ty, &tw, &th, &width, &height);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %s) texture information", ElementName);
    
    // Draw
    DrawComponent(DestX, DestY, width, height, tx, ty, tw, th);
}

void g2Controller::DrawComponent(int DestX, int DestY, int DestW, int DestH, const char* ElementName)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // Get the texture points and default component size
    float tx, ty, tw, th;
    bool IsFound = GetTheme()->GetComponent(ElementName, &tx, &ty, &tw, &th, NULL, NULL);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", ElementName);
    
    // Draw
    DrawComponent(DestX, DestY, DestW, DestH, tx, ty, tw, th);
}

void g2Controller::DrawComponent(int DestX, int DestY, int DestW, int DestH, float SrcX, float SrcY, float SrcW, float SrcH, int TextID)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // If the texture ID is invalid then switch to theme texture ID
    if(TextID < 0)
        TextID = GetTheme()->GetTextureID();
    
    // Set the current color and alpha
    glColor4f(R, G, B, Alpha);
    
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextID); 
    
    // Draw at this position
    glBegin(GL_QUADS);
        glTexCoord2f(SrcX, SrcY);
        glVertex2f(DestX + 0, DestY + 0);
        
        glTexCoord2f(SrcX, SrcY + SrcH);
        glVertex2f(DestX + 0, DestY + DestH);
        
        glTexCoord2f(SrcX + SrcW, SrcY + SrcH);
        glVertex2f(DestX + DestW, DestY + DestH);
        
        glTexCoord2f(SrcX + SrcW, SrcY);
        glVertex2f(DestX + DestW, DestY + 0);
    glEnd();
    
    // Release texture
    glDisable(GL_TEXTURE_2D);
}

void g2Controller::DrawCharacter(int DestX, int DestY, char Character)
{
    DrawCharacter(DestX, DestY, 1.0f, 1.0f, Character);
}

void g2Controller::DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, char Character)
{
    DrawCharacter(DestX, DestY, ScaleW, ScaleH, R, G, B, Alpha, Character);
}

void g2Controller::DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, float R, float G, float B, float A, char Character)
{
    // Are we allowed to draw?
    if(!IsVisible)
        return;
    
    // Set the current color and alpha
    // (Note we are using the args, not the class members, as values)
    glColor4f(R, G, B, A);
    
    // Get the texture points
    float tx, ty, tw, th;
    int width, height;
    GLuint textID;
    GetTheme()->GetCharacter(Character, &tx, &ty, &tw, &th, &width, &height, &textID);
    
    // Scale
    width = int(float(width) * ScaleW);
    height = int(float(height) * ScaleH);
    
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textID); 
    
    // Draw at this position
    glBegin(GL_QUADS);
        glTexCoord2f(tx, ty);
        glVertex2f(DestX + 0, DestY + 0);
        
        glTexCoord2f(tx, ty + th);
        glVertex2f(DestX + 0, DestY + height);
        
        glTexCoord2f(tx + tw, ty + th);
        glVertex2f(DestX + width, DestY + height);
        
        glTexCoord2f(tx + tw, ty);
        glVertex2f(DestX + width, DestY + 0);
    glEnd();
    
    // Release texture
    glDisable(GL_TEXTURE_2D);
}

void g2Controller::__Update(float dT)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Update self
    Update(dT);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update
        Child->__Update(dT);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__Render(int x, int y)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Render self
    Render(x, y);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Render (note the offset for the child)
        int OffsetX, OffsetY;
        Child->GetPos(&OffsetX, &OffsetY);
        Child->__Render(x + OffsetX, y + OffsetY);
        
        // Put back
        ChildObjects.push(Child);
    }
    
    // After a full render cycle, reset the mouse state so we
    // don't keep full-clicking
    if(ControllerState == g2ControllerState_Clicked)
        ControllerState = g2ControllerState_None;
}

void g2Controller::__WindowResizeEvent(int NewWidth, int NewHeight)
{
    // Update window self
    WindowResizeEvent(NewWidth, NewHeight);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child window event
        Child->__WindowResizeEvent(NewWidth, NewHeight);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__KeyEvent(unsigned char key, bool IsSpecial)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Update key event
    KeyEvent(key, IsSpecial);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child key event
        Child->__KeyEvent(key, IsSpecial);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__MouseHover(int x, int y)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Update mouse hovering
    MouseHover(x, y);
    
    // Maintain the pressed state
    if(InController(x, y) && ControllerState == g2ControllerState_Pressed)
        __MouseDrag(x, y);
    if(!InController(x, y))
        ControllerState = g2ControllerState_None;
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child window hover
        Child->__MouseHover(x, y);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Update mouse click
    MouseClick(button, state, x, y);
    
    // Are we in this object's volume and do we have a full left-click?
    if(InController(x, y) && button == g2MouseButton_Left && state == g2MouseClick_Down)
        ControllerState = g2ControllerState_Pressed;
    // Else, if there is a mouse release AND we are coming from a pressed state....
    else if(InController(x, y) && button == g2MouseButton_Left && state == g2MouseClick_Up && ControllerState == g2ControllerState_Pressed)
        ControllerState = g2ControllerState_Clicked;
    // Else, reset to either hover or none...
    else if(InController(x, y))
        ControllerState = g2ControllerState_Hover;
    else
        ControllerState = g2ControllerState_None;
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child window event
        Child->__MouseClick(button, state, x, y);
        
        // Put back
        ChildObjects.push(Child);
    }
    
    // Execute callback
    if(!GetDisabled() && GetControllerState() == g2ControllerState_Clicked && PressedCallback != 0)
        PressedCallback(this);
}

void g2Controller::__MouseDrag(int x, int y)
{
    // Ignore if not visible
    if(!GetVisibility())
        return;
    
    // Update mouse drag
    MouseDrag(x, y);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child mouse drags
        Child->__MouseDrag(x, y);
        
        // Put back
        ChildObjects.push(Child);
    }
}
