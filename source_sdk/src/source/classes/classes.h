#pragma once

#include <string>
#include <common/memory/memory.h>
#include <common/math/math.h>
#include <source/schema/schema_parser.h>
#include <source/handle/c_handle.h>
#include <source/handle/c_strong_handle.h>

#define schema(type, name, cached_name) public: \
    type name() { \
        return shared::memory->read<type>(reinterpret_cast<qword>(this) + shared::schema_dumped[cached_name]); \
    }

#define schema_string(name, cached_name) public: \
    std::string name() { \
        char buffer[256]{}; \
        shared::memory->read_raw(reinterpret_cast<ptr>(reinterpret_cast<qword>(this) + shared::schema_dumped[cached_name]), buffer, sizeof(buffer)); \
        return buffer; \
    }

namespace source {

    class c_entity_identity {
    public:
        schema(unsigned int, identity_flags, "CEntityIdentity->m_flags")
    private:
        schema(ptr, designer_name_ptr, "CEntityIdentity->m_designerName")
    public:
        std::string DesignerName() {
            char owner_name[256]{};
            shared::memory->read_raw(designer_name_ptr(), owner_name, sizeof(owner_name));

            return std::string(owner_name);
        }
    };

    class c_collision_property {
        schema(vector3f, minimum, "CCollisionProperty->m_vecMins")
        schema(vector3f, maximum, "CCollisionProperty->m_vecMaxs")
        schema(vector3f, surrounding_minimum, "CCollisionProperty->m_vecSurroundingMins")
        schema(vector3f, surrounding_maximum, "CCollisionProperty->m_vecSurroundingMaxs")
        schema(byte, collision_group, "CCollisionProperty->m_CollisionGroup")
    };

    class c_entity_instance {
    public:
        schema(c_entity_identity*, identity, "CEntityInstance->m_pEntity")
    };

    class alignas(16) c_transform {
    public:
        alignas(16) vector3f position;
        alignas(16) quaternionf rotation;
    };

    class c_game_scene_node {
        schema(c_transform, node_to_world, "CGameSceneNode->m_nodeToWorld")
    };

    class info_for_resource_type_cmodel {

    };

    class c_model_state {
        schema(c_strong_handle<info_for_resource_type_cmodel>, model, "CModelState->m_hModel");
    };

    class c_skeleton_instance : public c_game_scene_node {
        schema(c_model_state, model_state, "CSkeletonInstance->m_modelState");
    };

    class c_baseentity : public c_entity_instance {
        schema(int, health, "C_BaseEntity->m_iHealth")
        schema(int, max_health, "C_BaseEntity->m_iMaxHealth")
        schema(common::local_ptr<c_skeleton_instance>, scene_node, "C_BaseEntity->m_pGameSceneNode")
        schema(common::local_ptr<c_collision_property>, collision, "C_BaseEntity->m_pCollision")
        schema(byte, team, "C_BaseEntity->m_iTeamNum")
    };

    class c_base_player_pawn;

    class c_base_player_controller : public c_baseentity {
        schema_string(player_name, "CBasePlayerController->m_iszPlayerName");
        schema(c_handle<c_base_player_pawn>, pawn, "CBasePlayerController->m_hPawn")
        schema(qword, steam_id, "CBasePlayerController->m_steamID")
    };

    class c_citadel_player_controller : public c_base_player_controller {
        schema(int, current_rank, "CCitadelPlayerController->m_nCurrentRank")
    };

    class c_base_model_entity : public c_baseentity {
        schema(c_collision_property, model_collision, "C_BaseModelEntity->m_Collision")
    };

    class c_base_animgraph : public c_base_model_entity {
        schema(vector3f, force, "CBaseAnimGraph->m_vecForce")
        schema(int, force_bone, "CBaseAnimGraph->m_nForceBone")
    };

    class c_baseflex : public c_base_animgraph {

    };

    class c_base_combat_character : public c_baseflex {

    };

    class c_base_player_pawn : public c_base_combat_character {
        schema(vector3f, position, "C_BasePlayerPawn->m_vOldOrigin")
        schema(c_handle<c_base_player_controller>, controller, "C_BasePlayerPawn->m_hController")
    };

    class c_citadel_player_pawn_base : public c_base_player_pawn {

    };

    class c_citadel_player_pawn : public c_citadel_player_pawn_base {
        // qangle m_angEyeAngles

    };
}

namespace shared {
    inline extern common::local_ptr<source::c_citadel_player_controller> local_controller{}; ///< Общий указатель на `common::local_ptr` с типом `source::c_citadel_player_controller`
}
