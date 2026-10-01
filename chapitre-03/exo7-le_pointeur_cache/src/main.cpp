#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 7 - Le pointeur cache";
    config.width = 900;
    config.height = 560;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    window.ShowMouse(false);
    window.ClipMouseToClient(true);

    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent* event) {
        if (event->GetKey() == NkKey::NK_ESCAPE) running = false;
    });

    while (running) {
        NkInput.NewFrame();
        NkEvents().PollEvents();
        if (!running) break;

        logger.Info("[Exo7] x={0}, y={1}, rawDelta=({2}, {3})",
                    NkInput.MouseX(), NkInput.MouseY(),
                    NkInput.MouseRawDeltaX(), NkInput.MouseRawDeltaY());
        NkClock::Sleep((int64)16);
    }

    window.ClipMouseToClient(false);
    window.ShowMouse(true);
    window.Close();
    return 0;
}