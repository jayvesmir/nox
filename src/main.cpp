
extern "C" {
void cabi_main() {
    char* const uart = reinterpret_cast<char* const>(0x10000000);

    *uart = 'n';
    *uart = 'o';
    *uart = 'x';
}
}