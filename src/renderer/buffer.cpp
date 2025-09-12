#include "buffer.h"

#include <iostream>
#include <cstring>

bool VulkanBuffer::init(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
    m_size = size;
    if (!create_buffer(physical_device, device, size, usage, properties)) {
        return false;
    }

    if (!alloc_memory(physical_device, device, size, properties)) {
        return false;
    }
    return true;
}

bool VulkanBuffer::create_buffer(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = size;
    bufferCreateInfo.usage = usage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VkResult result = vkCreateBuffer(device, &bufferCreateInfo, nullptr, &m_buffer);
    if (result != VK_SUCCESS) {
        std::cout << "Failed to create Vulkan buffer!\n";
        return false;
    }
    return true;
}

bool VulkanBuffer::alloc_memory(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkMemoryPropertyFlags properties) {
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, m_buffer, &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo{};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = find_memory_type(physical_device, memoryRequirements.memoryTypeBits, properties);

    VkResult result = vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &m_memory);
    if (result != VK_SUCCESS) {
        std::cout << "Failed to allocate memory for Vulkan buffer!\n";
        return false;
    }

    vkBindBufferMemory(device, m_buffer, m_memory, 0);
    return true;
}

uint32_t VulkanBuffer::find_memory_type(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physical_device, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
        if ((type_filter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }
    std::cout << "Failed to find suitable memory type!\n";
    return -1;
}

void VulkanBuffer::copy_data(VkDevice device, const void* data) {
    void* mappedData;
    vkMapMemory(device, m_memory, 0, m_size, 0, &mappedData);
    memcpy(mappedData, data, m_size);
    vkUnmapMemory(device, m_memory);
}

void VulkanBuffer::deinit(VkDevice device) {
    if (m_buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(device, m_buffer, nullptr);
        m_buffer = VK_NULL_HANDLE;
    }
    if (m_memory != VK_NULL_HANDLE) {
        vkFreeMemory(device, m_memory, nullptr);
        m_memory = VK_NULL_HANDLE;
    }
}

VkBuffer VulkanBuffer::get_buffer() const {
    return m_buffer;
}

VkDeviceSize VulkanBuffer::get_size() const {
    return m_size;
}