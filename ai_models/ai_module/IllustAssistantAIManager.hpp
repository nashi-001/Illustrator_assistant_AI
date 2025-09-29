#pragma once
#include <torch/torch.h>
#include <torch/script.h>
#include <string>
#include <vector>

class BaseAIInterface{
public:
    virtual int LearnAIModel(struct LearnData) = 0;
    virtual int InferAIModel(struct InferData) = 0;
    
};

