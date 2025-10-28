#pragma once

#include <common/cheat/feature/setting/element.h>
#include <common/overlay/renderer.h>

class element_renderer {
public:
    explicit element_renderer(element* owner);

    virtual ~element_renderer();
public:
    virtual void render(const renderer& renderer, bool interactions_blocked = false);

    virtual void render_overlay(const renderer& renderer) {}

    virtual bool has_overlay() const { return false; }

    virtual bool is_blocking_interactions() const { return false; }

    virtual float height() const = 0;
public:
    static float width() {
        return 320 - 16*2;
    }
private:
    element* owner;
};
