#pragma once
#include <iostream>

#include <vector>
#include <algorithm>

#include "vulkan.hpp"

#include "RenderDevice.h"

#define DEBUG

class VulkanAPI
{
public:
	VulkanAPI();
	~VulkanAPI();

	vk::Instance* getInstance();
	void attachSurface(vk::SurfaceKHR* surface);

	RenderDevice getDevice(int offset);

private:
	vk::Instance m_Instance;

	int selectedDevice;
	vk::Device m_Device;
	std::vector<RenderDevice> m_RenderDevices;

	bool surfaceExists = false;
	vk::SurfaceKHR* m_Surface;



	std::vector<const char*> INSTANCE_LAYERS = {
#ifdef DEBUG
		"VK_LAYER_LUNARG_standard_validation",
#endif
		
	};

	std::vector<const char*> INSTANCE_EXTS = {
#ifdef DEBUG
		"VK_EXT_debug_utils",
#endif
		"VK_KHR_surface",
		"VK_KHR_win32_surface"
	};

	std::vector<const char*> DEVICE_EXTS = {
		"VK_KHR_swapchain"
	};


	VkDebugUtilsMessengerEXT callback;

	void registerDebug();

	VkResult CreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pCallback);
	
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, 
		VkDebugUtilsMessengerEXT callback, 
		const VkAllocationCallbacks* pAllocator);
		

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		vk::DebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

};

