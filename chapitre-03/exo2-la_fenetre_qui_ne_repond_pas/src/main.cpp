#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Fenetre qui ne repond pas";
    config.width = 1280;
    config.height = 720;
    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().PollEvents();
    while (running && window.IsOpen()) {
        // PollEvents() est volontairement absent pour cet exercice.
    }

    window.Close();
    return 0;
}