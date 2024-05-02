#pragma once
#include "UI.h"

class Texture;


class ImageUI :
    public UI
{
private:



public:
    virtual void Update();
    virtual void Render(HDC _dc);
    
 

    CLONE(ImageUI);

public:


    void AlignHorizontalCenter();
    void AlignHorizontalRight();
    void AlignHorizontalLeft();

	void AlignVerticalCenter();
	void AlignVerticalTop();
	void AlignVerticalBottom();


public:
    ImageUI(bool _bCamAff, Scene* _ownerScene);
    ~ImageUI();
};

