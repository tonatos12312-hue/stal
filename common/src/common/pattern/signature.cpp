#include "signature.h"

#include <common/memory/memory.h>

namespace common {

    signature::signature() = default;

    signature::signature(const std::string_view& string) : data(hex_to_bytes(string)), found_address(0) {}

    signature& signature::find(ptr base, size_t size) {
        if (data.size > size)
            return *this;

        byte* buffer = new byte[size];
        if (!shared::memory->read_raw(base, buffer, size))
            goto exit;

        for (size_t i = 0; i <= size - data.size; i++) {
            bool matched = true;
            for (size_t j = 0; j < data.size; j++) {
                const byte patternByte = data.buffer[j];
                if (patternByte == 0xFF) // wildcard
                    continue;

                if (patternByte != buffer[i + j]) {
                    matched = false;
                    break;
                }
            }

            if (matched)
                found_address = reinterpret_cast<qword>(base) + i;
        }

exit:
        delete[] buffer;
        return *this;
    }

    signature& signature::find(module_t module) {
        return find(module.base, module.size);
    }

    qword signature::address() const {
        return found_address;
    }

    remote_ptr<ptr> signature::remote() const {
        return remote_ptr<ptr>(reinterpret_cast<ptr>(found_address));
    }

    bool signature::is_found() const {
        return found_address > 0;
    }

    qword signature::resolve_disp32(int opcode_length) const {
        return resolve_displacement32(found_address, opcode_length);
    }
}
