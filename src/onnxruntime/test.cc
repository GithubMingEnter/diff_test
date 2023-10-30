#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <vector>
#include <onnxruntime_cxx_api.h>

using namespace std;


int main()
{
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    Ort::SessionOptions session_options;

    OrtCUDAProviderOptions cuda_options{
          0,
          OrtCudnnConvAlgoSearch::EXHAUSTIVE,
          std::numeric_limits<size_t>::max(),
          0,
          true
      };

    session_options.AppendExecutionProvider_CUDA(cuda_options);
    const char* model_path = "./overlapTransformer.onnx";

    int width = 900;
    int height = 32;
    int len_arr = width*height;
    float virtual_image[len_arr];
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
        {
            virtual_image[int(i*width+j)] = 1; // range
        }


    Ort::Session session(env, model_path, session_options);
    // print model input layer (node names, types, shape etc.)
    Ort::AllocatorWithDefaultOptions allocator;

    // print number of model input nodes
    size_t num_input_nodes = session.GetInputCount();
    std::vector<const char*> input_node_names = {"input"};
    std::vector<const char*> output_node_names = {"output"};

    std::vector<int64_t> input_node_dims = {1, 1, 32, 900};
    size_t input_tensor_size = 32 * 900;
    std::vector<float> input_tensor_values(input_tensor_size);
    for (unsigned int i = 0; i < input_tensor_size; i++)
        input_tensor_values[i] = float(virtual_image[i]);
    // create input tensor object from data values ！！！！！！！！！！
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(),
                                                            input_tensor_size, input_node_dims.data(), 4);

    std::vector<Ort::Value> ort_inputs;
    ort_inputs.push_back(std::move(input_tensor));

    auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_node_names.data(), ort_inputs.data(),
                                    ort_inputs.size(), output_node_names.data(), 1);

    float* floatarr = output_tensors[0].GetTensorMutableData<float>();

    for (int i=0; i<256; i++)
    {
        std::cout<<floatarr[i]<<std::endl;
    }

    return 0;
}
