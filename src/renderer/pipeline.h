#pragma once

#include "device.h"

#include <string>
#include <vector>
#include <vulkan/vulkan.h>

struct PipelineConfigInfo {
    PipelineConfigInfo() = default;
    PipelineConfigInfo(const PipelineConfigInfo&) = delete;
    PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

    std::vector<VkVertexInputBindingDescription> binding_descriptions{};
    std::vector<VkVertexInputAttributeDescription> attribute_descriptions{};
    VkPipelineViewportStateCreateInfo viewport_info;
    VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
    VkPipelineRasterizationStateCreateInfo rasterization_info;
    VkPipelineMultisampleStateCreateInfo multisample_info;
    VkPipelineColorBlendAttachmentState color_blend_attachment;
    VkPipelineColorBlendStateCreateInfo color_blend_info;
    VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
    std::vector<VkDynamicState> dynamic_state_enables;
    VkPipelineDynamicStateCreateInfo dynamics_state_info;
    VkPipelineLayout pipeline_layout = nullptr;
    VkRenderPass renderpass = nullptr;
    uint32_t subpass = 0;
};

struct Pipeline {
    std::string m_vert_path;
    std::string m_frag_path;
    
    Pipeline(Device& device, const std::string& vert_path, const std::string& frag_path, PipelineConfigInfo config);
    ~Pipeline();
    
    void create_graphics_pipeline();
    void create_shader_module(const std::vector<char>& code, VkShaderModule* shader_module);
    void default_config_info(PipelineConfigInfo config_info);
    void bind(VkCommandBuffer command_buffer);
    
    private:
    Device& m_device;
    VkPipeline m_graphics_pipeline;
    VkShaderModule m_vert_shader_module;
    VkShaderModule m_frag_shader_module;
};