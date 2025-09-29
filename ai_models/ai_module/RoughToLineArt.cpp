#include <iostream>
#include "RoughToLineArt.hpp"


std::string ModelPath = "../ai_module/RoughToLineArt.pt";
std::vector<struct> inferAI(const struct& input, int UseGPU, int Learn) {
struct Net : torch::nn::Module {
    Net(int input_channels, int num_tags, int num_classes) {
        conv1 = register_module("conv1", torch::nn::Conv2d(input_channels, 16, 3).stride(1).padding(1));
        // Global Pooling後のサイズを固定 (16チャンネル × 1 × 1)
        fc1   = register_module("fc1", torch::nn::Linear(16 + num_tags, 50));
        fc2   = register_module("fc2", torch::nn::Linear(50, num_classes));
    }

    torch::Tensor forward(torch::Tensor image, torch::Tensor tag) {
        auto x = torch::relu(conv1->forward(image));                // [B,16,H,W]
        x = torch::nn::functional::adaptive_avg_pool2d(x, {1,1});   // [B,16,1,1]
        x = x.view({x.size(0), -1});                                // [B,16]
        x = torch::cat({x, tag}, 1);                                // タグ結合 [B,16+TAG]
        x = torch::relu(fc1->forward(x));                           // [B,50]
        x = fc2->forward(x);                                        // [B,NUM_CLASSES]
        return x;
    }

    torch::nn::Conv2d conv1{nullptr};
    torch::nn::Linear fc1{nullptr}, fc2{nullptr};
};

// --- 2. 学習関数（最小型） ---
void train_step(Net& model,
                torch::optim::Optimizer& optimizer,
                torch::Tensor& image_tensor,
                torch::Tensor& mask_tensor,
                torch::Tensor& tag_tensor) 
{
    model.train();
    optimizer.zero_grad();

    auto output = model.forward(image_tensor, tag_tensor);

    auto loss = torch::nn::functional::cross_entropy(output, mask_tensor);
    loss.backward();
    optimizer.step();

    std::cout << "Loss: " << loss.item<float>() << std::endl;
}

// --- 3. メイン ---
int main() {
    int B = 2;      // バッチサイズ
    int C = 4;      // RGBA
    int H = 1024;
    int W = 1024;
    int TAG = 5;
    int NUM_CLASSES = 10;

    // --- データ作成 ---
    std::vector<float> ImageMap1D(B * C * H * W, 0.5f);
    std::vector<int64_t> MaskMap1D(B, 1);      // Global Poolingで分類なので1ラベル/B
    std::vector<float> TagList1D(B * TAG, 0.1f);

    // --- Tensor化 ---
    torch::Tensor image_tensor = torch::from_blob(ImageMap1D.data(), {B,C,H,W}, torch::kFloat32).clone();
    torch::Tensor mask_tensor  = torch::from_blob(MaskMap1D.data(), {B}, torch::kInt64).clone();
    torch::Tensor tag_tensor   = torch::from_blob(TagList1D.data(), {B,TAG}, torch::kFloat32).clone();

    // --- GPU ---
    if (torch::cuda::is_available()) {
        image_tensor = image_tensor.to(torch::kCUDA);
        mask_tensor  = mask_tensor.to(torch::kCUDA);
        tag_tensor   = tag_tensor.to(torch::kCUDA);
    }

    // --- モデル & オプティマイザ ---
    Net model(C, TAG, NUM_CLASSES);
    if (torch::cuda::is_available()) {
        model.to(torch::kCUDA);
    }
    torch::optim::SGD optimizer(model.parameters(), 0.01);

    // --- 学習ループ ---
    for (int epoch = 0; epoch < 5; ++epoch) {
        std::cout << "Epoch " << epoch << ": ";
        train_step(model, optimizer, image_tensor, mask_tensor, tag_tensor);
    }

    return 0;
}
/*
structの中身
a
struct data = {
    std::vector<float> ImageMap(B * C * H * W, 0.0f);
    std::vector<int64_t> MaskMap(B * H * W, 0);
    std::vector<float> TagList(B * TAG, 0.0f);

    float ImageMap: b*C*H*W + c*H*W + h*W + w

    int64_t MaskMap: b*H*W + h*W + w

    float TagList: b*TAG + t

}
*/