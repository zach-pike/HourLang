#pragma GCC push_options
#pragma GCC optimize("O0")

#include "raylib.h"

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include <any>
#include <string>

extern "C" {
    std::any getColor(ParameterValueList params, Stack& s) {
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

    std::any rayInitWindow(ParameterValueList params, Stack& s) {
        int width = ConvToInt(params[0]);
        int height = ConvToInt(params[1]);
        std::string name = std::any_cast<std::string>(params[2]);

        InitWindow(width, height, name.c_str());

        return std::any();
    }

    std::any rayCloseWindow(ParameterValueList params, Stack& s) {
        CloseWindow();

        return std::any();
    }

    std::any raySetTargetFPS(ParameterValueList params, Stack& s) {
        int fps = ConvToInt(params[0]);

        SetTargetFPS(fps);

        return std::any();
    }

    std::any rayBeginDrawing(ParameterValueList params, Stack& s) {
        BeginDrawing();

        return std::any();
    }

    std::any rayEndDrawing(ParameterValueList params, Stack& s) {
        EndDrawing();

        return std::any();
    }

    std::any rayClearBackground(ParameterValueList params, Stack& s) {
        Color c = std::any_cast<Color>(params[0]);

        ClearBackground(c);

        return std::any();
    }

    std::any rayWindowShouldClose(ParameterValueList params, Stack& s) {
        return WindowShouldClose();
    }

    std::any rayDrawRectangle(ParameterValueList params, Stack& s) {
        int x = ConvToInt(params[0]);
        int y = ConvToInt(params[1]);
        int width = ConvToInt(params[2]);
        int height = ConvToInt(params[3]);

        Color c = std::any_cast<Color>(params[4]);

        DrawRectangle(x, y, width, height, c);

        return std::any();
    }

    std::any rayDrawText(ParameterValueList params, Stack& s) {
        std::string text = std::any_cast<String>(params[0]);
        int x = ConvToInt(params[1]);
        int y = ConvToInt(params[2]);
        int fontSize = ConvToInt(params[3]);
        Color color = std::any_cast<Color>(params[4]);
        
        DrawText(text.c_str(), x, y, fontSize, color);

        return std::any();
    }

    std::any rayIsKeyDown(ParameterValueList params, Stack& s) {
        KeyboardKey x = std::any_cast<KeyboardKey>(params[0]);
        
        return (bool) IsKeyDown(x);
    }

    std::any rayLoadImage(ParameterValueList params, Stack& s) {
        String fileName = std::any_cast<String>(params[0]);
        
        return LoadImage(fileName.c_str());
    }

    std::any raySetWindowIcon(ParameterValueList params, Stack& s) {
        Image img = std::any_cast<Image>(params[0]);

        SetWindowIcon(img);

        return std::any();
    }
}

#pragma GCC pop_options