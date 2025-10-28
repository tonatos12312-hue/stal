#pragma once

#include <common/memory/remote_ptr.h>
#include <common/memory/local_ptr.h>

namespace source {

    class c_baseentity;
    class c_entity_identity;

    constexpr auto MAX_ENTITIES_IN_LIST = 512;
    constexpr auto MAX_ENTITY_LISTS = 64;
    constexpr auto MAX_TOTAL_ENTITIES = MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS;

    struct c_entity_list_identity {
        common::remote_ptr<c_baseentity> base_entity;
        ptr unknown;
        unsigned int handle_index;
        int unknown2;
        ptr internal_name;
        ptr entity_name;
        ptr unknown3[5];
        c_entity_identity* previous;
        c_entity_identity* next;
        ptr unknown4;
        ptr unknown5;
        ptr unknown6;
    };

    class c_entity_identities {
    public:
        c_entity_list_identity identities[MAX_ENTITIES_IN_LIST];
    };

    class c_game_entity_system {
    public:
        c_game_entity_system();
    public:
        common::remote_ptr<c_baseentity> base_from_index(unsigned int index) const;

        c_entity_list_identity identity_from_index(unsigned int index) const;
    };
}

namespace shared {
    inline extern common::local_ptr<source::c_game_entity_system> entity_system{}; ///< Общий указатель на `source::entity_system*`
}
