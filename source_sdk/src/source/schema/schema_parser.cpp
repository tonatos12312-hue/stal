#include "schema_parser.h"

namespace source {

    schema_parser::schema_parser(common::local_ptr<c_utl_vector<c_type_scope*>> scope_vector) : scope_vector(scope_vector) {}

    c_type_scope* schema_parser::get(const std::string_view& string) const {
        for (c_type_scope* scope : scopes())
            if (scope->name() == string)
                return scope;

        return nullptr;
    }

    std::vector<c_type_scope*> schema_parser::scopes() const {
        std::vector<c_type_scope*> vector{};
        for (size_t i = 0; i < scope_vector->size(); i++)
            if (c_type_scope* scope = scope_vector[i])
                vector.push_back(scope);

        return vector;
    }

    void schema_parser::dump() {
        const schema_parser parser = create();
        const c_type_scope* scope = parser.get<scopes::client>();
        for (const common::remote_ptr<c_schema_class> schema_class : scope->classes()) {
            for (const c_schema_field& field : schema_class->fields()) {
                shared::schema_dumped[schema_class->name() + "->" + field.name()] = field.offset();
            }
        }
    }
}
