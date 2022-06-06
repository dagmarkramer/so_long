NAME := so_long
HEADERFILES := so_long.h
SRCFILES := main.c displaymap.c mlx_utils.c mapparsing.c std_functions.c \
	checkers.c
OBJFILES := $(SRCFILES:%.c=%.o)
MLX		=	mlx/libmlx.a
LIBFT := libft/libft.a
CFLAGS ?= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJFILES)
	$(MAKE) -C libft
	$(MAKE) -C mlx
	$(CC) $(CFLAGS) -Llibft -lft -Lmlx -lmlx -framework OpenGL \
		-framework AppKit -o $@ $^

%.o: %.c $(HEADERFILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean
	rm -f $(OBJFILES)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
