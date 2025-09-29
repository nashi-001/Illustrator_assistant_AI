#pragma once
#include "IllustAssistantAiManager.hpp"
#include <iostream>

class AIInterface : public BaseAIInterface {
public:
    int LearnAIModel(LearnData data) override;
    int InferAIModel(InferData data) override;

};