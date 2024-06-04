//
// Created by lucac on 05/06/2024.
//

#ifndef TOPMENUBAR_H
#define TOPMENUBAR_H
#include "../UIStackManager.h"

class TopMenuBar : public UIElement {
public:
    TopMenuBar(UIStackManager *uiManager) : m_pUiManager(uiManager) {
        m_pUiManager->AddElement("menu_bar", this);
    }

    void Render() override {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("Edit")) {
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("Help")) {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

private:
    UIStackManager *m_pUiManager;
};
#endif //TOPMENUBAR_H
