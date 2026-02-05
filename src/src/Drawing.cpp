#include "Drawing.h"

namespace Drawing {
    bool Init() {
        return true;
    }

    void Shutdown() {
        // Shutdown
    }

    void DrawLine(Vector2 from, Vector2 to, float* color, float width) {
        // Stub implementation
    }

    void DrawRect(Vector2 topLeft, Vector2 bottomRight, float* color, float thickness, float rounding) {
        // Stub implementation
    }

    void DrawFilledRect(Vector2 topLeft, Vector2 bottomRight, float* color) {
        // Stub implementation
    }

    void DrawCircle(Vector2 center, float radius, float* color, float thickness) {
        // Stub implementation
    }

    void DrawFilledCircle(Vector2 center, float radius, float* color) {
        // Stub implementation
    }

    void DrawText(Vector2 position, const char* text, float* color, float size) {
        // Stub implementation
    }

    Vector2 GetTextSize(const char* text, float size) {
        return Vector2(0.0f, 0.0f);
    }

    void DrawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, float* color, float thickness) {
        // Stub implementation
    }

    void DrawFilledTriangle(Vector2 p1, Vector2 p2, Vector2 p3, float* color) {
        // Stub implementation
    }

    void DrawPolygon(Vector2* points, int count, float* color, float thickness) {
        // Stub implementation
    }

    void DrawFilledPolygon(Vector2* points, int count, float* color) {
        // Stub implementation
    }

    void SetLineWidth(float width) {
        // Stub implementation
    }

    void SetBlendMode(GLenum srcFactor, GLenum dstFactor) {
        // Stub implementation
    }

    void BeginFrame() {
        // Stub implementation
    }

    void EndFrame() {
        // Stub implementation
    }
}