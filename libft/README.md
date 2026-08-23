# libft

My implementation of the standard C library functions for 42 School. The goal
of this project is to re-code a set of libc functions and build a personal
library that can be reused in future C projects.

## Compiling

```bash
make        # builds libft.a (mandatory part)
make bonus  # also adds the linked-list functions into libft.a
make clean  # removes object files
make fclean # removes object files + libft.a
make re     # fclean + all
```

The Makefile compiles with `cc -Wall -Wextra -Werror`.

## Using the library

Compile it, then link the archive and include directory in your project:

```bash
make            # inside libft/
```

```c
#include "libft.h"
```

```bash
cc main.c -L/path/to/libft -lft -I/path/to/libft
```

Example:

```c
#include "libft.h"

int	main(void)
{
	char	**words;
	int		i;

	words = ft_split("hello world 42", ' ');
	if (!words)
		return (1);
	i = 0;
	while (words[i])
	{
		ft_putendl_fd(words[i], 1);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
```

> Every function that allocates memory (`ft_calloc`, `ft_strdup`, `ft_substr`,
> `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_lstmap`) must be
> freed by the caller.

## Part 1 — libc functions

| Function | Re-implements |
| --- | --- |
| `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint` | `<ctype.h>` checks |
| `ft_toupper`, `ft_tolower` | case conversion |
| `ft_strlen` | string length |
| `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp` | `<string.h>` memory |
| `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr` | `<string.h>` search/compare |
| `ft_strlcpy`, `ft_strlcat` | size-bounded copy/concat |
| `ft_atoi` | ASCII to int |
| `ft_calloc` | zeroed allocation |
| `ft_strdup` | duplicate string |

## Part 2 — additional functions

| Function | Description |
| --- | --- |
| `ft_substr(s, start, len)` | substring from `s` |
| `ft_strjoin(s1, s2)` | concatenate two strings |
| `ft_strtrim(s1, set)` | trim `set` chars from both ends |
| `ft_split(s, c)` | split string by delimiter into a NULL-terminated array |
| `ft_strmapi` / `ft_striteri` | apply function to each char (new string / in place) |
| `ft_itoa(n)` | int to ASCII |
| `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` | output to a file descriptor |

## Bonus — linked list

Single-linked list of type `t_list`:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | Description |
| --- | --- |
| `ft_lstnew(content)` | create a new node |
| `ft_lstadd_front(lst, new)` / `ft_lstadd_back(lst, new)` | insert node |
| `ft_lstsize(lst)` / `ft_lstlast(lst)` | length / last node |
| `ft_lstdelone(lst, del)` / `ft_lstclear(lst, del)` | free node(s) |
| `ft_lstiter(lst, f)` | apply `f` to every node's content |
| `ft_lstmap(lst, f, del)` | map contents into a new list |

---

Subject: [`libft.pdf`](libft.pdf)
