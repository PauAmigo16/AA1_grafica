#pragma once
#include "Renderer.h"

#include <objects/Cube.h>

class ExSimpleCube :
    public Renderer
{
    Cube* cube;

public:
    ExSimpleCube(int width, int height);
    ~ExSimpleCube();
protected:
    void render(float dt) override;
    void renderGUI() override;
};

