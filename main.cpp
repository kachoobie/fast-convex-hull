#include "include/sdldriver.h"

int main()
{
    int windowWidth = 1024, windowHeight = 768, size = 4;
    const char *windowName = "Slow Convex Hull";
    SDLDriver driver(windowWidth, windowHeight, size, windowName);

    driver.drive();

    return 1;
}