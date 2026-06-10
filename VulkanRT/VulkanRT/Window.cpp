#include "Window.hpp"
#include "Exception.hpp"
#include "StbImage.hpp"
#include <iostream>

namespace Vulkan {

namespace 
{
	void GlfwErrorCallback(const int error, const char* const description)
	{
		std::cerr << "ERROR:GLFW :" << description << "(code:" << error << ")" << std::endl;
	}

	void GLfwKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		auto* const this_ = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (this_->OnKey)
		{
			this_->OnKey(key, scancode, action, mods);
		}
	}
}

}