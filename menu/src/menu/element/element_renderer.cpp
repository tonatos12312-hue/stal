#include "element_renderer.h"

#include <resources.h>

element_renderer::element_renderer(element* owner) : owner(owner) {}

element_renderer::~element_renderer() = default;

void element_renderer::render(const renderer& renderer, bool interactions_blocked) {
    renderer.text(static_cast<ImFont*>(generated::font_inter_medium_16->get_font()), owner->display_name().data(), vector2f(0, 0));
}
