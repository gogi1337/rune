#pragma once

#include <string>
#include <vulkan/vulkan.h>

struct PipelineConfigInfo {

};

struct Pipeline {
    std::string m_vert_path;
    std::string m_frag_path;

    Pipeline(const std::string& vert_path, const std::string& frag_path, PipelineConfigInfo config);
    
    void create_graphics_pipeline();
    void create_shader_module(const std::vector<char>& code, VkShaderModule* shader_module);

    private:
    VkPipeline m_graphics_pipeline;
    VkShaderModule m_vert_shader_module;
    VkShaderModule m_frag_shader_module;
};