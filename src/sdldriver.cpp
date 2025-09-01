#include <stdio.h>
#include "../include/sdldriver.h"

SDLDriver::SDLDriver(int width, int height, int size, const char *windowName)
{
    windowWidth = width;
    windowHeight = height;
    pixelSize = size;

    window = SDL_CreateWindow(windowName, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
}

SDL_AppResult SDLDriver::drive()
{

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    ConvexHull ch;

    SDL_Event event;
    bool running = true;
    while(running) {
        SDL_RenderClear(this->renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                ch.addPoint(mouseX, mouseY);
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_SPACE) {
                    for (int i = 0; i < 10; ++i) {
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distribWidth(100, windowWidth - 100);
                        std::uniform_int_distribution<> distribHeight(100, windowHeight - 100);
                        int randomXCoor = distribWidth(gen), randomYCoor = distribHeight(gen);
                        ch.addPoint(randomXCoor, randomYCoor);
                    }
                } else if (event.key.scancode == SDL_SCANCODE_C) {
                    ch.dump();
                } else if (event.key.scancode == SDL_SCANCODE_RETURN) {
                    std::cout << "Finding convex hull..." << std::endl;
                    auto startTime = std::chrono::high_resolution_clock::now();
                    ch.generateConvexHull();
                    auto endTime = std::chrono::high_resolution_clock::now();
                    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                    std::cout << "Convex hull generated in " << duration << std::endl;
                } else if (event.key.scancode == SDL_SCANCODE_T) {
                    for (int i = 0; i < 1000; ++i) {
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distribWidth(100, windowWidth - 100);
                        std::uniform_int_distribution<> distribHeight(100, windowHeight - 100);
                        int randomXCoor = distribWidth(gen), randomYCoor = distribHeight(gen);
                        ch.addPoint(randomXCoor, randomYCoor);
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        std::vector<Point>::iterator it;
        std::vector<Point> pointSet = ch.pointSet;
        for (it = pointSet.begin(); it != pointSet.end(); ++it) {
            Point currentPoint = *it;
            SDL_FRect vertex;
            vertex.x = currentPoint.x, vertex.y = currentPoint.y, vertex.w = pixelSize, vertex.h = pixelSize;
            if (!SDL_RenderFillRect(renderer, &vertex)) {
                SDL_Log("Could not draw rectangle: %s", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        std::vector<Point> convexHull = ch.convexHull;
        if (convexHull.size() > 1) {
            for (int i = 1; i < convexHull.size(); ++i) {
                Point point1 = convexHull.at(i - 1);
                Point point2 = convexHull.at(i);
                if (!SDL_RenderLine(renderer, point1.x, point1.y, point2.x, point2.y)) {
                    SDL_Log("Could not draw line: %s", SDL_GetError());
                }
            }
            Point first = convexHull.at(0);
            Point last = convexHull.at(convexHull.size() - 1);
            if (!SDL_RenderLine(renderer, last.x, last.y, first.x, first.y)) {
                SDL_Log("Could not draw line: %s", SDL_GetError());
            }
        }


        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_Quit();
    return SDL_APP_CONTINUE;
}