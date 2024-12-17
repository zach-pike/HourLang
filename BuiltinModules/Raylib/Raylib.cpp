#pragma GCC push_options
#pragma GCC optimize("O0")

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include "Stack/Stack.hpp"

#include "raylib.h"

#include <iostream>
#include <cmath>

extern "C" {
    void moduleMain(Stack& s) {
        // Add some global vars
        s.setVariable("WHITE", Color { 255, 255, 255, 255 });
        s.setVariable("BLACK", Color { 0, 0, 0, 255 });
        s.setVariable("RED", Color { 255, 0, 0, 255 });
        s.setVariable("GREEN", Color { 0, 255, 0, 255 });
        s.setVariable("BLUE", Color { 0, 0, 255, 255 });
        
        // Letter keys
        s.setVariable("KEY_A", KEY_A);
        s.setVariable("KEY_B", KEY_B);
        s.setVariable("KEY_C", KEY_C);
        s.setVariable("KEY_D", KEY_D);
        s.setVariable("KEY_E", KEY_E);
        s.setVariable("KEY_F", KEY_F);
        s.setVariable("KEY_G", KEY_G);
        s.setVariable("KEY_H", KEY_H);
        s.setVariable("KEY_I", KEY_I);
        s.setVariable("KEY_J", KEY_J);
        s.setVariable("KEY_K", KEY_K);
        s.setVariable("KEY_L", KEY_L);
        s.setVariable("KEY_M", KEY_M);
        s.setVariable("KEY_N", KEY_N);
        s.setVariable("KEY_O", KEY_O);
        s.setVariable("KEY_P", KEY_P);
        s.setVariable("KEY_Q", KEY_Q);
        s.setVariable("KEY_R", KEY_R);
        s.setVariable("KEY_S", KEY_S);
        s.setVariable("KEY_T", KEY_T);
        s.setVariable("KEY_U", KEY_U);
        s.setVariable("KEY_V", KEY_V);
        s.setVariable("KEY_W", KEY_W);
        s.setVariable("KEY_X", KEY_X);
        s.setVariable("KEY_Y", KEY_Y);
        s.setVariable("KEY_Z", KEY_Z);

        // Extra keys
        s.setVariable("KEY_LEFT_CONTROL", KEY_LEFT_CONTROL);
        s.setVariable("KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL);

        s.setVariable("KEY_LEFT_ALT", KEY_LEFT_ALT);
        s.setVariable("KEY_RIGHT_ALT", KEY_RIGHT_ALT);

        s.setVariable("KEY_LEFT_SHIFT", KEY_LEFT_SHIFT);
        s.setVariable("KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT);

        s.setVariable("KEY_TAB", KEY_TAB);

        // Directional
        s.setVariable("KEY_UP", KEY_UP);
        s.setVariable("KEY_DOWN", KEY_DOWN);
        s.setVariable("KEY_LEFT", KEY_LEFT);
        s.setVariable("KEY_RIGHT", KEY_RIGHT);
    }

    std::vector<ModuleFunction> getModuleFunctions() {
        std::vector<ModuleFunction> funcs;

        // Type constructors
        MODULE_EXPORT(
            funcs,
            "Color",
            "getColor",
            PARAM_TYPES(
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,
            )
        );

        // Functions
        MODULE_EXPORT(
            funcs,
            "InitWindow",
            "rayInitWindow",
            PARAM_TYPES(
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,
                VariableType::STRING
            )
        );

        MODULE_EXPORT(
            funcs,
            "CloseWindow",
            "rayCloseWindow",
            PARAM_TYPES()
        );

        MODULE_EXPORT(
            funcs,
            "SetTargetFPS",
            "raySetTargetFPS",
            PARAM_TYPES(
                VariableType::INT | VariableType::FLOAT
            )
        );

        MODULE_EXPORT(
            funcs,
            "BeginDrawing",
            "rayBeginDrawing",
            PARAM_TYPES()
        );

        MODULE_EXPORT(
            funcs,
            "EndDrawing",
            "rayEndDrawing",
            PARAM_TYPES()
        );

        MODULE_EXPORT(
            funcs,
            "ClearBackground",
            "rayClearBackground",
            PARAM_TYPES(
                VariableType::ANY
            )
        );

        MODULE_EXPORT(
            funcs,
            "WindowShouldClose",
            "rayWindowShouldClose",
            PARAM_TYPES()
        );

        MODULE_EXPORT(
            funcs,
            "DrawRectangle",
            "rayDrawRectangle",
            PARAM_TYPES(
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,

                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,

                VariableType::ANY
            )
        );

        MODULE_EXPORT(
            funcs,
            "DrawText",
            "rayDrawText",
            PARAM_TYPES(
                VariableType::STRING,
                VariableType::INT | VariableType::FLOAT,
                VariableType::INT | VariableType::FLOAT,

                VariableType::INT | VariableType::FLOAT,

                VariableType::ANY
            )
        );

        MODULE_EXPORT(
            funcs,
            "IsKeyDown",
            "rayIsKeyDown",
            PARAM_TYPES(
                VariableType::ANY
            )
        );

        MODULE_EXPORT(
            funcs,
            "LoadImage",
            "rayLoadImage",
            PARAM_TYPES(
                VariableType::STRING
            )
        );

        MODULE_EXPORT(
            funcs,
            "SetWindowIcon",
            "raySetWindowIcon",
            PARAM_TYPES(
                VariableType::ANY
            )
        );

        
        return funcs;
    }
}

#pragma GCC pop_options