#pragma once

#include <cstdint>
#include <string>

//窗口设置
namespace Vulkan
{
	struct WindowConfig final
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool CursorDisabled;
		bool Fullscreen;
		bool Resizable;
	};
}
