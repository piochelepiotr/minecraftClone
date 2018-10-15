#include "renderEngine/displayManager.h"

int main(void)
{
    DisplayManager displayManager(2000, 1600, "Triangle");
    if(!displayManager.createDisplay()) return -1;
    displayManager.mainLoop();
}
