#pragma once

#include <string>
#include <any>

std::string ConvToString(std::any v);
float ConvToFloat(std::any v);
int ConvToInt(std::any v);
bool ConvToBool(std::any v);