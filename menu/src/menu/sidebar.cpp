#include "sidebar.h"

#include <resources.h>

sidebar::sidebar(const vector2f& size, common::cheat* cheat, gui_state* state) : size(size), cheat(cheat), state(state) {
    for (common::feature* feature : cheat->all_features())
        feature_renderers.push_back(feature_renderer(feature));

    for (feature_renderer& feature : feature_renderers)
        feature.set_selected(state->selected_feature()->display_name() == feature.owner()->display_name());
}

void sidebar::render(const renderer& renderer) {
    renderer.rect(vector2f(size.x, 0), vector2f(1, size.y), HEX_TO_IMCOL32("#212121"), 8);
    renderer.image(generated::image_logo->get_texture(), vector2f(size.x / 2 - 40 / 2, 32), vector2f(40, 40));

    float offset = 108;
    for (feature_renderer& feature : feature_renderers) {
        const vector2f feature_pos = vector2f(size.x / 2 - 50 / 2, offset);
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && renderer.hovering(feature_pos, vector2f(50, 50)))
            select_feature(feature);

        feature.render(renderer.translated(feature_pos));

        offset += 50 + 8;
    }
}

void sidebar::select_feature(feature_renderer& feature) {
    state->select_feature(feature.owner());

    for (feature_renderer& renderer : feature_renderers)
        renderer.set_selected(false);
    feature.set_selected(true);
}
