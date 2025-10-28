#pragma once

#include <common/cheat/cheat.h>
#include <common/math/vector2.h>
#include <common/resource/resource_manager.h>
#include "gui_state.h"
#include "sidebar.h"

class gui {
public:
    explicit gui(common::resource_manager* resource_manager, const vector2f& size, common::cheat* cheat);
public:
    void render();

    void select_feature(common::feature* feature);

    common::feature* selected_feature();

    bool is_opened() const;
private:
    bool opened;
    bool insert_pressed;
    float animation;
    vector2f position;
    vector2f size;
    gui_state state;
    sidebar side;
};

namespace shared {
    inline extern gui* menu = nullptr;
}
