#include "gui.h"

#include <imgui.h>
#include <Windows.h>
#include <common/overlay/renderer.h>
#include <common/util/easings.h>
#include <resources.h>

gui::gui(common::resource_manager* resource_manager, const vector2f& size, common::cheat* cheat)
    : opened(false),
    animation(0.0f),
    size(size),
    state(cheat->all_features()[0]),
    side(vector2f(85, size.y), cheat, &state),
    insert_pressed(false) {

    generated::setup_resources(resource_manager);
}

void gui::render() {
    animation = ease_out_quart(animation, opened ? 1 : 0, ImGui::GetIO().DeltaTime * 5);

    const bool insert_current = (GetAsyncKeyState(VK_HOME) & 0x8000) != 0;
    if (insert_current && !insert_pressed)
        opened = !opened;
    insert_pressed = insert_current;

    if (animation <= 0.01f)
        return;

    //position = vector2f(1920 / 2 - size.x / 2, 1080 / 2 - size.y / 2);

    //ImGui::SetNextWindowPos(ImVec2(position.x, position.y));
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
    position = vector2f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
    const renderer renderer(ImGui::GetWindowDrawList(), position, animation);
    state.tick();

    renderer.rect(vector2f(0, 0), size, IM_COL32_BLACK, 18);
    side.render(renderer);

    float left_offset = -10 + state.animation * 32;
    float right_offset = -10 + state.animation * 32;
    auto& frames = state.frame_renderers();

    for (size_t i = 0; i < frames.size(); i++) {
        if (frames[i].position() == frame_position::left) {
            frames[i].render(renderer.translated(vector2f(101, left_offset), state.animation));
            left_offset += frames[i].height() + 18;
        } else {
            frames[i].render(renderer.translated(vector2f(101 + frames[0].width() + 13, right_offset), state.animation));
            right_offset += frames[i].height() + 18;
        }
    }

    left_offset = -10 + state.animation * 32;
    right_offset = -10 + state.animation * 32;

    for (size_t i = 0; i < frames.size(); i++) {
        if (frames[i].position() == frame_position::left) {
            frames[i].render_overlays(renderer.translated(vector2f(101, left_offset), state.animation));
            left_offset += frames[i].height() + 18;
        } else {
            frames[i].render_overlays(renderer.translated(vector2f(101 + frames[0].width() + 13, right_offset), state.animation));
            right_offset += frames[i].height() + 18;
        }
    }

    ImGui::End();
}

bool gui::is_opened() const {
    return opened;
}
