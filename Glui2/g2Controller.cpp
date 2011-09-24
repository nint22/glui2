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
    x = y = 0;
    ControllerState = g2ControllerState_None;
    IsDisabled = false;
    
    // Save parent and theme
    ParentObject = Parent;
    ParentTheme = MainTheme;
    
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
        
        // Is this its own class, if so leave it poped and stop
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

void g2Controller::SetColor(float r, float g, float b)
{
    // Min/max bounds to [0.0, 1.0]
    R = fmax(fmin(r, 1.0f), 0.0f);
    G = fmax(fmin(g, 1.0f), 0.0f);
    B = fmax(fmin(b, 1.0f), 0.0f);
}

void g2Controller::GetColor(float* r, float*g, float* b)
{
    g2Assert(r != NULL, "Given red channel buffer is null");
    *r = R;
    
    g2Assert(g != NULL, "Given green channel buffer is null");
    *g = G;
    
    g2Assert(b != NULL, "Given blue channel buffer is null");
    *b = B;
}

void g2Controller::SetAlpha(float NewAlpha)
{
    // Min/max bounds to [0.0, 1.0]
    Alpha = fmax(fmin(NewAlpha, 1.0f), 0.0f);
}

float g2Controller::GetAlpha()
{
    return Alpha;
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
    // Find the new detla
    int dx = x - this->x;
    int dy = y - this->y;
    
    // Save for this position
    this->x = x;
    this->y = y;
    
    // Update all children by setting the offsets
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child mouse drags
        int xi, yi;
        Child->GetPos(&xi, &yi);
        Child->SetPos(xi + dx, yi + dy);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::GetPos(int* x, int* y)
{
    g2Assert(x != NULL && y != NULL, "Cannot set x and/or y because one or both of them are NULL.");
    *x = this->x;
    *y = this->y;
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
    
    // No children have an interesection, as the parent do we intersect?
    if(ActiveController == NULL && InController(x, y))
        ActiveController = this;
    
    // All done
    return ActiveController;
}

void g2Controller::Update(float dT)
{
    // Allow the user to overload as needed...
    
    // Supress warning
    dT = dT;
}

void g2Controller::Render()
{
    // Allow the user to overload as needed...
}

bool g2Controller::InController(int x, int y)
{
    // Supress warning
    x = y;
    
    // Allow the user to overload as needed...
    return false;
}

void g2Controller::WindowResizeEvent(int NewWidth, int NewHeight)
{
    // Supress warning
    NewWidth = NewHeight;
    
    // Allow the user to overload as needed...
}

void g2Controller::KeyEvent(unsigned char key)
{
    // Supress warning
    key = key;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Supress warning
    button = g2MouseButton_Left;
    state = g2MouseClick_Down;
    x = y;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseHover(int x, int y)
{
    // Supress warning
    x = y;
    
    // Allow the user to overload as needed...
}

void g2Controller::MouseDrag(int x, int y)
{
    // Supress warning
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
    if(!IsVisible || Alpha <= 0.0f)
        return;
    
    // Set the current color and alpha
    glColor4f(R, G, B, Alpha);
    
    // Get the texture points
    float tx, ty, tw, th;
    int width, height;
    GLuint textID;
    bool IsFound = GetTheme()->GetComponent(ElementType, &tx, &ty, &tw, &th, &width, &height, &textID);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", (int)ElementType);
    
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

void g2Controller::DrawCharacter(int DestX, int DestY, char Character)
{
    // Are we allowed to draw?
    if(!IsVisible || Alpha <= 0.0f)
        return;
    
    // Set the current color and alpha
    glColor4f(R, G, B, Alpha);
    
    // Get the texture points
    float tx, ty, tw, th;
    int width, height;
    GLuint textID;
    GetTheme()->GetCharacter(Character, &tx, &ty, &tw, &th, &width, &height, &textID);
    
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

void g2Controller::__Render()
{
    // Render self
    Render();
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Render
        Child->__Render();
        
        // Put back
        ChildObjects.push(Child);
    }
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

void g2Controller::__KeyEvent(unsigned char key)
{
    // Update key event
    KeyEvent(key);
    
    // Update all children
    int QueueSize = (int)ChildObjects.size();
    for(int i = 0; i < QueueSize; i++)
    {
        // Get child
        g2Controller* Child = ChildObjects.front();
        ChildObjects.pop();
        
        // Update child key event
        Child->__KeyEvent(key);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__MouseHover(int x, int y)
{
    // Update mouse click
    MouseHover(x, y);
    
    // Are we in this object's volume?
    if(InController(x, y))
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
        
        // Update child window hover
        Child->__MouseHover(x, y);
        
        // Put back
        ChildObjects.push(Child);
    }
}

void g2Controller::__MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Update mouse click
    MouseClick(button, state, x, y);
    
    // Are we in this object's volume and do we have a full left-click?
    if(InController(x, y) && button == g2MouseButton_Left && state == g2MouseClick_Down)
        ControllerState = g2ControllerState_Pressed;
    else if(button == g2MouseButton_Left && state == g2MouseClick_Up)
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
}

void g2Controller::__MouseDrag(int x, int y)
{
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
