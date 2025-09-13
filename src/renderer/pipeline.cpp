#include "pipeline.h"
#include "../utils/file.h"

#include <stdexcept>

Pipeline::Pipeline(Device& device, const std::string& vert_path, const std::string& frag_path, PipelineConfigInfo config) : m_vert_path(vert_path), m_frag_path(frag_path), m_device(device) {
    create_graphics_pipeline();
}

Pipeline::~Pipeline() {
    vkDestroyShaderModule(m_device.device(), m_vert_shader_module, nullptr);
    vkDestroyShaderModule(m_device.device(), m_frag_shader_module, nullptr);
    vkDestroyPipeline(m_device.device(), m_graphics_pipeline, nullptr);
}

void Pipeline::create_graphics_pipeline() {
    auto vert_code = read_file(m_vert_path);
    auto frag_code = read_file(m_frag_path);
    
    create_shader_module(vert_code, &m_vert_shader_module);
    VkPipelineShaderStageCreateInfo vert_stage{};
    vert_stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_stage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_stage.module = m_vert_shader_module;
    vert_stage.pName = "main";

    create_shader_module(frag_code, &m_frag_shader_module);
    VkPipelineShaderStageCreateInfo frag_stage{};
    frag_stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_stage.module = m_frag_shader_module;
    frag_stage.pName = "main";

    // todo
}

void Pipeline::create_shader_module(const std::vector<char>& code, VkShaderModule* shader_module) {
    VkShaderModuleCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code.size();
    create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(m_device.device(), &create_info, nullptr, shader_module) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module");
    }
}

void Pipeline::default_config_info(PipelineConfigInfo config_info) {
    // todo
}

void Pipeline::bind(VkCommandBuffer command_buffer) {
    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphics_pipeline);
}