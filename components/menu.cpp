#include "../app_state.h"
#include "components.cpp"

class Menu : public Component {
    public:
    
    Menu() : Component() {}
    void render(AppState* appState, void* componentState) override {
        if (ImGui::BeginMenu("My Menu")) {
            if (ImGui::MenuItem("Test me")) appState->logger->warning("It works");
            ImGui::EndMenu();
        }
    }
};
