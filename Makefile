NAME		=	so_long
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
MLX			=	mlx/Makefile.gen
INC			=	-I ./inc -I ./libft -I ./mlx
LIB			=	-L ./libft -lft -L ./mlx -lmlx -lXext -lX11 -lm -lbsd
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/mlx_utils.c \
				src/so_long.c

all:		$(MLX) obj $(NAME)

$(NAME):	$(OBJ)
			make -C libft
			$(CC) $(FLAGS) -fsanitize=address -o $@ $^ $(LIB)

$(MLX):
			make -C mlx

obj:
			mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
			make $@ -C libft
			rm -rf $(OBJ) obj

fclean:		clean
			make $@ -C libft
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
