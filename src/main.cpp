#include"Window.hpp"

int main() {
    Vulkan::WindowConfig window_config
    { 
        "VulkanRT",
        800,
        600,
        false,
        false,
        false
    };
    Vulkan::Window window(window_config);

    window.Run();

    return 0;
}
