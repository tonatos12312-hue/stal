#pragma once

#include <common/cheat/feature/feature.h>
#include <common/overlay/renderer.h>

class feature_renderer {
public:
    explicit feature_renderer(common::feature* feature);
public:
    void render(const renderer& renderer);

    common::feature* owner() const;

    void set_selected(bool selected);
private:
    common::feature* feature;
    bool selected;
    float animation;
};
