#pragma once

#include <common/cheat/feature/setting/frame.h>
#include <common/overlay/renderer.h>
#include "element_renderer.h"

class frame_renderer {
public:
    explicit frame_renderer(const frame& feature_frame);
public:
    void render(const renderer& renderer) const;

    void render_overlays(const renderer& renderer) const;

    bool has_overlay() const;

    static float width() {
        return 320;
    }

    float height() const;

    frame_position position() const;
private:
    frame feature_frame;
    std::vector<element_renderer*> element_renderers;
};
