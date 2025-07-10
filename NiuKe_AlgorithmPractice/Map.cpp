#include "Map.h"
#include "Map.h"

// Add an obstacle rectangle to the map
void Map::addObstacle(int x1, int y1, int x2, int y2) {
    obstacles.push_back({ x1, y1, x2, y2 });
}

// Draw all obstacles with horizontal camera offset
void Map::draw(int screenX) const {
    setfillcolor(RGB(139, 69, 19)); // Brown color for obstacles
    for (const auto& obs : obstacles) {
        int drawX1 = obs.x1 - screenX;
        int drawX2 = obs.x2 - screenX;
        // Only draw if within [0,600] window
        if (drawX2 >= 0 && drawX1 <= 600) {
            fillrectangle(drawX1, obs.y1, drawX2, obs.y2);
        }
    }
}

// Check collision between a rectangle at (x,y) with size (w,h) and any obstacle
bool Map::checkCollision(int x, int y, int w, int h) const {
    for (const auto& obs : obstacles) {
        if (x < obs.x2 && x + w > obs.x1 && y < obs.y2 && y + h > obs.y1) {
            return true;
        }
    }
    return false;
}
