#include "pipeline.h"
#include "../utils/file.h"

Pipeline::Pipeline(const std::string& vert_path, const std::string& frag_path) : m_vert_path(vert_path), m_frag_path(frag_path) {
    create_graphics_pipeline();
}

void Pipeline::create_graphics_pipeline() {
    auto vert_code = read_file(m_vert_path);
    auto frag_code = read_file(m_frag_path);
    
    VkShaderModule vertModule = create_shader_module(vert_code);
    VkPipelineShaderStageCreateInfo vertStage{};
    vertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertStage.module = vertModule;
    vertStage.pName = "main";

    VkShaderModule fragModule = create_shader_module(frag_code);
    VkPipelineShaderStageCreateInfo fragStage{};
    fragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragStage.module = fragModule;
    fragStage.pName = "main";

    // todo
}

VkShaderModule Pipeline::create_shader_module(const std::vector<char>& code) {
    return nullptr;
}