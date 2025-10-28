#pragma once

#include <source/entity_system.h>

namespace shared {
    inline extern common::remote_ptr<qword> entity_list{}; ///< Общий указатель на `entity_list` с типом `common::remote_ptr<qword>`
}

namespace source {

    constexpr auto invalid_ehandle_index = 0xFFFFFFFF;
    constexpr auto ent_entry_mask = 0x7FFF;
    constexpr auto num_serial_num_shift_bits = 15;

    class c_baseentity;

    class c_base_handle {
    public:
        c_base_handle() : handle_index(invalid_ehandle_index) {}

        explicit c_base_handle(unsigned int index) : handle_index(index) {}

        c_base_handle(int entry, int serial_number) : handle_index(entry | (serial_number << num_serial_num_shift_bits)) {}
    public:
        common::local_ptr<c_baseentity> get() const {
            if (!valid())
                return {};

            const qword entry = shared::memory->read<qword>(*shared::entity_list + 0x8 * ((handle_index & 0x7FFF) >> 9));
            return common::local_ptr<c_baseentity>(shared::memory->read<qword>(entry + 120 * (handle_index & 0x1FF)));
        }

        int entry_index() const {
            return valid() ? handle_index & ent_entry_mask : ent_entry_mask;
        }

        int serial_number() const {
            return handle_index >> num_serial_num_shift_bits;
        }

        int index() const {
            return handle_index;
        }

        bool valid() const {
            return handle_index != invalid_ehandle_index;
        }
    private:
        unsigned int handle_index;
    };
}
