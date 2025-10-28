#pragma once

namespace common {

    enum class resource_type {
        image,
        font
    };

    class resource {
    public:
        explicit resource(resource_type type) : type(type) {}

        virtual ~resource() = default;
    public:
        resource_type get_type() const {
            return type;
        }
    private:
        resource_type type;
    };
}
