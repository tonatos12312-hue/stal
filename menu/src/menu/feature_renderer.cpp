#include "feature_renderer.h"

#include <common/math/vector2.h>
#include <common/util/easings.h>

feature_renderer::feature_renderer(common::feature* feature) : feature(feature), selected(false), animation(0.0f) {}

void feature_renderer::render(const renderer& renderer) {
    animation = ease_out_quart(animation, selected ? 1 : 0, ImGui::GetIO().DeltaTime * 3);

    //if (selected)
      //  renderer.rect(vector2f(0, 0), vector2f(50, 50), ImColor(10 + static_cast<int>(animation * 131), 10 + static_cast<int>(animation * 65), 15 + static_cast<int>(animation * 240)), 12);

    common::image* image = feature->menu_icon();
    //const vector2f size = vector2f(image->get_size().x, image->get_size().y);
    //renderer.image(image->get_texture(), vector2f(50, 50) / 2 - size / 2, size, HEX_TO_IMCOL32(selected ? "#000000" : "#4D4E65"));
}

common::feature* feature_renderer::owner() const {
    return feature;
}

void feature_renderer::set_selected(bool selected) {
    this->selected = selected;
}
