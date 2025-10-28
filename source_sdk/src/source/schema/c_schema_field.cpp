#include "c_schema_field.h"

#include <common/memory/memory.h>

namespace source {

    c_schema_field::c_schema_field() = default;

    std::string c_schema_field::name() const {
        char string[256]{};
        shared::memory->read_raw(name_ptr, string, 256);

        return string;
    }

    std::string c_schema_field::owner() const {
        char string[256]{};
        shared::memory->read_raw(owner_name_ptr, string, 256);

        return string;
    }

    dword c_schema_field::offset() const {
        return memory_offset;
    }
}
