#include "drivers/uart.hpp"
#include "std/cstdint"
#include "std/cstdio"
#include "std/cstring"
#include "std/impl/formatters.hpp"

namespace std {
    namespace detail {
        drivers::uart_ns16550a stdout_serial;
    }

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

        while (*fmt) {
            if (*fmt == '%') {
                ++fmt;

                if (!*fmt)
                    return;

                switch (*fmt) {
                case 'i': {
                    char buf[int_strbuf_size] = {0};
                    if (*(fmt + 1) && *(fmt + 2)) {
                        if (std::memcmp("8", fmt + 1, 1) == 0) {
                            std::puts_n(buf, std::format_to<int8_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                            fmt++;
                        } else if (std::memcmp("16", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<int16_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                            fmt += 2;
                        } else if (std::memcmp("32", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                            fmt += 2;
                        } else if (std::memcmp("64", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<int64_t>(buf, sizeof(buf), __builtin_va_arg(args, int64_t)));
                            fmt += 2;
                        } else {
                            std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                        }
                    } else
                        std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                } break;

                case 'u': {
                    char buf[int_strbuf_size] = {0};
                    if (*(fmt + 1) && *(fmt + 2)) {
                        if (std::memcmp("8", fmt + 1, 1) == 0) {
                            std::puts_n(buf, std::format_to<uint8_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t)));
                            fmt++;
                        } else if (std::memcmp("16", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint16_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t)));
                            fmt += 2;
                        } else if (std::memcmp("32", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t)));
                            fmt += 2;
                        } else if (std::memcmp("64", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint64_t>(buf, sizeof(buf), __builtin_va_arg(args, uint64_t)));
                            fmt += 2;
                        } else {
                            std::puts_n(buf, std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t)));
                        }
                    } else
                        std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t)));
                } break;

                case 'x': {
                    char buf[int_strbuf_size] = {0};
                    if (*(fmt + 1) && *(fmt + 2)) {
                        if (std::memcmp("8", fmt + 1, 1) == 0) {
                            std::puts_n(buf, std::format_to<uint8_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16));
                            fmt++;
                        } else if (std::memcmp("16", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint16_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16));
                            fmt += 2;
                        } else if (std::memcmp("32", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16));
                            fmt += 2;
                        } else if (std::memcmp("64", fmt + 1, 2) == 0) {
                            std::puts_n(buf, std::format_to<uint64_t>(buf, sizeof(buf), __builtin_va_arg(args, uint64_t), 16));
                            fmt += 2;
                        } else {
                            std::puts_n(buf, std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16));
                        }
                    } else
                        std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t), 16));
                } break;

                case 'X': {
                    char buf[int_strbuf_size] = {0};
                    if (*(fmt + 1) && *(fmt + 2)) {
                        if (std::memcmp("8", fmt + 1, 1) == 0) {
                            std::puts_n(buf,
                                        std::format_to<uint8_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16, true));
                            fmt++;
                        } else if (std::memcmp("16", fmt + 1, 2) == 0) {
                            std::puts_n(buf,
                                        std::format_to<uint16_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16, true));
                            fmt += 2;
                        } else if (std::memcmp("32", fmt + 1, 2) == 0) {
                            std::puts_n(buf,
                                        std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16, true));
                            fmt += 2;
                        } else if (std::memcmp("64", fmt + 1, 2) == 0) {
                            std::puts_n(buf,
                                        std::format_to<uint64_t>(buf, sizeof(buf), __builtin_va_arg(args, uint64_t), 16, true));
                            fmt += 2;
                        } else {
                            std::puts_n(buf,
                                        std::format_to<uint32_t>(buf, sizeof(buf), __builtin_va_arg(args, uint32_t), 16, true));
                        }
                    } else
                        std::puts_n(buf, std::format_to<int32_t>(buf, sizeof(buf), __builtin_va_arg(args, int32_t), 16, true));
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