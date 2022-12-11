#include "../app_state.h"
#include "components.cpp"

class MainWindow : public Component {
    public:
    
    MainWindow() : Component() {}
    void render(AppState* appState, void* componentState) override {
        ImGui::ShowDemoWindow();
    }
};