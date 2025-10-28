#pragma once

#include <vector>
#include <string_view>
#include <unordered_map>
#include <common/memory/local_ptr.h>
#include <common/pattern/signature.h>
#include <common/util/process.h>
#include <source/c_utl_vector.h>
#include <source/schema/c_type_scope.h>

namespace source {

    /**
     * @brief Часто используемые модули
     */
    enum class scopes {
        client,
        server,
        engine2,
        schema_system,
        material_system2,
        tier0,
    #if defined(SCHEMA_CS2)
        matchmaking,
    #endif
    #if defined(SCHEMA_DEADLOCK)
        pulsesystem,
    #endif
    };

    /**
     * @brief Представляет низкоуровневый парсер классов в schemasystem.dll
     *
     * @param scope_vector Кешированный локальный указатель на список загруженных модулей
     */
    class schema_parser {
    public:
        explicit schema_parser(common::local_ptr<c_utl_vector<c_type_scope*>> scope_vector);
    public:
        /**
         * @brief Ищет модуль в уже загруженных из часто используемых
         *
         * @tparam scope Модуль из enum
         * @return c_type_scope* если нашел, иначе nullptr
         */
        template<scopes scope>
        constexpr c_type_scope* get() const {
            if constexpr (scope == scopes::client)
                return get("client.dll");
            if constexpr (scope == scopes::server)
                return get("server.dll");
            else if constexpr (scope == scopes::engine2)
                return get("engine2.dll");
            else if constexpr (scope == scopes::tier0)
                return get("tier0.dll");
            else if constexpr (scope == scopes::schema_system)
                return get("schemasystem.dll");
            else if constexpr (scope == scopes::material_system2)
                return get("materialsystem2.dll");
    #if defined(SCHEMA_CS2)
            else if constexpr (scope == scopes::matchmaking)
                return get("matchmaking.dll");
    #endif
    #if defined(SCHEMA_DEADLOCK)
            else if constexpr (scope == scopes::pulsesystem)
                return get("pulsesystem.dll");
    #endif

            return nullptr;
        }

        /**
         * @brief Ищет модуль из уже загруженных
         *
         * @param string Имя модуля
         * @return c_type_scope* если нашел, иначе nullptr
         */
        c_type_scope* get(const std::string_view& string) const;

        /**
         * @brief Возвращает список из уже загруженных модулей
         *
         * @return Список из `c_type_scope*` в виде `std::vector`
         */
        std::vector<c_type_scope*> scopes() const;
    public:
        /**
         * @brief Создает парсер schemasystem
         *
         * Автоматически получает модуль schemasystem.dll в удаленном процессе
         * Читает оффсеты для работы через универсальные сигнатуры для всех игр
         *
         * @return Экземпляр `schema_parser`
         */
        static schema_parser create() {
            const common::module_t schema_system_module = *common::util::find_module(shared::memory->pid(), "schemasystem.dll");

            const dword offset = shared::memory->read<dword>(common::signature("41 0F B7 ? ? ? 00 00").find(schema_system_module).address() + 4);
            const auto scopes = common::local_ptr<c_utl_vector<c_type_scope*>>(common::signature("4C 8D 35 ? ? ? ? 0F 28 45").find(schema_system_module).resolve_disp32(3) + offset);

            return schema_parser(scopes);
        }

        static void dump();
    private:
        common::local_ptr<c_utl_vector<c_type_scope*>> scope_vector; ///< Список из уже загруженных модулей
    };
}

namespace shared {
    inline extern std::unordered_map<std::string, dword> schema_dumped{}; ///< Общий указатель на `std::unordered_map` со сдампленной schema классами и полями
}
