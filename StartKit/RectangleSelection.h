#ifndef RECTANGLE_SELECTION_H_
#define RECTANGLE_SELECTION_H_

#include "lib/gb.h"
#include <functional>
#include <algorithm>


class RectangleSelection
{
private:
    Position start_point_;
    Position end_point_;

public:
    RectangleSelection(int x, int y) { SetStartPoint(x, y); }
    void SetStartPoint(int x, int y) { start_point_.x = x; start_point_.y = y; }
    const Position& GetStartPoint(void) { return start_point_; }
    void SetEndPoint(int x, int y) { end_point_.x = x; end_point_.y = y; }
    const Position& GetEndPoint(void) { return end_point_; }
    RECT GetRectangle(void) {
        RECT rect;
        rect.left   = (std::min)(start_point_.x, end_point_.x);
        rect.right  = std::max(start_point_.x, end_point_.x);
        rect.top    = std::min(start_point_.y, end_point_.y);
        rect.bottom = std::max(start_point_.y, end_point_.y);
        return rect;
    }

    void Draw(void) {
        
        Vector2 v[4] = {
            { static_cast<float>(start_point_.x), static_cast<float>(start_point_.y) },
            { static_cast<float>(end_point_.x),   static_cast<float>(start_point_.y) },
            { static_cast<float>(end_point_.x),   static_cast<float>(end_point_.y) },
            { static_cast<float>(start_point_.x), static_cast<float>(end_point_.y) }
        };

        gb_drawColor(COLOR_GREEN);
        gb_drawPolygon(4, v);
        gb_drawColor(COLOR_WHITE);
    }
};

#endif // RECTANGLE_SELECTION_H_
