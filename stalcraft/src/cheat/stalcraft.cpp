#include "stalcraft.h"

#include <Windows.h>
#include <thread>
#include <utility>
#include "feature/chams.h"
#include "hook/swapbuffers.h"
#include "hook/gl_draw_elements.h"
#include "material/material_set.h"

stalcraft::stalcraft() {}

int stalcraft::start() {
    Beep(550, 500);

    register_feature(gl_draw_elements_hook::chams_feature = new chams_feature);
    printf("[cheat] registered chams feature\n");

    material_set::init();
    printf("[material_set] materials initialized\n");

    swapbuffers_hook::sc_cheat = this;
    swapbuffers_hook::setup();
    printf("[hook] swapbuffers hooked\n");

    gl_draw_elements_hook::setup();
    printf("[hook] draw_elements hooked\n");

    return TRUE;
}
