//
// Created by lucac on 04/06/2024.
//

#ifndef VIEWPORT_H
#define VIEWPORT_H
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdlgpu.h>
#include <Miscellaneous/Assert.h>
class Viewport {
public:
    Viewport() = default;

    bool ViewportSizeChanged(ImVec2* newSize) const {
        *newSize = m_currentViewportSize;
        return m_bSizeChanged;
    }

    void Render(SDL_GpuTextureSamplerBinding* binding) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0,0));
        ImGui::Begin("Viewport Example");
        m_currentViewportSize = ImGui::GetContentRegionAvail();
        if(m_currentViewportSize.x != m_previousViewportSize.x || m_currentViewportSize.y != m_previousViewportSize.y) {
            if(m_currentViewportSize.x > 0 && m_currentViewportSize.y > 0 ) {
                m_previousViewportSize = m_currentViewportSize;
                m_bSizeChanged = true;
                INFO("The viewport changed size: {0}, {1}", m_currentViewportSize.x, m_currentViewportSize.y);
            }
        }
        else {
            m_bSizeChanged = false;
        }

        ImGui::Image(binding,m_currentViewportSize);
        ImGui::End();
        ImGui::PopStyleVar();
    }

private:
    ImVec2 m_previousViewportSize = ImVec2(0, 0);
    ImVec2 m_currentViewportSize = ImVec2(100, 100);
    bool m_bSizeChanged = true;
};
#endif //VIEWPORT_H
