#pragma once

#include <stdexcept>

namespace common {

    class overlay;

    using render_fn = void(*)(overlay*);

    /**
     * @brief Представляет базовый класс для оверлея
     */
    class overlay {
    public:
        explicit overlay(render_fn render_function) : render_function(render_function) {}

        virtual ~overlay() = default;
    public:
        /**
         * @brief Создает и инициализирует окно
         */
        virtual void create() {
            if (created)
                throw std::exception("Overlay already created");

            created = true;
        }

        /**
         * @brief Запускает цикл рендера
         */
        virtual void loop() {
            if (!created)
                throw std::exception("Overlay not created");
        }
    public:
        /**
         * @brief Указывает, можно ли взаимодействовать с оверлеем
         *
         * @return true, если можно взаимодействовать
         */
        bool is_interactable() const {
            return interactable;
        }

        /**
         * @brief Меняет флаг взаимодействия с оверлеем
         *
         * @param interactable Новое значение флага
         */
        void set_interactable(bool interactable) {
            this->interactable = interactable;
        }
    protected:
        render_fn render_function; ///< Функция рендера контента
    private:
        bool created = false; ///< Флаг, указывающий, создан ли оверлей
        bool interactable = false; ///< Флаг, указывающий, можно ли взаимодействовать с оверлеем
    };
}
