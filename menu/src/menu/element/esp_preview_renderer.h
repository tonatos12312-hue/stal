#pragma once

#include <common/overlay/renderer.h>
#include <esp/esp_preview.h>
#include "element_renderer.h"

class esp_preview_renderer final : public element_renderer {
public:
    explicit esp_preview_renderer(esp_preview* preview);
public:
    void render(const renderer& renderer, bool interactions_blocked) override;

    float height() const override;
private:
    esp_preview* preview;
    esp_element* drag;
    vector2f previous;
    vector2f drag_position;
};
