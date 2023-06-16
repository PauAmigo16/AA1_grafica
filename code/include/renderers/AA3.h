#pragma once
#include "Renderer.h"
#include "../objects/TexturedPlane.h"
#include "../objects/CarSpawner.h"
#include "../objects/BB_Spawner.h"

class AA3 :
    public Renderer
{
public:
    AA3(int w, int h);
    ~AA3();

    void render(float dt);
    void renderGUI();

private:
    TexturedPlane* theTrack;
    CarSpawner* cars;
    BB_Spawner* trees;

    bool inFP_Mode = false;

    void HandleCameraMode();

};
