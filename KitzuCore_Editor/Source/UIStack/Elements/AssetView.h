//
// Created by lucac on 04/06/2024.
//

#ifndef ASSETVIEW_H
#define ASSETVIEW_H
#include "../UIStackManager.h"

class AssetView : public UIElement {
public:
    AssetView(UIStackManager *uiManager) : m_pUiManager(uiManager) {
        m_pUiManager->AddElement("asset_view", this);
        m_bOpen = true;
    }

    void Render() override {
        if(m_bOpen) {
            ImGui::Begin("Asset Viewer",&m_bOpen);
            ImGui::End();
        }
    }

private:
    UIStackManager *m_pUiManager;
};
#endif //ASSETVIEW_H
