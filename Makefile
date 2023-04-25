NAME = cub3d
CC = gcc
HEADERS = includes/get_next_line.h includes/cub3d.h
MLX_FLAGS = -lm -Lmlx -lmlx -framework OpenGL -framework AppKit
CC_FLAGS = -I includes/ -Wall -Wextra -Werror
SRC = $(wildcard *.c) $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ) -o $(NAME) 

%.o : %.c $(HEADERS)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

norm :
	norminette libft cub3d.c src includes