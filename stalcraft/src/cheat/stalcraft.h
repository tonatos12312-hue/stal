#pragma once

#include <common/cheat/cheat.h>

class stalcraft final : public common::cheat {
public:
    stalcraft();
public:
    void unload() override {}

    int start() override;
};
