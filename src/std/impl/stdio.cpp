#include "drivers/uart.hpp"
#include "std/cstdint"
#include "std/cstdio"
#include "std/cstring"
#include "std/impl/formatters.hpp"

namespace std {
    namespace detail {
        drivers::uart_ns16550a stdout_serial;

        static uint32_t parse_size_param(const char* fmt_it) {
            if (std::memcmp("8", fmt_it + 1, 1) == 0)
                return 8;
            else if (std::memcmp("16", fmt_it + 1, 2) == 0)
                return 16;
            else if (std::memcmp("32", fmt_it + 1, 2) == 0)
                return 32;
            else if (std::memcmp("64", fmt_it + 1, 2) == 0)
                return 64;
            return 0;
        }

        static void put_int(const char** fmt_it, bool sign, __builtin_va_list args, char* out_buf, uint64_t out_buf_size,
                            const auto&... rest) {
            if (!sign) {
                if (*(*fmt_it + 1) && *(*fmt_it + 2)) {
                    switch (parse_size_param(*fmt_it)) {
                    case 8: {
                        std::puts_n(out_buf,
                                    std::format_to<uint8_t>(out_buf, out_buf_size, __builtin_va_arg(args, uint32_t), rest...));
                        (*fmt_it)++;
                    } break;

                    case 16: {
                        std::puts_n(out_buf,
                                    std::format_to<uint16_t>(out_buf, out_buf_size, __builtin_va_arg(args, uint32_t), rest...));
                        *fmt_it += 2;
                    } break;

                    default:
                    case 32: {
                        std::puts_n(out_buf,
                                    std::format_to<uint32_t>(out_buf, out_buf_size, __builtin_va_arg(args, uint32_t), rest...));
                        *fmt_it += 2;
                    } break;

                    case 64: {
                        std::puts_n(out_buf,
                                    std::format_to<uint64_t>(out_buf, out_buf_size, __builtin_va_arg(args, uint64_t), rest...));
                        *fmt_it += 2;
                    } break;
                    }
                } else
                    std::puts_n(out_buf,
                                std::format_to<uint32_t>(out_buf, out_buf_size, __builtin_va_arg(args, uint32_t), rest...));
            } else {
                if (*(*fmt_it + 1) && *(*fmt_it + 2)) {
                    switch (parse_size_param(*fmt_it)) {
                    case 8: {
                        std::puts_n(out_buf,
                                    std::format_to<int8_t>(out_buf, out_buf_size, __builtin_va_arg(args, int32_t), rest...));
                        (*fmt_it)++;
                    } break;

                    case 16: {
                        std::puts_n(out_buf,
                                    std::format_to<int16_t>(out_buf, out_buf_size, __builtin_va_arg(args, int32_t), rest...));
                        *fmt_it += 2;
                    } break;

                    default:
                    case 32: {
                        std::puts_n(out_buf,
                                    std::format_to<int32_t>(out_buf, out_buf_size, __builtin_va_arg(args, int32_t), rest...));
                        *fmt_it += 2;
                    } break;

                    case 64: {
                        std::puts_n(out_buf,
                                    std::format_to<int64_t>(out_buf, out_buf_size, __builtin_va_arg(args, int64_t), rest...));
                        *fmt_it += 2;
                    } break;
                    }
                } else
                    std::puts_n(out_buf,
                                std::format_to<int32_t>(out_buf, out_buf_size, __builtin_va_arg(args, int32_t), rest...));
            }
        }

        static void put_float(const char** fmt_it, __builtin_va_list args, char* out_buf, uint64_t out_buf_size) {
            if (*(*fmt_it + 1) && *(*fmt_it + 2)) {
                if (std::memcmp("32", *fmt_it + 1, 2) == 0) {
                    std::puts("<float32>");
                    *fmt_it += 2;
                } else if (std::memcmp("64", *fmt_it + 1, 2) == 0) {
                    std::puts("<float64>");
                    *fmt_it += 2;
                } else {
                    std::puts("<float32>");
                }
            } else
                std::puts("<float32>");
        }
    } // namespace detail

    void putc(char c) {
        detail::stdout_serial.write(c);
    }

    void puts(const char* str) {
        while (*str)
            detail::stdout_serial.write(*str++);
    }

    void puts_n(const char* str, uint64_t n) {
        for (auto it = str; it <= (str + n); it++)
            detail::stdout_serial.write(*it);
    }

    void printf(const char* fmt, ...) {
        __builtin_va_list args;
        __builtin_va_start(args, fmt);
        vprintf(fmt, args);
        __builtin_va_end(args);
    }

    void vprintf(const char* fmt, __builtin_va_list args) {
        constexpr auto int_strbuf_size = 64;
        constexpr auto float_strbuf_size = 128;

        while (*fmt) {
            if (*fmt == '%') {
                ++fmt;

                if (!*fmt)
                    return;

                switch (*fmt) {
                case 'i': {
                    char buf[int_strbuf_size] = {0};
                    detail::put_int(&fmt, true, args, buf, sizeof(buf));
                } break;

                case 'u': {
                    char buf[int_strbuf_size] = {0};
                    detail::put_int(&fmt, false, args, buf, sizeof(buf));
                } break;

                case 'x': {
                    char buf[int_strbuf_size] = {0};
                    detail::put_int(&fmt, false, args, buf, sizeof(buf), 16);
                } break;

                case 'X': {
                    char buf[int_strbuf_size] = {0};
                    detail::put_int(&fmt, false, args, buf, sizeof(buf), 16, true);
                } break;

                case 'p': {
                    char buf[int_strbuf_size] = {0};
                    std::puts("0x");
                    std::puts_n(buf, std::format_to<uint64_t>(buf, sizeof(buf), __builtin_va_arg(args, uint64_t), 16));
                } break;

                case 'P': {
                    char buf[int_strbuf_size] = {0};
                    std::puts("0x");
                    std::puts_n(buf, std::format_to<uint64_t>(buf, sizeof(buf), __builtin_va_arg(args, uint64_t), 16, true));
                } break;

                case 'f': {
                    char buf[float_strbuf_size] = {0};
                    detail::put_float(&fmt, args, buf, sizeof(buf));
                } break;

                case '%':
                    putc('%');
                    break;

                default:
                    putc('%');
                    putc(*fmt);
                    break;
                }

                fmt++;
            } else {
                putc(*fmt++);
            }
        }
    }
} // namespace std