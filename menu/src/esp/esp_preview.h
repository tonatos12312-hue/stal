#pragma once

#include <vector>
#include <common/cheat/feature/setting/element.h>
#include "esp_element.h"
#include "name_esp_element.h"
#include "corner_box_esp_element.h"
#include "box_esp_element.h"
#include "fade_esp_element.h"
#include "healthbar_esp_element.h"

class esp_preview final : public element {
public:
    explicit esp_preview(const std::vector<esp_element*>& element_vector) : element("ESP Preview"), element_vector(element_vector) {}
public:
    void render(const renderer& renderer, const vector2f& position, const vector2f& size, float health, const std::string_view& name) {
        esp_info info;
        info.position = position;
        info.size = size;
        info.health = health;
        info.name = name;

        for (esp_element* element : element_vector)
            if (element->is_enabled())
                element->render(info, renderer);
    }

    void render_preview(const renderer& renderer, const vector2f& position, const vector2f& size) {
        render(renderer, position, size, 0.52f, "anfisov");
    }

    std::vector<esp_element*> elements() const {
        return element_vector;
    }
private:
    std::vector<esp_element*> element_vector;
};
