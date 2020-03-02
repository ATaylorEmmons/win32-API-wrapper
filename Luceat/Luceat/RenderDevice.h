#pragma once


#include "vulkan.hpp"

struct QueueFamilyData {
	bool supportsPresentation = false;
	bool supportsGraphics = false;
	int familyId;
	int queueCount;
};

class RenderDevice
{
public:
	RenderDevice(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR* surface);

	~RenderDevice();

	vk::SurfaceCapabilitiesKHR getSurfaceCapabilities();

private:
	RenderDevice();

	vk::PhysicalDevice physicalDevice;
	vk::Device logicalDevice;

	std::vector<QueueFamilyData> queueFamilies;

	vk::SurfaceCapabilitiesKHR m_SurfaceCapabilities;
	std::vector<vk::SurfaceFormatKHR> m_SurfaceFormats;
	std::vector<vk::PresentModeKHR> m_SurfacePresentationModes;
};

