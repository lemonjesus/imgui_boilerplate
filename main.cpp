#include "hello_imgui/hello_imgui.h"
#include "hello_imgui/widgets/logger.h"

#include "app_state.h"

#include "components/components.cpp"

#ifdef HELLOIMGUI_USE_SDL_OPENGL3
#include <SDL.h>
#endif

// MyLoadFonts: demonstrate
// * how to load additional fonts
// * how to use assets from the local assets/ folder
//   Files in the application assets/ folder are embedded automatically
//   (on iOS/Android/Emscripten)
ImFont * gAkronimFont = nullptr;
void MyLoadFonts() {
  // First, we load the default fonts (the font that was loaded first is the default font)
  HelloImGui::ImGuiDefaultSettings::LoadDefaultFont_WithFontAwesomeIcons();

  // Then we load a second font from
  // Since this font is in a local assets/ folder, it was embedded automatically
  std::string fontFilename = "fonts/Akronim-Regular.ttf";
  gAkronimFont = HelloImGui::LoadFontTTF_WithFontAwesomeIcons(fontFilename, 40.f);
}

int main(int, char **) {
  // Our application state
  AppState appState;

  Sidebar sidebar = Sidebar();
  MainWindow main_window = MainWindow();

  // Hello ImGui params (they hold the settings as well as the Gui callbacks)
  HelloImGui::RunnerParams runnerParams;
  runnerParams.appWindowParams.windowTitle = "Hello ImGUI: Advanced docking demo";

  // Provide a full screen dock space
  runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;

  // Define the docking splits, i.e the way the screen space is split in different
  // target zones for the dockable windows
  runnerParams.dockingParams.dockingSplits = {
      // First, add a space named "BottomSpace" whose height is 25% of the app height
      // This will split the preexisting default dockspace "MainDockSpace"
      // (which is provided by "Hello ImGui") in two parts.
      { "MainDockSpace", "BottomSpace", ImGuiDir_Down, 0.25 },
      // Then, add a space to the left which occupies a column
      // whose width is 25% of the app width
      { "MainDockSpace", "LeftSpace", ImGuiDir_Left, 0.25 }
      // We now have three spaces: "MainDockSpace", "BottomSpace", and "LeftSpace"
  };

  // HelloImGui::Widgets::Logger is a Dockable Window, with the title "Logs"
  // and placed in the dockspace "BottomSpace"
  // (see src/hello_imgui/widgets/logger.h)
  HelloImGui::Widgets::Logger logger("Logs", "BottomSpace");
  appState.logger = &logger;

  // Define our dockable windows :
  //  - Each window provide a Gui callback
  runnerParams.dockingParams.dockableWindows = {
      // A Command panel named "Commands" will be placed in "LeftSpace".
      // Its Gui is provided by a lambda that calls "CommandGui"
      {"Commands", "LeftSpace", [&]() { sidebar.render(&appState, nullptr); }},

      // A Log  window named "Logs" will be placed in "BottomSpace"
      // It uses HelloImGui::Widgets::Logger
      logger,

      // A Window named "Dear ImGui Demo" will be placed in "MainDockSpace".
      // Its Gui function is *not* provided here.
      // This way, we can define the Gui of this window elsewhere: as long
      // as we create a window named "Dear ImGui Demo", it will be placed
      // in "MainDockSpace".
      {"Dear ImGui Demo", "MainDockSpace", [&]() { main_window.render(&appState, nullptr); }},
  };

  // We use the default Menu and status bar of Hello ImGui
  runnerParams.imGuiWindowParams.showStatusBar = true;

  // Custom load fonts
  runnerParams.callbacks.LoadAdditionalFonts = MyLoadFonts;

  // Menu bar: we use the default menu of Hello ImGui,
  // to which we add some more items
  Menu menu = Menu();
  runnerParams.imGuiWindowParams.showMenuBar = true;
  runnerParams.callbacks.ShowMenus = [&]() { menu.render(&appState, nullptr); };

  // Example of native SDL events handling
  runnerParams.callbacks.AnyBackendEventCallback = [&logger](void * event) {
#ifdef HELLOIMGUI_USE_SDL_OPENGL3
    SDL_Event*  sdlEvent = (SDL_Event *)event;
        switch( sdlEvent->type)
        {
            case SDL_KEYDOWN:
                logger.warning( "SDL_KEYDOWN detected\n" );
                return true; // if you return true, the event is not processd further
        }
        return false;
#else
    return false;
#endif
  };

  // Status bar:
  runnerParams.imGuiWindowParams.showStatusBar = true;
  // uncomment next line in order to hide the FPS in the status bar
  // runnerParams.imGuiWindowParams.showStatus_Fps = false;
  StatusBar status_bar = StatusBar();
  runnerParams.callbacks.ShowStatus = [&] { status_bar.render(&appState, nullptr); };

  // Then, we run the app
  HelloImGui::Run(runnerParams);
  return 0;
}
