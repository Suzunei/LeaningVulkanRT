#pragma once

#include "WindowConfig.hpp"
#include "Vulkan.hpp"
#include <functional>
#include <vector>

namespace Vulkan
{
	class Window final
	{
	public:

		VULKAN_NON_COPIABLE(Window)

		explicit Window(const WindowConfig& config);
		~Window();

		//window instance properties
		const WindowConfig& Config() const { return config_; }
		GLFWwindow* Handle() const { return window_; }
		float ContentScale() const;
		VkExtent2D FramebufferSize() const;
		VkExtent2D WindowSize() const;

		//GLFW instance properties
		const char* GetKeyName(int key, int scancode) const;
		std::vector<const char*> GetRequiredInstanceExtensions() const;
		double GetTime() const;

		//Callbacks
		std::function<void()> DrawFrame;
		std::function<void(int key, int scancode, int action, int mods)> OnKey;


	private:

		const WindowConfig config_;
		GLFWwindow* window_{};
	};
}
