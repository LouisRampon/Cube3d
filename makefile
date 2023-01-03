# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 11:47:12 by lorampon          #+#    #+#              #
#    Updated: 2023/01/03 19:06:39 by lorampon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS_MAIN_WITHOUT_PATH = main.c	\


SRCS_PARSING_WITHOUT_PATH = ft_parsing.c			\
							ft_parse_options.c		\
							ft_parse_map.c			\
							ft_init_map.c			\
							ft_init_list.c			\
							get_next_line.c			\
							get_next_line_utils.c	\
							ft_lst_to_tab.c			\


SRCS_EXEC_WITHOUT_PATH =	move.c \
							raycasting.c \
							raycasting_h.c \
							raycasting_v.c \
							mlx_hook.c		\
							display.c		\
							draw.c 			\
							
							
SRCS_UTILS_WITHOUT_PATH = 	map_utils.c\
							ft_split_charset.c		\
							ft_free_tab.c			\
							ft_error_exit.c			\
							ft_count_char.c			\
							ft_alloc.c				\
							ft_arena_storage_pool.c	\

OBJS_SRCS_MAIN_WITHOUT_PATH = $(SRCS_MAIN_WITHOUT_PATH:.c=.o)
OBJS_SRCS_PARSING_WITHOUT_PATH = $(SRCS_PARSING_WITHOUT_PATH:.c=.o)
OBJS_SRCS_ENV_WITHOUT_PATH = $(SRCS_ENV_WITHOUT_PATH:.c=.o)
OBJS_SRCS_EXEC_WITHOUT_PATH = $(SRCS_EXEC_WITHOUT_PATH:.c=.o)
OBJS_SRCS_UTILS_WITHOUT_PATH = $(SRCS_UTILS_WITHOUT_PATH:.c=.o)
OBJS_SRCS_BUILT_IN_WITHOUT_PATH = $(SRCS_BUILT_IN_WITHOUT_PATH:.c=.o)

HEADER_WITHOUT_PATH = cub3d.h

PATH_TO_SRCS_MAIN = ./srcs/
PATH_TO_LIB_DIR = ./libft/
PATH_TO_SRCS_PARSING = ./srcs/parsing/
PATH_TO_SRCS_EXEC = ./srcs/exec/
PATH_TO_SRCS_UTILS = ./srcs/utils/
PATH_TO_OBJS = ./.objs/
PATH_TO_HEADER = ./includes/
PATH_TO_MLX = ./mlx/

SRCS_MAIN = $(addprefix $(PATH_TO_SRCS_MAIN), $(SRCS_MAIN_WITHOUT_PATH))
SRCS_PARSING = $(addprefix $(PATH_TO_SRCS_PARSING), $(SRCS_PARSING_WITHOUT_PATH))
SRCS_EXEC = $(addprefix $(PATH_TO_SRCS_EXEC), $(SRCS_EXEC_WITHOUT_PATH))
SRCS_UTILS = $(addprefix $(PATH_TO_SRCS_UTILS), $(SRCS_UTILS_WITHOUT_PATH))


OBJS_SRCS_MAIN = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_MAIN_WITHOUT_PATH))
OBJS_SRCS_PARSING = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_PARSING_WITHOUT_PATH))
OBJS_SRCS_EXEC = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_EXEC_WITHOUT_PATH))
OBJS_SRCS_UTILS = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_UTILS_WITHOUT_PATH))



OBJS =	$(OBJS_SRCS_MAIN)		\
		$(OBJS_SRCS_PARSING)	\
		$(OBJS_SRCS_EXEC)		\
		$(OBJS_SRCS_UTILS) 		
		
HEADER =	$(addprefix $(PATH_TO_HEADER), $(HEADER_WITHOUT_PATH))

	######### COMMANDS ###########
CC = gcc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS_MLX = -framework OpenGL -framework AppKit
RM = rm -rf
PATH_TO_LIBFT = ./libft/
LIBFT_A = $(PATH_TO_LIBFT)libft.a
PATH_TO_MLX = ./mlx/
MLX_A = $(PATH_TO_MLX)libmlx.a
	################################

	####### COLORS FOR PRINTF #######
GREEN 		= \033[0;32m
RED			= \033[0;91m
YELLOW      = \033[0;93m
WHITE       = \033[1;49;97m
	#################################
	
all: rcs $(PATH_TO_OBJS) $(NAME)
	printf "$(GREEN) $(NAME) is up to date$(WHITE)\n" 

$(PATH_TO_OBJS):
	mkdir -p ./.objs/

$(OBJS_SRCS_MAIN):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_MAIN)%.c Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW) Compiling:$(WHITE) $<"
	$(CC) $(CFLAGS) $(READLINE_HOMEBREW_INCLUDE) -c $< -o $@

$(OBJS_SRCS_PARSING):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_PARSING)%.c Makefile $(HEADER) 
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_SRCS_ENV):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_ENV)%.c Makefile $(HEADER) 
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@
	

$(OBJS_SRCS_EXEC):$(PATH_TO_OBJS)%.o : $(PATH_TO_SRCS_EXEC)%.c Makefile $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJS_SRCS_UTILS):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_UTILS)%.c Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_SRCS_BUILT_IN):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_BUILT_IN)%.c Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(MLX_A)
	printf "\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(CFLAGS_MLX) -o $(NAME)

rcs: 
	make -C $(PATH_TO_MLX)
	make -C $(PATH_TO_LIB_DIR)

git: fclean
	git add *
	git add -u
	git commit
	
clean:
	$(RM) $(PATH_TO_OBJS)
	printf "$(RED) Files has been deleted in $(PATH_TO_OBJS) ($(NAME))$(WHITE)\n" 
	printf "$(GREEN) Clean $(WHITE)\n" 
	
fclean: clean
	$(RM) $(NAME)
	printf "$(RED) $(NAME) has been deleted$(WHITE)\n" 
	
re: fclean all

.PHONY: all rcs git clean fclean re
.SILENT: