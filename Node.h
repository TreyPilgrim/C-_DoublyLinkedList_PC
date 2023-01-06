1#pragma once
#include "PC.h"

class Node :public PC
{
public:
    Node *next {nullptr};
    Node *prev{nullptr};

    PC player;

    Node(): next{nullptr}, prev {nullptr} {}

};
