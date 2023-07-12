#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

constexpr uint32_t WIDTH  = 800;
constexpr uint32_t HEIGHT = 600;

const std::vector<const char*> requiredValidationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif


bool checkValidationLayerSupport()
{
    uint32_t supportedValidationLayerCount = 0;
    vkEnumerateInstanceLayerProperties(&supportedValidationLayerCount, nullptr);
    std::vector<VkLayerProperties> supportedLayers(supportedValidationLayerCount);
    vkEnumerateInstanceLayerProperties(&supportedValidationLayerCount, supportedLayers.data());

    std::cout << "supported Layers: \n";
    for (const auto& layer : supportedLayers)
    {
        std::cout << "\t" << layer.layerName << '\n';
    }
    std::cout << "required Layers: \n";
    for (const char* layer : requiredValidationLayers)
    {
        std::cout << "\t" << layer << '\n';
    }

    for (const char* layer : requiredValidationLayers)
    {
        bool found = false;
        for (const auto& supportedLayer : supportedLayers)
        {
            if (std::strcmp(layer, supportedLayer.layerName) == 0)
            {
                found = true;
                break;
            }
        }
        if (found == false)
        {
            return false;
        }
    }

    return true;
}

const std::vector<const char*> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers)
    {
        requiredExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return requiredExtensions;
}

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
    
private:
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }
    
    void initVulkan()
    {
        createInstance();
    }
    
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }
    
    void cleanup()
    {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void createInstance()
    {
        requiredGlobalExtensions = getRequiredExtensions();
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        
        uint32_t supportedExtensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, nullptr);
        std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, supportedExtensions.data());
        std::cout << "supported global Extensions: \n";
        for (const auto& extension : supportedExtensions)
        {
            std::cout << "\t" << extension.extensionName << '\n';
        }

        std::cout << "required global extensions: \n";
        for (const char* extension: requiredGlobalExtensions)
        {
            std::cout << "\t" << extension << '\n';
        }
        
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredGlobalExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredGlobalExtensions.data();
        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(requiredValidationLayers.size());
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }
        
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }
    
private:
    GLFWwindow* window;

    std::vector<const char*> requiredGlobalExtensions;
    VkInstance instance;
};

int main()
{
    HelloTriangleApplication app;
    
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
