#include "RenderDevice.h"



RenderDevice::RenderDevice()
{
}


RenderDevice::RenderDevice(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR* surface)
{

	for (uint32_t i = 0; i < physicalDevice.getQueueFamilyProperties().size(); i++) {
		QueueFamilyData q;
		q.supportsPresentation = physicalDevice.getSurfaceSupportKHR(i, *surface);

		if (physicalDevice.getQueueFamilyProperties().at(i).queueFlags & vk::QueueFlagBits::eGraphics) {
			q.supportsGraphics = true;
		}

		q.queueCount = physicalDevice.getQueueFamilyProperties().at(i).queueCount;
		queueFamilies.push_back(q);
	}

	m_SurfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(*surface);
	m_SurfaceFormats = physicalDevice.getSurfaceFormatsKHR(*surface);
	m_SurfacePresentationModes = physicalDevice.getSurfacePresentModesKHR(*surface);


}

RenderDevice::~RenderDevice()
{
}

vk::SurfaceCapabilitiesKHR RenderDevice::getSurfaceCapabilities()
{
	return m_SurfaceCapabilities;
}
