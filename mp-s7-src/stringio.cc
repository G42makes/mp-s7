extern "C" {
#include <unistd.h>
#include "py/mpconfig.h"
}

extern "C" int mp_hal_stdin_rx_chr(void);
extern "C" void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
