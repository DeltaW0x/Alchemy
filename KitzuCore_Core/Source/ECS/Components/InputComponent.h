//
// Created by lucac on 08/06/2024.
//

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>

struct InputStateComponent{

    InputStateComponent() {
        int size;
        currentKeyboardState = SDL_GetKeyboardState(&size);
        previousKeyboardState =(uint8_t *) calloc(size, sizeof(uint8_t*));

        memset(previousGamepadState,0,sizeof(previousGamepadState));
    }
    bool init = false;

    const uint8_t* currentKeyboardState = nullptr;
    uint8_t* previousKeyboardState = nullptr;

    uint32_t currentButtonMask;
    uint32_t previousButtonMask;

    float currentPosition[2] = {0,0};
    float previousPosition[2] = {0,0};

    SDL_Gamepad* gamepad;
    uint8_t connected = 0;
    uint8_t currentGamepadState[SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MAX];
    uint8_t previousGamepadState[SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MAX];
    int16_t axisState[SDL_GamepadAxis::SDL_GAMEPAD_AXIS_MAX];
};

#endif //INPUTCOMPONENT_H
