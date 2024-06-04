//
// Created by lucac on 04/06/2024.
//

#ifndef UILAYER_H
#define UILAYER_H
#include "UIStackManager.h"
#include "Elements/AssetView.h"
#include "Elements/Viewport.h"
#include "Elements/TopMenuBar.h"

class UILayer {
public:
    UILayer(){
        m_pUiManager = new UIStackManager();
        m_pAssetView = new AssetView(m_pUiManager);
        m_pTopMenuBar = new TopMenuBar(m_pUiManager);
        m_pViewport = new Viewport();
    }

    ~UILayer() {
        delete m_pUiManager;
        delete m_pAssetView;
        delete m_pViewport;
        delete m_pTopMenuBar;
    }

    Viewport* GetViewport() {
        return m_pViewport;
    }

    UIStackManager* GetManager() {
        return m_pUiManager;
    }

private:
    UIStackManager* m_pUiManager;
    AssetView* m_pAssetView;
    Viewport * m_pViewport;
    TopMenuBar* m_pTopMenuBar;
};
#endif //UILAYER_H
