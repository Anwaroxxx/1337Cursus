NAME     = libget_next_line.a
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)
BUFFER_SIZE ?= 42
AR       = ar
ARFLAGS  = rcs

SRCS     = get_next_line.c \
	get_next_line_utils.c

SRCS_BONUS = get_next_line_bonus.c \
	get_next_line_utils_bonus.c

OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus: all $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
