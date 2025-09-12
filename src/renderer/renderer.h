#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <optional>
#include <set>
#include <fstream>

#include "../window.h"

struct Renderer {
    Window* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchain_images;
    VkFormat swapchain_image_format;
    VkExtent2D swapchain_extent;
    std::vector<VkImageView> swapchain_image_views;
    VkRenderPass render_pass;
    VkPipelineLayout pipeline_layout;
    VkPipeline graphics_pipeline;
    std::vector<VkFramebuffer> swapchain_framebuffers;
    VkCommandPool command_pool;
    std::vector<VkCommandBuffer> command_buffers;
    VkSemaphore image_available_semaphore;
    VkSemaphore render_finished_semaphore;
    VkDescriptorSetLayout descriptor_set_layout;

    // --- core ---
    void init_renderer(Window* wind);
    void init_vulkan();
    void deinit();

    // --- vulkan setup ---
    void create_instance();
    void create_surface();
    void pick_physical_device();
    uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void create_logical_device();
    void create_swapchain();
    void create_image_views();
    void create_renderpass();
    void create_graphics_pipeline();
    void create_framebuffers();
    void create_command_pool();
    // void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
    void create_command_buffers();
    void create_sync_objects();

    void device_wait_idle();
    void draw();

    // --- helpers ---
    VkShaderModule create_shader_module(const std::vector<char>& code);
};
