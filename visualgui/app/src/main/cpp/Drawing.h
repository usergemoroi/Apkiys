#ifndef DRAWING_H
#define DRAWING_H

#include "Vector.h"
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

namespace Drawing {
    // Initialization
    bool Init();
    void Shutdown();
    
    // Basic shapes
    void DrawLine(Vector2 from, Vector2 to, float* color, float width);
    void DrawRect(Vector2 topLeft, Vector2 bottomRight, float* color, float thickness, float rounding = 0.0f);
    void DrawFilledRect(Vector2 topLeft, Vector2 bottomRight, float* color);
    void DrawCircle(Vector2 center, float radius, float* color, float thickness);
    void DrawFilledCircle(Vector2 center, float radius, float* color);
    
    // Text rendering
    void DrawText(Vector2 position, const char* text, float* color, float size = 14.0f);
    Vector2 GetTextSize(const char* text, float size = 14.0f);
    
    // Advanced
    void DrawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, float* color, float thickness);
    void DrawFilledTriangle(Vector2 p1, Vector2 p2, Vector2 p3, float* color);
    void DrawPolygon(Vector2* points, int count, float* color, float thickness);
    void DrawFilledPolygon(Vector2* points, int count, float* color);
    
    // Utilities
    void SetLineWidth(float width);
    void SetBlendMode(GLenum srcFactor, GLenum dstFactor);
    void BeginFrame();
    void EndFrame();
}

#endif // DRAWING_H
