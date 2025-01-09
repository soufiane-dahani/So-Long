SRCS = ft_printf.c ft_printf_utils.c graphics.c map_utils.c map.c player.c so_long_maloc.c \
       so_long.c utils.c get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}
NAME = so_long
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror


LDFLAGS = -lmlx -lX11 -lXext

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME} $(LDFLAGS)

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:
