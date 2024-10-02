#pragma once

namespace processor {
    namespace ext {
        bool supports_f();
        bool supports_v();

        void enable_v();
        void enable_f();
        void disable_v();
        void disable_f();
    } // namespace ext

} // namespace processor