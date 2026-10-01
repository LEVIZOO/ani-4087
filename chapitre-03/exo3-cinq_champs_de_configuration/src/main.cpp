#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 3 - Cinq champs";
    config.width = 900;
    config.height = 560;
    config.hasShadow = false;
    config.transparent = true;
    config.opacity = 0.75f;
    config.alwaysOnTop = true;
    config.minimizable = false;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    while (running && window.IsOpen()) {
        NkEvents().PollEvents();
        NkClock::Sleep((int64)10);
    }

    window.Close();
    return 0;
}