#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 5 - La taille qui change";
    config.width = 900;
    config.height = 560;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().AddEventCallback<NkWindowResizeEvent>([](NkWindowResizeEvent* event) {
        logger.Info("[Exo5] Nouvelle taille : {0}x{1}", event->GetWidth(), event->GetHeight());
    });

    while (running) {
        NkEvents().PollEvents();
        NkClock::Sleep((int64)10);
    }

    window.Close();
    return 0;
}