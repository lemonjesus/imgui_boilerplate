#include "../app_state.h"
#include "components.cpp"

class Sidebar : public Component {
    public:
    
    Sidebar() : Component() {}
    void render(AppState* appState, void* componentState) override {
        ImGui::TextWrapped("The font below was loaded from the application assets folder (those files are embedded automatically).");
        ImGui::TextWrapped("Hello, Dear ImGui! " ICON_FA_SMILE);
        ImGui::Separator();

        // Edit 1 float using a slider from 0.0f to 1.0f
        if (ImGui::SliderFloat("float", &(appState->f), 0.0f, 1.0f))
            appState->logger->warning("state.f was changed to %f", appState->f);

        // Buttons return true when clicked (most widgets return true when edited/activated)
        if (ImGui::Button("Button")) {
            appState->counter++;
            appState->logger->info("Button was pressed", appState->f);
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", appState->counter);

        switch(appState->rocketState) {
        case AppState::RocketState::Init:
            if (ImGui::Button(ICON_FA_ROCKET " Launch rocket")) {
                appState->rocketState = AppState::RocketState::Preparing;
                appState->logger->warning("Rocket is being prepared");
            }
            break;
        case AppState::RocketState::Preparing:
            ImGui::Text(ICON_FA_ROCKET " Please Wait");
            appState->rocket_progress += 0.003f;
            if (appState->rocket_progress >= 1.f) {
                appState->rocketState = AppState::RocketState::Launched;
                appState->logger->warning("Rocket was launched!");
            }
            break;
        case AppState::RocketState::Launched:
            ImGui::Text(ICON_FA_ROCKET " Rocket Launched");
            if (ImGui::Button("Reset Rocket")) {
                appState->rocketState = AppState::RocketState::Init;
                appState->rocket_progress = 0.f;
            }
            break;
        }
    }
};