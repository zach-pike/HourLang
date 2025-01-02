#pragma GCC push_options
#pragma GCC optimize("O0")

#include "raylib.h"

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include <any>
#include <string>

extern "C" {
    Any getColor(ParameterValueList params, Stack& s) {
        int r = ConvToInt(params[0]);
        int g = ConvToInt(params[1]);
        int b = ConvToInt(params[2]);
        int a = ConvToInt(params[3]);

        return Color {
            (uint8_t) r,
            (uint8_t) g,
            (uint8_t) b,
            (uint8_t) a
        };
    }

    Any rayInitWindow(ParameterValueList params, Stack& s) {
        int width = ConvToInt(params[0]);
        int height = ConvToInt(params[1]);
        std::string name = std::any_cast<std::string>(params[2]);

        InitWindow(width, height, name.c_str());

        return Any();
    }

    Any rayCloseWindow(ParameterValueList params, Stack& s) {
        CloseWindow();

        return Any();
    }

    Any raySetTargetFPS(ParameterValueList params, Stack& s) {
        int fps = ConvToInt(params[0]);

        SetTargetFPS(fps);

        return Any();
    }

    Any rayBeginDrawing(ParameterValueList params, Stack& s) {
        BeginDrawing();

        return Any();
    }

    Any rayEndDrawing(ParameterValueList params, Stack& s) {
        EndDrawing();

        return Any();
    }

    Any rayClearBackground(ParameterValueList params, Stack& s) {
        Color c = std::any_cast<Color>(params[0]);

        ClearBackground(c);

        return Any();
    }

    Any rayWindowShouldClose(ParameterValueList params, Stack& s) {
        return WindowShouldClose();
    }

    Any rayDrawRectangle(ParameterValueList params, Stack& s) {
        int x = ConvToInt(params[0]);
        int y = ConvToInt(params[1]);
        int width = ConvToInt(params[2]);
        int height = ConvToInt(params[3]);

        Color c = std::any_cast<Color>(params[4]);

        DrawRectangle(x, y, width, height, c);

        return Any();
    }

    Any rayDrawText(ParameterValueList params, Stack& s) {
        std::string text = std::any_cast<String>(params[0]);
        int x = ConvToInt(params[1]);
        int y = ConvToInt(params[2]);
        int fontSize = ConvToInt(params[3]);
        Color color = std::any_cast<Color>(params[4]);
        
        DrawText(text.c_str(), x, y, fontSize, color);

        return Any();
    }

    Any rayIsKeyDown(ParameterValueList params, Stack& s) {
        KeyboardKey x = std::any_cast<KeyboardKey>(params[0]);
        
        return (Bool) IsKeyDown(x);
    }

    Any rayLoadImage(ParameterValueList params, Stack& s) {
        String fileName = std::any_cast<String>(params[0]);
        
        return LoadImage(fileName.c_str());
    }

    Any raySetWindowIcon(ParameterValueList params, Stack& s) {
        Image img = std::any_cast<Image>(params[0]);

        SetWindowIcon(img);

        return Any();
    }

    Any rayLoadTexture(ParameterValueList params, Stack& s) {
        String fileName = std::any_cast<String>(params[0]);
        
        return LoadTexture(fileName.c_str());
    }

    Any rayVector2(ParameterValueList params, Stack& s) {
        float x = ConvToFloat(params[0]);
        float y = ConvToFloat(params[1]);
        
        return Vector2 { x, y };
    }

    Any rayDrawTextureEx(ParameterValueList params, Stack& s) {
        Texture2D texture = std::any_cast<Texture2D>(params[0]);
        Vector2 pos = std::any_cast<Vector2>(params[1]);
        float rotation = ConvToFloat(params[2]);
        float scale = ConvToFloat(params[3]);
        Color tint = std::any_cast<Color>(params[4]);

        DrawTextureEx(texture, pos, rotation, scale, tint);

        return Any();
    }
}

#pragma GCC pop_options