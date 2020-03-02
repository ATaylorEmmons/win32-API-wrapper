#include <iostream>

#include "Vulkan.hpp"

#include <windows.h>


#include "VulkanAPI.h"

#include "Win32Base.h"
#include "Loop.h"

#include "InputState.h"

int main() {

	Win32Base window("My Favorite Pizza Place", 800, 600);
	VulkanAPI vk;

	Loop loop;
	
	window.init(&loop);
	
	//vk.attachSurface(window.CreateSurface(vk.getInstance()));

	//RenderDevice activeDevice = vk.getDevice(0);

	//std::cout << "Vulkans Viewed Width: " << activeDevice.getSurfaceCapabilities().currentExtent.width << std::endl;
	//std::cout << "Vulkans Viewed Height: " << activeDevice.getSurfaceCapabilities().currentExtent.height << std::endl;

	window.start();

	char c;
	std::cin >>  c;
}