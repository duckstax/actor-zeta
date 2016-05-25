#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <cstdint>
#include <cstddef>
#include <string>

namespace actor_zeta {

    constexpr unsigned char encoding_table[] = {
/*     ..0 ..1 ..2 ..3 ..4 ..5 ..6 ..7 ..8 ..9 ..A ..B ..C ..D ..E ..F  */
/* 0.. */  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 1.. */  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2.. */  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3.. */  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0,
/* 4.. */  0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
/* 5.. */ 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 0, 0, 0, 0, 37,
/* 6.. */  0, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
/* 7.. */ 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0, 0, 0, 0, 0};


    constexpr char decoding_table[] = " 0123456789"
                                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
                                      "abcdefghijklmnopqrstuvwxyz";


    constexpr uint64_t next_interim(uint64_t current, size_t char_code) {
        return (current << 6) | encoding_table[(char_code <= 0x7F) ? char_code : 0];
    }

    constexpr uint64_t command_val(const char *cstr, uint64_t interim = 0xF) {
        return (*cstr == '\0') ?
               interim :
               command_val(cstr + 1,
                           next_interim(interim, static_cast<size_t>(*cstr)));
    }


    enum class command_value : uint64_t {
        big_hack = 31337
    };

    inline std::string to_string(const command_value &what) {
        auto x = static_cast<uint64_t>(what);
        std::string result;
        result.reserve(11);
        bool read_chars = ((x & 0xF000000000000000) >> 60) == 0xF;
        uint64_t mask = 0x0FC0000000000000;
        for (int bitshift = 54; bitshift >= 0; bitshift -= 6, mask >>= 6) {
            if (read_chars)
                result += decoding_table[(x & mask) >> bitshift];
            else if (((x & mask) >> bitshift) == 0xF)
                read_chars = true;
        }
        return result;
    }


    template<size_t Size>
    constexpr command_value command(char const (&str)[Size]) {
        // last character is the NULL terminator
        static_assert(Size <= 11, "only 10 characters are allowed");
        return static_cast<command_value>(command_val(str));
    }

    template<command_value V>
    struct command_constant {
        constexpr command_constant() { }

        constexpr operator command_value() const {
            return V;
        }

        static constexpr uint64_t uint_value() {
            return static_cast<uint64_t>(V);
        }

        static const command_constant value;
    };

    template<class T>
    struct is_command_constant {
        static constexpr bool value = false;
    };

    template<command_value X>
    struct is_command_constant<command_constant<X>> {
        static constexpr bool value = true;
    };

    template<command_value V>
    std::string to_string(const command_constant<V> &) {
        return to_string(V);
    }

    template<command_value V>
    const command_constant<V> command_constant<V>::value = command_constant<V>{};

}
#endif //COMMAND_HPP
