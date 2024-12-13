#pragma GCC push_options
#pragma GCC optimize("O0")

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include "raylib.h"

#include <iostream>
#include <cmath>

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
        int width = std::any_cast<int>(params[0]);
        int height = std::any_cast<int>(params[1]);
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

    void moduleMain(Stack& s) {}

    std::vector<ModuleFunction> getModuleFunctions() {
        // Module functions
        ModuleFunction color{
            .symbolName = "getColor",
            .functionName = "Color",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                }),
                .hasVaArgs = false
            }
        };

        ModuleFunction initWindow{
            .symbolName = "rayInitWindow",
            .functionName = "InitWindow",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT, VariableType::INT, VariableType::STRING }),
                .hasVaArgs = false
            }
        };

        ModuleFunction closeWindow{
            .symbolName = "rayCloseWindow",
            .functionName = "CloseWindow",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ }),
                .hasVaArgs = false
            }
        };

        ModuleFunction setTargetFPS{
            .symbolName = "raySetTargetFPS",
            .functionName = "SetTargetFPS",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction beginDrawing{
            .symbolName = "rayBeginDrawing",
            .functionName = "BeginDrawing",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ }),
                .hasVaArgs = false
            }
        };

        ModuleFunction endDrawing{
            .symbolName = "rayEndDrawing",
            .functionName = "EndDrawing",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ }),
                .hasVaArgs = false
            }
        };

        ModuleFunction clearBackground{
            .symbolName = "rayClearBackground",
            .functionName = "ClearBackground",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({
                    VariableType::ANY
                }),
                .hasVaArgs = false
            }
        };

        ModuleFunction windowShouldClose{
            .symbolName = "rayWindowShouldClose",
            .functionName = "WindowShouldClose",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ }),
                .hasVaArgs = false
            }
        };

        ModuleFunction drawRectangle{
            .symbolName = "rayDrawRectangle",
            .functionName = "DrawRectangle",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::INT | VariableType::FLOAT,
                    VariableType::ANY
                }),
                .hasVaArgs = false
            }
        };


        std::vector<ModuleFunction> funcs;
        funcs.push_back(color);
        funcs.push_back(initWindow);
        funcs.push_back(closeWindow);
        funcs.push_back(setTargetFPS);
        funcs.push_back(beginDrawing);
        funcs.push_back(endDrawing);
        funcs.push_back(clearBackground);
        funcs.push_back(windowShouldClose);
        funcs.push_back(drawRectangle);
        
        return funcs;
    }
}

#pragma GCC pop_options