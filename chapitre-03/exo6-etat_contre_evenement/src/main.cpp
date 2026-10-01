#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 6 - Etat contre evenement";
    config.width = 900;
    config.height = 560;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    uint32 heldFrames = 0;
    uint32 spacePressEvents = 0;

    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent* event) {
        if (event->GetKey() == NkKey::NK_SPACE) ++spacePressEvents;
    });
    NkEvents().AddEventCallback<NkKeyReleaseEvent>([&](NkKeyReleaseEvent* event) {
        if (event->GetKey() == NkKey::NK_SPACE) {
            logger.Info("[Exo6] NkInput.IsKeyDown : {0} frames", heldFrames);
            logger.Info("[Exo6] NkKeyPressEvent : {0} evenement(s)", spacePressEvents);
            heldFrames = 0;
            spacePressEvents = 0;
        }
    });

    while (running) {
        NkInput.NewFrame();
        NkEvents().PollEvents();
        if (NkInput.IsKeyDown(NkKey::NK_SPACE)) ++heldFrames;
        NkClock::Sleep((int64)16);
    }

    window.Close();
    return 0;
}