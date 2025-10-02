#ifndef GUI_H
#define GUI_H

#include <string>

// GUI state structure
struct GUIState {
    std::string password;
    int passwordLength;
    bool showPassword;
    char lengthInputBuffer[4];
    bool lengthInputActive;
};

// Initialize GUI state
void initGUI(GUIState& state);

// Run the GUI main loop
void runGUI();

#endif // GUI_H