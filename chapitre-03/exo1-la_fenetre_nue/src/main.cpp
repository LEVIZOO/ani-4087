#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Fenetre nue";
    config.width = 1280;
    config.height = 720;
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