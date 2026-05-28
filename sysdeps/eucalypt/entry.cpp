#include <stdint.h>
#include <stdlib.h>
#include <mlibc/elf/startup.h>

extern "C" void __dlapi_enter(uintptr_t *);

extern char **environ;

extern "C" void __mlibc_entry(uintptr_t *entry_stack,
    int (*main_fn)(int, char **, char **)) {
    mlibc::exec_stack_data stack;
    mlibc::parse_exec_stack(entry_stack, &stack);
    mlibc::set_startup_data(stack.argc, stack.argv, stack.envp);
    exit(main_fn(stack.argc, stack.argv, stack.envp));
}
