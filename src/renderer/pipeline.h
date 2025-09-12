#pragma once

#include <string>
#include <vulkan/vulkan.h>

struct Pipeline {
    std::string m_vert_path;
    std::string m_frag_path;

    Pipeline(const std::string& vert_path, const std::string& frag_path);
    
    void create_graphics_pipeline();
    VkShaderModule create_shader_module(const std::vector<char>& code);
};