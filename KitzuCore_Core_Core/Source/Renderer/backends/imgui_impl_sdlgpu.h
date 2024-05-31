#ifndef IMGUI_IMPL_SDL_GPU
#define IMGUI_IMPL_SDL_GPU
#include "../imgui.h"
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL.h>
struct ImGui_ImplSDLGpu_InitInfo
{
    SDL_GpuDevice*                  Device;
    SDL_Window*                     Window;
    SDL_GpuRenderPass*              RenderPass;                                                
    SDL_GpuSampleCount              MSAASamples;
    SDL_GpuBackend                  GpuBackend;
    uint32_t                        ImageCount;
    void(*DebugCallback)(const char*);
};


IMGUI_IMPL_API bool         ImGui_ImplSDLGpu_Init(ImGui_ImplSDLGpu_InitInfo* info);
IMGUI_IMPL_API void         ImGui_ImplSDLGpu_NewFrame();
IMGUI_IMPL_API void         ImGui_ImplSDLGpu_RenderDrawData(ImDrawData* draw_data, SDL_GpuRenderPass* renderPass, SDL_GpuGraphicsPipeline* pipeline);
IMGUI_IMPL_API bool         ImGui_ImplSDLGpu_CreateFontsTexture();


#endif