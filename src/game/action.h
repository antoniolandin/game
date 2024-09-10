#pragma once

#include <string>

enum ActionType {
    ACTION_START,
    ACTION_END,
};

struct Action {
    std::string name;
    ActionType type;
};
