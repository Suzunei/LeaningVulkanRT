#pragma once

#define NOMINMAX
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef APIENTRY

#define VULKAN_NON_COPIABLE(ClassName) \
	ClassName(const ClassName&) = delete; \
	ClassName(ClassName&&) = delete; \
	ClassName& operator = (const ClassName&) = delete; \
	ClassName& operator = (ClassName&&) = delete;

#define VULKAN_HANDLE(VulkanHandleType, name) \
public: \
	VulkanHandleType Handle() const { return name; } \
private: \
	VulkanHandleType name{};

namespace Vulkan
{
	void Check(VkResult result, const char* operation);
	const char* ToString(VkResult result);
}

//#define NOMINMAX  防止min max与std min max冲突
//#define GLFW_INCLUDE_NONE 告诉GLFW不要自动包含OPENGL头文件
//#undef APIENTRY  取消 APIENTRY 宏定义，防止命名污染

//第二部分是将指定类的拷贝构造，移动构造，拷贝赋值，移动赋值全部=delete
//第三部分为类自动生成一个handle成员，public提供handle方法返回句柄，
//private: 存储 VulkanHandleType name{} 成员，默认初始化为 VK_NULL_HANDLE
//这样每个vulkan包装类都有统一的方式暴露vulkan对象句柄
//第四部分声明了两个工具函数

//总结：基础设施头文件，为整个vulkan封装提供平台兼容性，资源不可复制语义，包括句柄管理模式和错误检查工具
