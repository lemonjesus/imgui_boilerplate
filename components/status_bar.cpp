#include "../app_state.h"
#include "components.cpp"

class StatusBar : public Component {
    public:
    
    StatusBar() : Component() {}
    void render(AppState* appState, void* componentState) override {
        if (appState->rocketState == AppState::RocketState::Preparing) {
            ImGui::Text("Rocket completion: ");
            ImGui::SameLine();
            ImGui::ProgressBar(appState->rocket_progress, ImVec2(100.f, 15.f));
        }
    }
};
