#pragma once

#include <vector>
#include <functional>
#include <mutex>

using dr_render_fn = std::function<void()>;

namespace common {

    class deferred_render final {
    public:
        void render() {
            std::vector<dr_render_fn> current_queue;
            {
                std::lock_guard lock(queue_mutex);
                current_queue = queue;
            }

            for (const dr_render_fn& renderFunction : current_queue) {
                if (renderFunction) {
                    renderFunction();
                }
            }
        }

        void add(dr_render_fn function) {
            if (function) {
                std::lock_guard lock(queue_mutex);
                temp_queue.push_back(std::move(function));
            }
        }

        void clear() {
            std::lock_guard lock(queue_mutex);
            temp_queue.clear();
        }

        void commit_frame() {
            std::lock_guard lock(queue_mutex);
            queue = std::move(temp_queue);
            temp_queue.clear();
        }

    private:
        std::vector<dr_render_fn> queue{};
        std::vector<dr_render_fn> temp_queue{};
        mutable std::mutex queue_mutex;
    };
}

namespace shared {
    inline common::deferred_render lazy_renderer{};
}
