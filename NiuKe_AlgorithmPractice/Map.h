#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

// Map class manages obstacles and drawing with a camera offset.
struct Barrier {
    int x1, y1, x2, y2;
};
class Map {
private:
    vector<Barrier> obstacles; // Obstacle rectangles in world coordinates
public:
    // Add an obstacle (top-left (x1,y1), bottom-right (x2,y2))
    void addObstacle(int x1, int y1, int x2, int y2);
    // Draw obstacles with horizontal offset (camera position)
    void draw(int screenX) const;
    // Check collision between rectangle (x,y,w,h) and any obstacle
    bool checkCollision(int x, int y, int w, int h) const;
};
