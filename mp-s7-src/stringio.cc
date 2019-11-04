//#include "retro/Console.h"

extern "C" {
#include <unistd.h>
#include "py/mpconfig.h"
}

extern "C" int mp_hal_stdin_rx_chr(void);
extern "C" void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    //int r = write(1, str, len);
    //retro::Console::currentInstance->write(str, len);
    //(void)r;
}
