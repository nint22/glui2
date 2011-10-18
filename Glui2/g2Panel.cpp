/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2Panel.h"

g2Panel::g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors, const char* Title)
: g2Controller(Parent, MainTheme)
{
    // Save the given anchor points
    this->Anchors = Anchors;
    Width = Height = 256;
    
    Label = new g2Label(this, MainTheme);
    Label->SetColor(0, 0, 0);
    SetTitle(Title);
}

void g2Panel::SetAlignment(g2Anchor Anchors)
{
    this->Anchors = Anchors;
    WindowResizeEvent(WindowWidth, WindowHeight);
}

g2Anchor g2Panel::GetAlignment()
{
    return Anchors;
}

void g2Panel::SetTitle(const char* Title)
{
    // Set title
    Label->SetText(Title);
    
	// Center the text
	CenterTitle();
}

g2Label* g2Panel::GetTitle()
{
    return Label;
}

void g2Panel::SetSize(int NewWidth, int NewHeight)
{
    // If we are keeping taking the height
    if((Anchors & g2Anchor_None) == g2Anchor_None)
    {
        Height = NewHeight;
        Width = NewWidth;
    }
    if((Anchors & g2Anchor_Top) == g2Anchor_Top)
        Height = NewHeight;
    if((Anchors & g2Anchor_Bottom) == g2Anchor_Top)
        Height = NewHeight;
    if((Anchors & g2Anchor_Left) == g2Anchor_Top)
        Height = NewWidth;
    if((Anchors & g2Anchor_Right) == g2Anchor_Top)
        Height = NewWidth;
    
    // Center the title text
    CenterTitle();
}

g2Button* g2Panel::AddButton(int x, int y, const char* Label, __g2CallBack(callback))
{
    g2Button* NewButton = new g2Button(this, GetTheme());
    NewButton->SetPos(x, y);
    NewButton->SetText(Label);
    NewButton->SetCallback(callback);
    return NewButton;
}

g2Label* g2Panel::AddLabel(int x, int y, const char* Text)
{
    g2Label* NewLabel = new g2Label(this, GetTheme());
    NewLabel->SetPos(x, y);
    NewLabel->SetText(Text);
    return NewLabel;
}

g2CheckBox* g2Panel::AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback), bool* LiveCheckState)
{
    g2CheckBox* NewCheckBox = new g2CheckBox(this, GetTheme());
    NewCheckBox->SetPos(x, y);
    NewCheckBox->GetLabel()->SetText(Text);
    NewCheckBox->SetCallback(callback);
    NewCheckBox->SetLiveVariable(LiveCheckState);
    return NewCheckBox;
}

g2TextField* g2Panel::AddTextField(int x, int y, const char* Text)
{
    g2TextField* NewTextField = new g2TextField(this, GetTheme());
    NewTextField->SetPos(x, y);
    NewTextField->SetText(Text);
    return NewTextField;
}

g2RadioGroup* g2Panel::AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback), int* LiveIndex)
{
    g2RadioGroup* NewRadioGroup = new g2RadioGroup(this, GetTheme());
    NewRadioGroup->SetOptions(Options, OptionCount);
    NewRadioGroup->SetPos(x, y);
    NewRadioGroup->SetCallback(callback);
    NewRadioGroup->SetLiveVariable(LiveIndex);
    return NewRadioGroup;
}

g2DropDown* g2Panel::AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback), int* LiveIndex)
{
    g2DropDown* NewDropDown = new g2DropDown(this, GetTheme());
    NewDropDown->SetPos(x, y);
    NewDropDown->SetOptions(Options, OptionCount);
    NewDropDown->SetCallback(callback);
    NewDropDown->SetLiveVariable(LiveIndex);
    return NewDropDown;
}

g2Dialog* g2Panel::AddDialog(g2DialogType Type, const char* Message)
{
    g2Dialog* NewDialog = new g2Dialog(Type, Message);
    return NewDialog;
}

g2Slider* g2Panel::AddSlider(int x, int y, __g2CallBack(callback), float* LiveValue)
{
    g2Slider* NewSlider = new g2Slider(this, GetTheme());
    NewSlider->SetPos(x, y);
    NewSlider->SetCallback(callback);
    NewSlider->SetLiveVariable(LiveValue);
    return NewSlider;
}

g2ProgressBar* g2Panel::AddProgressBar(int x, int y)
{
    g2ProgressBar* NewProgress = new g2ProgressBar(this, GetTheme());
    NewProgress->SetPos(x, y);
    return NewProgress;
}

g2Spinner* g2Panel::AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback), float* LiveValue)
{
    g2Spinner* NewSpinner = new g2Spinner(this, GetTheme(), Type);
    NewSpinner->SetPos(x, y);
    NewSpinner->SetCallback(callback);
    NewSpinner->SetLiveVariable(LiveValue);
    return NewSpinner;
}

void g2Panel::Render(int pX, int pY)
{
    // Get the size of the source image
    int ImageWidth, ImageHeight;
    GetTheme()->GetComponentSize(g2Theme_Panel, &ImageWidth, &ImageHeight);
    
    // Precompute the offsets and subset sizes
    int Y1 = pY;
    int H1 = ImageHeight / 3;
    
    int Y3 = pY + Height - H1;
    int H3 = H1;
    
    int Y2 = pY + H1;
    int H2 = H1;
    
    /*** Draw ***/
    
    // Draw the top
    DrawComponentStretch(g2Theme_Panel, pX, Y1, Width, 0, ImageHeight / 3);
    
    // Draw the bottom
    DrawComponentStretch(g2Theme_Panel, pX, Y3, Width, 2 * (ImageHeight / 3), ImageHeight);
    
    // Fill each row as best as possible
    for(int i = 0; i <= (Height - H1 - H3) / H2; i++)
    {
        if(i < (Height - H1 - H3) / H2)
            DrawComponentStretch(g2Theme_Panel, pX, Y2 + i * H2, Width, ImageHeight / 3 + 1, 2 * (ImageHeight / 3) + 1);
        else
            DrawComponentStretch(g2Theme_Panel, pX, Y2 + i * H2, Width, ImageHeight / 3 + 1, ImageHeight / 3 + Height % H2);
    }
}

void g2Panel::GetCollisionRect(int* Width, int* Height)
{
    // Post width and height
    *Width = this->Width;
    *Height = this->Height;
}

void g2Panel::WindowResizeEvent(int NewWidth, int NewHeight)
{
    // Save the given width x height
    WindowWidth = NewWidth;
    WindowHeight = NewHeight;
    
    // If on top, copy width, keep 20% visible
    if((Anchors & g2Anchor_Top) == g2Anchor_Top)
    {
        Width = NewWidth;
        Height = NewHeight / 5;
        SetPos(0, 0);
    }
    // If on bottom, copy width, keep 20% visible from bottom
    if((Anchors & g2Anchor_Bottom) == g2Anchor_Bottom)
    {
        Width = NewWidth;
        Height = NewHeight / 5;
        SetPos(0, NewHeight - Height);
    }
    // If we are on the left, copy height, keep 20% visible from left
    if((Anchors & g2Anchor_Left) == g2Anchor_Left)
    {
        Height = NewHeight;
        Width = NewWidth / 5;
        SetPos(0, 0);
    }
    // If we are on the right, copy height, keep 20% visible from right
    if((Anchors & g2Anchor_Right) == g2Anchor_Right)
    {
        Height = NewHeight;
        Width = NewWidth / 5;
        SetPos(NewWidth - Width, 0);
    }
    
    // Center the title text
    CenterTitle();
}

void g2Panel::CenterTitle()
{
    // Center the title text
    int x, y;
    GetTheme()->GetComponentSize(g2Theme_Panel, NULL, &y);
    x = (Width / 2) - Label->GetWidth() / 2;
    y = (y / 3) / 2 - GetTheme()->GetCharacterHeight() / 2;
    Label->SetPos(x, y);
}
