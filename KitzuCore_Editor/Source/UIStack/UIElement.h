//
// Created by lucac on 04/06/2024.
//

#ifndef UIELEMENT_H
#define UIELEMENT_H
#include <imgui/imgui.h>
class UIElement {
public:

    virtual void Update() {
    };

    virtual void Render() {
    };

    virtual void Clean() {
    };

    virtual void Open() {
    };

    virtual void Close() {
    }

protected:
    bool m_bOpen = false;
};
#endif //UIELEMENT_H
