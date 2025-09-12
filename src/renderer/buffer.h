#pragma once

#include <vulkan/vulkan.h>
#include <vector>

struct VulkanBuffer {
public:
    VkBuffer m_buffer = VK_NULL_HANDLE;
    VkDeviceMemory m_memory = VK_NULL_HANDLE;
    VkDeviceSize m_size = 0;
    bool init(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    void copy_data(VkDevice device, const void* data);
    void deinit(VkDevice device);
    VkBuffer get_buffer() const;
    VkDeviceSize get_size() const;

private:
    bool create_buffer(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    bool alloc_memory(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkMemoryPropertyFlags properties);
    uint32_t find_memory_type(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties);
};