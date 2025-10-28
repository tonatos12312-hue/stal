#include "entity_system.h"

#include <common/memory/memory.h>

namespace source {

    c_game_entity_system::c_game_entity_system() = default;

    common::remote_ptr<c_baseentity> c_game_entity_system::base_from_index(unsigned int index) const {
        return identity_from_index(index).base_entity;
    }

    c_entity_list_identity c_game_entity_system::identity_from_index(unsigned int index) const {
        if (index >= MAX_TOTAL_ENTITIES)
            return {};

        constexpr qword chunk_array_offset = sizeof(ptr) + sizeof(qword);
        const qword chunk_ptr_address = reinterpret_cast<qword>(this) + chunk_array_offset + (index / MAX_ENTITIES_IN_LIST) * sizeof(ptr);
        if (!chunk_ptr_address)
            return {};

        const ptr chunk_ptr = shared::memory->read<ptr>(chunk_ptr_address);
        if (!chunk_ptr)
            return {};

        const qword identity_offset = (index % MAX_ENTITIES_IN_LIST) * sizeof(c_entity_list_identity);
        const ptr identity_ptr = reinterpret_cast<ptr>(reinterpret_cast<qword>(chunk_ptr) + identity_offset);

        return shared::memory->read<c_entity_list_identity>(identity_ptr);
    }
}
