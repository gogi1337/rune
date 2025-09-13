#include "../window.h"

#include <vector>
#include <optional>
#include <vulkan/vulkan.h>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool is_complete();
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

bool check_device_extension_support(VkPhysicalDevice device);
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data, void *p_user_data);
VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *p_create_info, const VkAllocationCallbacks *p_allocator, VkDebugUtilsMessengerEXT *p_debug_messenger);
void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks *p_allocator);

struct Device {
#ifdef NDEBUG
    const bool enable_validation_layers = false;
#else
    const bool enable_validation_layers = true;
#endif

    Device(Window &window);
    ~Device();

    // Not copyable or movable
    Device(const Device &) = delete;
    Device &operator=(const Device &) = delete;
    Device(Device &&) = delete;
    Device &operator=(Device &&) = delete;

    VkCommandPool get_command_pool() { return m_command_pool; }
    VkDevice device() { return m_device; }
    VkSurfaceKHR surface() { return m_surface; }
    VkQueue graphics_queue() { return m_graphics_queue; }
    VkQueue present_queue() { return m_present_queue; }

    SwapChainSupportDetails get_swap_chain_support();
    uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);
    QueueFamilyIndices find_physical_queue_families();
    VkFormat find_supported_format(
        const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features
    );

    // Maybe should use only buffer.h or implement them there - idk
    // void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &buffer_memory);
    // VkCommandBuffer begin_single_time_commands();
    // void end_single_time_commands(VkCommandBuffer command_buffer);
    // void copy_buffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
    // void copy_buffer_to_image(
    //     VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layer_count);

    // void create_image_with_info(
    //     const VkImageCreateInfo &image_info,
    //     VkMemoryPropertyFlags properties,
    //     VkImage &image,
    //     VkDeviceMemory &image_memory);

    VkPhysicalDeviceProperties m_properties;

    private:
    VkInstance m_instance;
    VkDebugUtilsMessengerEXT m_debug_messenger;
    VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
    Window &m_window;
    VkCommandPool m_command_pool;

    VkDevice m_device;
    VkSurfaceKHR m_surface;
    VkQueue m_graphics_queue;
    VkQueue m_present_queue;

    const std::vector<const char *> m_validation_layers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> m_device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    void create_instance();
    void setup_debug_messenger();
    void create_surface();
    void pick_physical_device();
    void create_logical_device();
    void create_command_pool();
    bool is_device_suitable(VkPhysicalDevice device);
    std::vector<const char *> get_required_extensions();
    bool check_validation_layer_support();
    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
    void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info);
    void has_glfw_required_instance_extensions();
    bool check_device_extension_support(VkPhysicalDevice device);
    SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
};