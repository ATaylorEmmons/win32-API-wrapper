#include "VulkanAPI.h"



VulkanAPI::VulkanAPI()
{
	/*
	
		Application Info
	
	*/
	vk::ApplicationInfo applicationInfo;
	applicationInfo.apiVersion = VK_MAKE_VERSION(1, 1, 94);
	applicationInfo.pEngineName = "LUCEAT";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_API_VERSION_1_1;

	vk::InstanceCreateInfo instanceInfo;
	instanceInfo.pApplicationInfo = &applicationInfo;
	
	/*
	
		Layers and Exts

	*/
	instanceInfo.enabledLayerCount = INSTANCE_LAYERS.size();
	instanceInfo.ppEnabledLayerNames = INSTANCE_LAYERS.data();
	
	instanceInfo.enabledExtensionCount = INSTANCE_EXTS.size();
	instanceInfo.ppEnabledExtensionNames = INSTANCE_EXTS.data();
	
	m_Instance = vk::createInstance(instanceInfo);

#ifdef DEBUG
	registerDebug();
#endif

}


VulkanAPI::~VulkanAPI()
{
	m_Instance.destroySurfaceKHR(*m_Surface);
	delete m_Surface;

	DestroyDebugUtilsMessengerEXT(static_cast<VkInstance>(m_Instance), callback, nullptr);
	m_Instance.destroy();
	
}

vk::Instance * VulkanAPI::getInstance()
{
	return &m_Instance;
}

void VulkanAPI::attachSurface(vk::SurfaceKHR* surface)
{
	this->m_Surface = surface;

	std::vector<vk::PhysicalDevice> physicalDevices = m_Instance.enumeratePhysicalDevices();
	for (int i = 0; i < physicalDevices.size(); i++) {

		m_RenderDevices.push_back(RenderDevice(physicalDevices.at(i), m_Surface));
	}
}

RenderDevice VulkanAPI::getDevice(int offset)
{
	return m_RenderDevices.at(offset);
}

void VulkanAPI::registerDebug() {


	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)debugCallback;
	createInfo.pUserData = nullptr; // Optional

	CreateDebugUtilsMessengerEXT(static_cast<VkInstance>(m_Instance), &createInfo, nullptr, &callback);

}

VkResult VulkanAPI::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pCallback)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void VulkanAPI::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks * pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanAPI::debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, vk::DebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	std::cout << "Validation Layer Report: " << std::endl;
	std::cout << "________________________" << std::endl;
	std::cout << pCallbackData->pMessage << std::endl;
	std::cout << "________________________" << std::endl;

	return VK_FALSE;
}