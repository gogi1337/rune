#include "pipeline.h"
#include "../utils/file.h"

Pipeline::Pipeline(const std::string& vert_path, const std::string& frag_path, PipelineConfigInfo config) : m_vert_path(vert_path), m_frag_path(frag_path) {
    create_graphics_pipeline();
}

void Pipeline::create_graphics_pipeline() {
    auto vert_code = read_file(m_vert_path);
    auto frag_code = read_file(m_frag_path);
    
    create_shader_module(vert_code, &m_vert_shader_module);
    VkPipelineShaderStageCreateInfo vertStage{};
    vertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertStage.module = m_vert_shader_module;
    vertStage.pName = "main";

    create_shader_module(frag_code, &m_frag_shader_module);
    VkPipelineShaderStageCreateInfo fragStage{};
    fragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragStage.module = m_frag_shader_module;
    fragStage.pName = "main";

    // todo
}

void Pipeline::create_shader_module(const std::vector<char>& code, VkShaderModule* shader_module) {
    // todo
}