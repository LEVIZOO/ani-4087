#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState&) {
    NkWindowConfig config;
    config.title = "Exo 10 - Le retour de focus";
    config.width = 900;
    config.height = 560;

    NkWindow window(config);
    if (!window.IsValid()) return 1;

    bool running = true;
    bool hasFocus = true;
    bool resetWhileUnfocused = false;
    int32 accumulatedRawDeltaX = 0;

    logger.Info("[Exo10] Mode initial : conservation de l'accumulateur sans focus.");
    logger.Info("[Exo10] Appuyer sur R bascule la remise a zero sans focus.");

    NkEvents().AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { running = false; });
    NkEvents().AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent* event) {
        if (event->GetKey() == NkKey::NK_ESCAPE) {
            running = false;
        } else if (event->GetKey() == NkKey::NK_R) {
            resetWhileUnfocused = !resetWhileUnfocused;
            logger.Info("[Exo10] Remise a zero sans focus : {0}",
                        resetWhileUnfocused ? "OUI" : "NON");
        }
    });
    NkEvents().AddEventCallback<NkWindowFocusLostEvent>([&](NkWindowFocusLostEvent*) {
        hasFocus = false;
        logger.Info("[Exo10] Focus perdu; mode remise a zero : {0}",
                    resetWhileUnfocused ? "OUI" : "NON");
    });
    NkEvents().AddEventCallback<NkWindowFocusGainedEvent>([&](NkWindowFocusGainedEvent*) {
        hasFocus = true;
        logger.Info("[Exo10] Retour de focus : rawDeltaX={0}, accumulateur={1}",
                    NkInput.MouseRawDeltaX(), accumulatedRawDeltaX);
    });
    NkEvents().AddEventCallback<NkMouseRawEvent>([&](NkMouseRawEvent* event) {
        accumulatedRawDeltaX += event->GetDeltaX();
    });

    while (running) {
        NkInput.NewFrame();
        NkEvents().PollEvents();
        if (!running) break;

        if (hasFocus || resetWhileUnfocused) {
            accumulatedRawDeltaX = 0;
        }
        NkClock::Sleep((int64)16);
    }

    window.Close();
    return 0;
}