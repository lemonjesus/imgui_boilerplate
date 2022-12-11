#ifndef _APP_STATE_H
#define _APP_STATE_H

// Struct that holds the application's state
struct AppState {
  float f = 0.0f;
  int counter = 0;

  enum class RocketState {
    Init,
    Preparing,
    Launched
  };

  float rocket_progress = 0.f;
  RocketState rocketState;
  HelloImGui::Widgets::Logger* logger;
};

#endif