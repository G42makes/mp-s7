#include "retro/Console.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

//Here we start to merge the C code from the MP minimal example with the C++ code from the Retro68 Console example
extern "C" {

#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "lib/utils/pyexec.h" 

}

extern "C" int mp_hal_stdin_rx_chr(void);
extern "C" void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);

#if MICROPY_ENABLE_COMPILER
void do_str(const char *src, mp_parse_input_kind_t input_kind) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // uncaught exception
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}
#endif

static char *stack_top;
#if MICROPY_ENABLE_GC
static char heap[2048];
#endif


namespace retro
{
    void InitConsole();
}

int main()
{
    int stack_dummy;
    stack_top = (char*)&stack_dummy;

    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init();


    retro::InitConsole();
    //std::string out = "Hello, world.\nEnter \"exit\" to quit.\n";
    //retro::Console::currentInstance->write(out.data(), out.size());

    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }

    /*
    std::string in;
    do
    {
        in = retro::Console::currentInstance->ReadLine();
        out = "You Entered: " + in;
        retro::Console::currentInstance->write(out.data(), out.size());
    } while(in != "exit\n");
    */

    mp_deinit();
    return 0;

}

extern "C" void gc_collect(void) {
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    void *dummy;
    gc_collect_start();
    gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end();
    gc_dump_info();
}

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    //int r = write(1, str, len);
    retro::Console::currentInstance->write(str, len);
    //(void)r;
}

