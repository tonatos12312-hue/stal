#include "c_type_scope.h"

#include <common/memory/memory.h>

namespace source {

    std::string c_type_scope::name() const {
        char string[256]{};
        shared::memory->read_raw(reinterpret_cast<ptr>(reinterpret_cast<qword>(this) + sizeof(ptr)), string, 256);

        return string;
    }

    std::optional<common::remote_ptr<c_schema_class>> c_type_scope::get(const std::string_view& string) const {
        for (const common::remote_ptr<c_schema_class> schema_class : classes())
            if (schema_class->name() == string)
                return schema_class;

        return std::nullopt;
    }

    std::vector<common::remote_ptr<c_schema_class>> c_type_scope::classes() const {
        std::vector<common::remote_ptr<c_schema_class>> vector{};
        const qword declared_classes_array = shared::memory->read<qword>(reinterpret_cast<qword>(this) + 0x440);
        for (word i = 0; i < shared::memory->read<word>(reinterpret_cast<qword>(this) + 0x510); i++) {
            const auto declared_entry = common::remote_ptr<c_declared_entry>(declared_classes_array + i * sizeof(c_declared_entry));
            vector.push_back(declared_entry->declared_class->class_ptr);
        }

        return vector;
    }
}
