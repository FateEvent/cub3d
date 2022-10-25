# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/10/25 15:57:11 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
ARGS		=	map.cub
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g3
LINKS		=	-lglfw -L /goinfre/${USER}/.brew/Cellar/glfw/3.3.8/lib/ #-ldl -lm #linuxflags
LIBLINKS	=	-I./MLX42/include/MLX42 -I./includes -I./libft/includes
SRC_PATH	=	srcs/
OBJ_PATH	=	bin/
C_EXTENSION	=	.c

MAIN_PATH	=	main/
MAIN_FILES	=	main
SRCS_FILES	+=	$(addprefix $(MAIN_PATH), $(MAIN_FILES))

PARSE_PATH	=	parsing/
PARSE_FILES	=	check check_map check_map_utils check_map_utils2 gap_check \
				gap_check_reverse get_color get_color2 get_texture hole_check \
				invalid_check wall_check get_spawn_position
SRCS_FILES	+=	$(addprefix $(PARSE_PATH), $(PARSE_FILES))

MLX_PATH	=	mlx_tools/
MLX_FILES	=	textures window colours colour_conversions
SRCS_FILES	+=	$(addprefix $(MLX_PATH), $(MLX_FILES))

UTILS_PATH	=	utils/
UTILS_FILES	=	ft_map_reader drawing_tools utils ft_from_uchar_to_rgb_buf \
				vec_utils
SRCS_FILES	+=	$(addprefix $(UTILS_PATH), $(UTILS_FILES))

RC_PATH		=	ray_casting/
RC_FILES	=	hooks hooks_2 ray_casting_tools wall_casting wall_casting_vol2 \
				floor_ceiling_textures
SRCS_FILES	+=	$(addprefix $(RC_PATH), $(RC_FILES))

MD_PATH		=	map_display/
MD_FILES	=	ft_display_map
SRCS_FILES	+=	$(addprefix $(MD_PATH), $(MD_FILES))

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

RM	=	rm -f

SRCS_FILES_EXT	+=	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))

SRCS			+=	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))

OBJS			=	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:c=o))

NONE	= \033[0m
HIGREEN	= \033[92m
HIBLUE	= \033[94m
CURSIVE	= \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC ./libft
	@$(MAKE) -sC ./MLX42
	@mv ./libft/libft.a .
	@mv ./MLX42/libmlx42.a .
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) libft.a libmlx42.a $(LINKS) -fsanitize=address
	@echo "$(CURSIVE)$(HIBLUE)Parce qu'ouvrir une fenêtre,$(NONE)"
	@echo "$(CURSIVE)$(HIGREEN)c'est surfait.$(NONE)"

.c.o:
	@$(CC) $(FLAGS) -c $(LIBLINKS) $< -o ${<:.c=.o}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} ${LIBLINKS} -c $< -o $@

exe: all
	@./$(NAME) $(ARGS)

clean:
	@$(RM) -r libft.a libmlx42.a $(OBJ_PATH)
	@$(MAKE) clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

relib: fclean
	@$(MAKE) re -sC ./MLX42
	@$(MAKE) all

.PHONY: all exe clean fclean re