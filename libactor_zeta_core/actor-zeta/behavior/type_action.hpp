#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace actor_zeta {
    namespace behavior {
///
/// @brief Type of commands used for lyfecycle 
///
        class type_action {
        private:
            std::string body_;
            std::size_t hash_;
        public:
            type_action() = delete;

            type_action(const type_action &) = default;

            type_action &operator=(const type_action &t)= default;

            type_action(type_action &&) = default;

            type_action &operator=(type_action &&) = default;

            ~type_action() = default;

            template<std::size_t N>
            type_action(const char(&aStr)[N]): body_(aStr) {
                hash_ = std::hash<std::string>{}(body_);
            }

            type_action(const char *, std::size_t);

            type_action(const std::string&);

            //bool operator<(const type_action &t) const noexcept{ memcmp()}
            bool operator==(const type_action &t) const noexcept;

            auto hash() const noexcept -> std::size_t;

            auto to_string() const -> const std::string&;
        };
    }
}

namespace std {
    template<>
    struct hash<actor_zeta::behavior::type_action> {
        inline size_t operator()(const actor_zeta::behavior::type_action &ref) const {
            return ref.hash();
        }
    };
}

#endif //TOKEN_HPP
