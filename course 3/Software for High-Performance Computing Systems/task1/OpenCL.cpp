#include <iostream>
#include <vector>
#include <CL/cl.hpp>

const char* kernelSource = R"(
    __kernel void msg() {
        int globalId = get_global_id(0);
        printf("from process %d\n", globalId);
    }
)";

int main() {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty()) {
        std::cerr << "No OpenCL platforms found." << std::endl;
        return 1;
    }

    cl::Platform platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    if (devices.empty()) {
        std::cerr << "No OpenCL devices found." << std::endl;
        return 1;
    }

    cl::Device device = devices.front();

    cl::Context context(device);
    cl::CommandQueue queue(context, device);

 
    cl::Program::Sources sources(1, std::make_pair(kernelSource, strlen(kernelSource)));
    cl::Program program(context, sources);
    if (program.build({ device }) != CL_SUCCESS) {
        std::cerr << "Error building kernel: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
        return 1;
    }

    cl::Kernel kernel(program, "msg");


    cl::NDRange globalSize(5); 
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, cl::NullRange);

    queue.finish();

    return 0;
}
