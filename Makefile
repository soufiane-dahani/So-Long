SRCS = ft_printf.c ft_printf_utils.c graphics.c map_utils.c map.c player.c so_long_maloc.c \
		so_long.c utils.c

#SRCSB = 

OBJS = ${SRCS:.c=.o}
#OBJSB = ${SRCSB:.c=.o}
NAME = so_long
#NAMEB = checker
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lmlx -lX11 -lXext

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME} $(LDFLAGS)

#bonus: ${NAMEB}

#${NAMEB}: ${OBJSB}
 
all: ${NAME}

clean:
	${RM} ${OBJS} ${OBJSB}

fclean: clean
	${RM} ${NAME} ${NAMEB} 

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: