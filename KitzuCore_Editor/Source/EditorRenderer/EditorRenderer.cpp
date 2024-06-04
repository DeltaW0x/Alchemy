//
// Created by lucac on 04/06/2024.
//

#include "EditorRenderer.h"

EditorRenderer::EditorRenderer(SDL_Window *window, UIStackManager *uiManager) : m_pUiStackManager(uiManager) {
    m_pLowLevelRenderer = new Renderer(window, SDL_GPU_BACKEND_VULKAN, SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
                                       SDL_GPU_SAMPLECOUNT_1,
                                       SDL_GPU_PRESENTMODE_VSYNC);

#pragma region ImGui Setup
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    SetupImGuiStyle();

    ImGui_ImplSDLGpu_InitInfo initInfo = {};
    initInfo.Device = m_pLowLevelRenderer->GetDevice();
    initInfo.Window = window;
    initInfo.SwapchainComposition = m_pLowLevelRenderer->GetSwapchainComposition();
    initInfo.WindowPresentMode = m_pLowLevelRenderer->GetPresentMode();
    initInfo.MSAASamples = SDL_GPU_SAMPLECOUNT_1;

    ImGui_ImplSDLGpu_Init(&initInfo);
    ImGui_ImplSDL3_InitForOther(window);

#pragma endregion

    m_pHdrRenderTargetInfo.isCube = false;
    m_pHdrRenderTargetInfo.depth = 1;
    m_pHdrRenderTargetInfo.width = 100;
    m_pHdrRenderTargetInfo.height = 100;
    m_pHdrRenderTargetInfo.layerCount = 1;
    m_pHdrRenderTargetInfo.levelCount = 1;
    m_pHdrRenderTargetInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_pHdrRenderTargetInfo.format = SDL_GPU_TEXTUREFORMAT_R16G16B16A16;
    m_pHdrRenderTargetInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
    m_pHdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pHdrRenderTargetInfo);

    m_pSdrRenderTargetInfo.isCube = false;
    m_pSdrRenderTargetInfo.depth = 1;
    m_pSdrRenderTargetInfo.width = 100;
    m_pSdrRenderTargetInfo.height = 100;
    m_pSdrRenderTargetInfo.layerCount = 1;
    m_pSdrRenderTargetInfo.levelCount = 1;
    m_pSdrRenderTargetInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_pSdrRenderTargetInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8;
    m_pSdrRenderTargetInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
    m_pSdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pSdrRenderTargetInfo);

    SDL_GpuSamplerCreateInfo samplerInfo = {};
    samplerInfo.minFilter = SDL_GPU_FILTER_LINEAR;
    samplerInfo.magFilter = SDL_GPU_FILTER_LINEAR;
    samplerInfo.mipmapMode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR;
    samplerInfo.addressModeU = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.anisotropyEnable = SDL_FALSE;
    samplerInfo.compareEnable = SDL_FALSE;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 1.0f;
    m_pViewportTextureSampler = SDL_GpuCreateSampler(m_pLowLevelRenderer->GetDevice(), &samplerInfo);
}

void EditorRenderer::BeginDraw() {
    m_pLowLevelRenderer->BeginDraw();
    m_pMainCmdBuffer = SDL_GpuAcquireCommandBuffer(m_pLowLevelRenderer->GetDevice());
    if (m_Viewport.ViewportSizeChanged(&m_currentViewportSize)) {
        SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pHdrRenderTarget);
        SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pSdrRenderTarget);
        m_pHdrRenderTargetInfo.width  = (u32) m_currentViewportSize.x;
        m_pHdrRenderTargetInfo.height = (u32) m_currentViewportSize.y;
        m_pSdrRenderTargetInfo.width  = (u32) m_currentViewportSize.x;
        m_pSdrRenderTargetInfo.height = (u32) m_currentViewportSize.y;

        m_pHdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pHdrRenderTargetInfo);
        m_pSdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pSdrRenderTargetInfo);
    }

    SDL_GpuColorAttachmentInfo hdrAttachmentInfoClear = {};
    hdrAttachmentInfoClear.loadOp = SDL_GPU_LOADOP_CLEAR;
    hdrAttachmentInfoClear.storeOp = SDL_GPU_STOREOP_STORE;
    hdrAttachmentInfoClear.clearColor = {1,0,0,1};
    hdrAttachmentInfoClear.cycle = SDL_TRUE;
    hdrAttachmentInfoClear.textureSlice.texture = m_pHdrRenderTarget;

    SDL_GpuRenderPass * clearPass = SDL_GpuBeginRenderPass(m_pMainCmdBuffer,&hdrAttachmentInfoClear,1,{});
    SDL_GpuEndRenderPass(clearPass);

    SDL_GpuTextureRegion hdrTexRegion = {};
    hdrTexRegion.w = m_currentViewportSize.x;
    hdrTexRegion.h = m_currentViewportSize.y;
    hdrTexRegion.d = 1;
    hdrTexRegion.textureSlice.texture = m_pHdrRenderTarget;

    SDL_GpuTextureRegion sdrTexRegion = {};
    sdrTexRegion.w = m_currentViewportSize.x;
    sdrTexRegion.h = m_currentViewportSize.y;
    sdrTexRegion.d = 1;
    sdrTexRegion.textureSlice.texture = m_pSdrRenderTarget;

    SDL_GpuBlit(m_pMainCmdBuffer,&hdrTexRegion,&sdrTexRegion,SDL_GPU_FILTER_LINEAR,SDL_TRUE);
    SDL_GpuSubmit(m_pMainCmdBuffer);

}

void EditorRenderer::DrawUI() {
    ImGui_ImplSDLGpu_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
    m_binding = {m_pSdrRenderTarget,m_pViewportTextureSampler};
    m_Viewport.Render(&m_binding);
    m_pUiStackManager->RenderAllElements();
    ImGui::Render();

    SDL_GpuColorAttachmentInfo swapchainAttachmentInfo = {};
    swapchainAttachmentInfo.loadOp = SDL_GPU_LOADOP_LOAD;
    swapchainAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
    swapchainAttachmentInfo.textureSlice.texture = m_pLowLevelRenderer->GetSwapchainTexture();
    swapchainAttachmentInfo.textureSlice.mipLevel = 0;
    swapchainAttachmentInfo.textureSlice.layer = 0;
    swapchainAttachmentInfo.cycle = SDL_TRUE;

    SDL_GpuRenderPass *imguiRenderPass = SDL_GpuBeginRenderPass(m_pLowLevelRenderer->GetMainCommandBuffer(),
                                                                &swapchainAttachmentInfo, 1, {});
    ImGui_ImplSDLGpu_RenderDrawData(ImGui::GetDrawData(), imguiRenderPass);
    SDL_GpuEndRenderPass(imguiRenderPass);
}

void EditorRenderer::EndDraw() {
    DrawUI();
    m_pLowLevelRenderer->EndDraw();
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void EditorRenderer::Clean() {
    m_pLowLevelRenderer->Clean();
}

void EditorRenderer::SetupImGuiStyle() {
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_MenuBarBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Border
    colors[ImGuiCol_Border] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_BorderShadow] = ImVec4{0.0f, 0.0f, 0.0f, 0.24f};

    // Text
    colors[ImGuiCol_Text] = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
    colors[ImGuiCol_TextDisabled] = ImVec4{0.5f, 0.5f, 0.5f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_CheckMark] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{0.1f, 0.1f, 0.13f, 0.92f};

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{0.44f, 0.37f, 0.61f, 0.54f};
    colors[ImGuiCol_SliderGrabActive] = ImVec4{0.74f, 0.58f, 0.98f, 0.54f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.13f, 0.13, 0.17, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.24, 0.24f, 0.32f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.2f, 0.22f, 0.27f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{0.24f, 0.24f, 0.32f, 1.0f};

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
    colors[ImGuiCol_SeparatorActive] = ImVec4{0.84f, 0.58f, 1.0f, 1.0f};

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{0.74f, 0.58f, 0.98f, 0.29f};
    colors[ImGuiCol_ResizeGripActive] = ImVec4{0.84f, 0.58f, 1.0f, 0.29f};

    // Docking
    colors[ImGuiCol_DockingPreview] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};

    auto &style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;
}
