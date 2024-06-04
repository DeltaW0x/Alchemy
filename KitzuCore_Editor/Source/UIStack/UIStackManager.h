//
// Created by lucac on 04/06/2024.
//

#ifndef UISTACKMANAGER_H
#define UISTACKMANAGER_H
#include <unordered_map>
#include "UIElement.h"

class UIStackManager {

public:
    UIStackManager() = default;

    UIElement* GetElement(const char* name) {
        return m_uiElementMap[name];
    }

    void AddElement(const char *name, UIElement *element) {
        m_uiElementMap.insert(std::make_pair(name, element));
    }

    void RemoveElement(const char *name) {
        if (m_uiElementMap.count(name)) {
            m_uiElementMap.erase(name);
        }
    }

    void RenderAllElements() {
        for (auto &&element: m_uiElementMap) {
            element.second->Render();
        }
    }

    void Clean() {
        for (auto &&element: m_uiElementMap) {
            element.second->Clean();
        }
    }

private:
    std::unordered_map<const char *, UIElement *> m_uiElementMap;
};

#endif //UISTACKMANAGER_H
