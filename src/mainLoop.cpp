#include "renderEngine/displayManager.h"

int main(void)
{
    DisplayManager displayManager(800, 800, "Triangle");
    if(!displayManager.createDisplay()) return -1;
    displayManager.mainLoop();
}
