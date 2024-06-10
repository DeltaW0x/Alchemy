//
// Created by lucac on 08/06/2024.
//


#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <utility>
#include "../Components/InputComponent.h"

inline void QueryInputState(InputStateComponent *component) {
    memcpy(component->previousKeyboardState, component->currentKeyboardState, sizeof(component->currentKeyboardState));
    component->currentKeyboardState = SDL_GetKeyboardState(nullptr);

    component->previousButtonMask = component->currentButtonMask;
    memcpy(component->previousPosition, component->currentPosition, sizeof(component->currentPosition));
    component->currentButtonMask = SDL_GetMouseState(&component->currentPosition[0], &component->currentPosition[1]);

    if (component->connected) {
        memcpy(component->previousGamepadState, component->currentGamepadState, sizeof(component->currentGamepadState));
        for (int i = 0; i < SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MAX; i++) {
            component->currentGamepadState[i] = SDL_GetGamepadButton(component->gamepad,
                                                                     static_cast<SDL_GamepadButton>(i));
        }
        for (int i = 0; i < SDL_GamepadAxis::SDL_GAMEPAD_AXIS_MAX; i++) {
            component->axisState[i] = SDL_GetGamepadAxis(component->gamepad, static_cast<SDL_GamepadAxis>(i));
        }
    }
}

#endif //INPUT_H
