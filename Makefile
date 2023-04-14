NAME = cub3d

all:
	gcc -I includes/ cub3d.c libft/*.c src/*.c src/*/*.c -lm -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)