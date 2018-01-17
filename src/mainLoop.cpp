#include "renderEngine/displayManager.h"

int main(void)
{
    DisplayManager displayManager(1200, 800, "Triangle");
    if(!displayManager.createDisplay()) return -1;
    displayManager.mainLoop();
}
