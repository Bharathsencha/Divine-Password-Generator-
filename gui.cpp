#include "gui.h"
#include "generator.h"
#include "raylib.h"
#include <cstring>
#include <string>

void initGUI(GUIState& state) {
    state.password = "";
    state.passwordLength = 16; // Start with a strong default
    state.showPassword = false;
    strcpy(state.lengthInputBuffer, "16");
    state.lengthInputActive = false;
}

void runGUI() {
    const int screenWidth = 600;
    const int screenHeight = 500;
    
    InitWindow(screenWidth, screenHeight, "Password Generator");
    SetTargetFPS(60);
    
    GUIState state;
    initGUI(state);
    
    Rectangle generateButton = {200, 300, 200, 50};
    Rectangle copyButton = {200, 370, 200, 50};
    Rectangle lengthInputBox = {250, 150, 100, 40};
    
    int framesCounter = 0;
    
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        
        // Handle length input box activation
        if (CheckCollisionPointRec(mousePos, lengthInputBox)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state.lengthInputActive = true;
            }
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state.lengthInputActive = false;
            }
        }
        
        // Handle text input when active
        if (state.lengthInputActive) {
            framesCounter++;
            
            // Get character pressed
            int key = GetCharPressed();
            while (key > 0) {
                // Only allow numbers and limit to 4 digits (for max 9999)
                if ((key >= '0' && key <= '9') && strlen(state.lengthInputBuffer) < 3) {
                    int len = strlen(state.lengthInputBuffer);
                    state.lengthInputBuffer[len] = (char)key;
                    state.lengthInputBuffer[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            
            // Handle backspace
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int len = strlen(state.lengthInputBuffer);
                if (len > 0) {
                    state.lengthInputBuffer[len - 1] = '\0';
                }
            }
            
            // Update password length from buffer
            if (strlen(state.lengthInputBuffer) > 0) {
                int inputVal = atoi(state.lengthInputBuffer);
                // Clamp between 12 and 999
                if (inputVal >= 12 && inputVal <= 999) {
                    state.passwordLength = inputVal;
                } else if (inputVal > 999) {
                    strcpy(state.lengthInputBuffer, "999");
                    state.passwordLength = 999;
                }
            }
        } else {
            framesCounter = 0;
        }
        
        // Generate button logic
        if (CheckCollisionPointRec(mousePos, generateButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Make sure we have a valid length (minimum 12 for security)
                if (strlen(state.lengthInputBuffer) == 0 || state.passwordLength < 12) {
                    state.passwordLength = 12;
                    strcpy(state.lengthInputBuffer, "12");
                }
                state.password = generatePassword(state.passwordLength);
                state.showPassword = true;
            }
        }
        
        // Copy button logic
        if (state.showPassword && CheckCollisionPointRec(mousePos, copyButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SetClipboardText(state.password.c_str());
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Title
        DrawText("Password Generator", 150, 30, 30, DARKBLUE);
        
        // Password length label
        DrawText("Password Length (12-999):", 195, 120, 20, DARKGRAY);
        
        // Password length input box
        DrawRectangleRec(lengthInputBox, state.lengthInputActive ? LIGHTGRAY : WHITE);
        DrawRectangleLinesEx(lengthInputBox, 2, state.lengthInputActive ? BLUE : DARKGRAY);
        
        // Draw input text
        DrawText(state.lengthInputBuffer, lengthInputBox.x + 10, lengthInputBox.y + 10, 20, BLACK);
        
        // Draw blinking cursor when active
        if (state.lengthInputActive) {
            if ((framesCounter / 20) % 2 == 0) {
                int textWidth = MeasureText(state.lengthInputBuffer, 20);
                DrawText("_", lengthInputBox.x + 10 + textWidth, lengthInputBox.y + 10, 20, BLACK);
            }
        }
        
        // Generate button
        Color btnColor = CheckCollisionPointRec(mousePos, generateButton) ? DARKBLUE : BLUE;
        DrawRectangleRec(generateButton, btnColor);
        DrawText("GENERATE", 235, 315, 20, WHITE);
        
        // Display password
        if (state.showPassword) {
            DrawRectangle(50, 220, 500, 50, LIGHTGRAY);
            DrawRectangleLinesEx({50, 220, 500, 50}, 2, DARKGRAY);
            DrawText(state.password.c_str(), 60, 235, 20, DARKGREEN);
            
            // Copy button
            Color copyBtnColor = CheckCollisionPointRec(mousePos, copyButton) ? DARKGREEN : GREEN;
            DrawRectangleRec(copyButton, copyBtnColor);
            DrawText("COPY", 265, 385, 20, WHITE);
        }
        
        // Instructions
        DrawText("Click the input box, clear it, and type your desired length", 100, 440, 15, GRAY);
        DrawText("Then click GENERATE to create password", 145, 460, 15, GRAY);
        
        EndDrawing();
    }
    
    CloseWindow();
}