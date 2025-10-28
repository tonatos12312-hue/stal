#include "c_schema_class.h"

#include <common/memory/memory.h>

namespace source {

    c_schema_class::c_schema_class() = default;

    std::string c_schema_class::name() const {
        char string[256]{};
        shared::memory->read_raw(name_ptr, string, 256);

        return string;
    }

    std::string c_schema_class::scope_name() const {
        char string[256]{};
        shared::memory->read_raw(scope_name_ptr, string, 256);

        return string;
    }

    std::optional<c_schema_field> c_schema_class::field(const std::string_view& string) const {
        for (const c_schema_field& field : fields())
            if (field.name() == string)
                return field;

        return std::nullopt;
    }

    std::vector<c_schema_field> c_schema_class::fields() const {
        std::vector<c_schema_field> vector{};
        for (word i = 0; i < field_count; i++)
            vector.push_back(shared::memory->read<c_schema_field>(reinterpret_cast<qword>(declared_fields) + i * sizeof(c_schema_field)));

        return vector;
    }
}
