# ft_printf

My re-implementation of `printf(3)` for 42 School. It reproduces the behavior
of the real printf for a defined set of conversions, handles all buffer
management itself, and returns the number of characters printed (or `-1` on
write error).

The library also includes the **bonus**: field width, precision and every flag
(`-`, `0`, `#`, `+`, space) working with every conversion.

## Compiling

```bash
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files + libftprintf.a
make re     # fclean + all
```

Compiled with `cc -Wall -Wextra -Werror`.

## Using it

```c
#include "ft_printf.h"
```

```bash
cc main.c -L/path/to/ft_printf -lftprintf -I/path/to/ft_printf
```

Example:

```c
#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("%s scored %d%% (%x in hex)\n", "player", 42, 42);
	ft_printf("printed %d characters\n", count);
	return (0);
}
```

Output:

```
player scored 42% (2a in hex)
printed 30 characters
```

## Supported conversions

| Specifier | Meaning |
| --- | --- |
| `%c` | single character |
| `%s` | string (`NULL` prints `(null)`) |
| `%p` | pointer address (`NULL` prints `(nil)`) |
| `%d`, `%i` | signed decimal int |
| `%u` | unsigned decimal int |
| `%x`, `%X` | hexadecimal, lowercase / uppercase |
| `%%` | literal percent sign |

## Flags and modifiers (bonus)

| Syntax | Effect |
| --- | --- |
| `-10d` | left-justify within the given width |
| `010d` | zero-pad to the width (ignored with `-` or precision) |
| `.5d` / `%.3s` | minimum digits for numbers / max chars for strings |
| `#x` | prefix `0x` / `0X` for non-zero values |
| `+d` | force a `+` sign for positive numbers |
| ` d` | space instead of `+` when `+` is absent |

Flags may be combined: `%-+10.5d`, `%#010x`, etc. Behavior matches glibc's
printf on edge cases (sign prefixes with `%p`, `%%` ignoring flags, empty
output for `%.0d` of zero, ...).

## Project structure

```
ft_printf.h        t_fmt state struct + prototypes
ft_printf.c        core loop: scans format, dispatches conversions
ft_printf_parse.c  flag / width / precision parser
ft_print_utils.c   low-level output helpers
ft_print_conv.c    %c %s %%
ft_print_int.c     %d %i
ft_print_uint.c    %u %x %X %p
ft_print_base.c    shared numeric engine (padding, signs, prefixes)
```

---

Subject: [`printf.pdf`](printf.pdf)
