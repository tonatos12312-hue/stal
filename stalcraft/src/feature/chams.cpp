#include "chams.h"

#include <resources.h>

chams_feature::chams_feature() : feature("Chams", generated_sc::image_ic) {
    frame general("General", frame_position::left);
    general.add(material_setting = new combobox("Material", { "Metallic" }, { "Vazelin", "Metallic", "Glass", "Wireframe" }));
    general.add(color_setting = new color("Color", { 139.0f / 255.0f, 0.0f, 1.0f, 1.0f }));
    general.add(bind = new keybind);
    general.add(state_type_setting = new combobox("State type", { "Hold" }, { "Hold", "Toggle", "Always on (BAN RISK)" }));

    add_frame(general);
}
