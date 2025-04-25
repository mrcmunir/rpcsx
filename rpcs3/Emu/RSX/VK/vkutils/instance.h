#pragma once

#include "../VulkanAPI.h"
#include "swapchain.h"

#include <vector>

#ifdef __APPLE__
#include <MoltenVK/mvk_vulkan.h>
#include <MoltenVK/mvk_private_api.h>
#endif

namespace vk
{
	class supported_extensions
	{
	private:
		std::vector<VkExtensionProperties> m_vk_exts;

	public:
		enum enumeration_class
		{
			instance = 0,
			device = 1
		};

		supported_extensions(enumeration_class _class, const char* layer_name = nullptr, VkPhysicalDevice pdev = VK_NULL_HANDLE);

		bool is_supported(std::string_view ext) const;
	};

	class instance
	{
	private:
		std::vector<physical_device> gpus;
		VkInstance m_instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;

		PFN_vkDestroyDebugReportCallbackEXT _vkDestroyDebugReportCallback = nullptr;
		PFN_vkCreateDebugReportCallbackEXT _vkCreateDebugReportCallback = nullptr;
		VkDebugReportCallbackEXT m_debugger = nullptr;

#ifdef ANDROID
		bool owns_loader = false;
#endif

		bool extensions_loaded = false;

	public:
#ifdef ANDROID
		static void* g_vk_loader;

		static void* get_vk_loader()
		{
			return g_vk_loader;
		}
#endif
		instance() = default;

		~instance();

		void destroy();

		void enable_debugging();

		bool create(const char* app_name, bool fast = false);

		void bind();

		std::vector<physical_device>& enumerate_devices();

		swapchain_base* create_swapchain(display_handle_t window_handle, vk::physical_device& dev);
	};
} // namespace vk
