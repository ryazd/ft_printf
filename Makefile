.PHONY: all libmake ft_printf clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./libft -lftprintf
NAME = libftprintf.a
SOURCES = ft_printf.c ft_ptf_float_binary.c ft_ptf_integer.c ft_ptf_parse.c \
		  ft_ptf_print.c ft_ptf_string.c ft_ptf_non_printable.c
OBJECTS = $(subst .c,.o,$(SOURCES))

all: $(NAME)

libmake:
	@(cd libft; make)

$(NAME): libmake $(OBJECTS)
	@cp libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@(cd libft; make clean)
	@rm -rf $(OBJECTS)

fclean:
	@(cd libft; make fclean)
	@rm -rf $(OBJECTS)
	@rm -rf $(NAME)

re: fclean all
