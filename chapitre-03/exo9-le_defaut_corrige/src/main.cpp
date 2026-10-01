#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 9 - Le defaut corrige";
    config.width = 900;
    config.height = 560;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    int32 accumulatedRawDeltaX = 0;

    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent* event) {
        if (event->GetKey() == NkKey::NK_ESCAPE) running = false;
    });
    NkEvents().AddEventCallback<NkMouseRawEvent>([&](NkMouseRawEvent* event) {
        accumulatedRawDeltaX += event->GetDeltaX();
    });

    while (running) {
        NkInput.NewFrame();
        NkEvents().PollEvents();
        if (!running) break;

        const int32 frameRawDeltaX = NkInput.MouseRawDeltaX();
        const int32 accumulatedThisFrame = accumulatedRawDeltaX;
        accumulatedRawDeltaX = 0;
        logger.Info("[Exo9] rawDeltaX={0}, accumulatedX={1}",
                    frameRawDeltaX, accumulatedThisFrame);
        NkClock::Sleep((int64)16);
    }

    window.Close();
    return 0;
}