#ifndef _COMPONENTS_CPP
#define _COMPONENTS_CPP

class Component {
    public:
    virtual void render(AppState* appState, void* componentState) = 0;
};

#include "sidebar.cpp"
#include "main_window.cpp"
#include "menu.cpp"
#include "status_bar.cpp"

#endif