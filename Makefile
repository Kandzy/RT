# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/20 21:21:14 by dkliukin          #+#    #+#              #
#    Updated: 2018/10/20 21:21:15 by dkliukin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	parsing/run_scene.c parsing/additional_function.c parsing/find_tag_position.c parsing/check_rgb_type.c parsing/check_rotation_field.c\
	parsing/check_transparency_field.c parsing/get_template_object.c parsing/match_tag.c parsing/tag_information_parsing.c parsing/set_params_in_template.c\
	parsing/check_hex_field.c parsing/check_fields.c parsing/processing_scene.c \
	warning/warning.c warning/camera_warning.c warning/light_warning.c warning/scene_warning.c warning/type_warning.c warning/custom_warning.c\
	error/error.c error/file_error.c warning/warning_ext.c\

SRC_DIR = ./src/
OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR),$(SRC:.c=.o))
INC = ./include/rt.h ./include/scene.h ./include/warning.h ./include/error.h ./include/parsing.h\
		./include/external.h
NAME = rt
# CFLAG = -Werror -Wextra -Wall -O2
# FRAMEWORK =  -framework SDL2
FRAMEWORK_PATH = -F /Library/Frameworks
LIBDIR = ./libft
CC = gcc -g
REMAKE = rmk

$(OBJ_DIR)%.o: %.c $(INC)
		@echo "\033[0;32mCreating object file\033[0m \033[31m$@\033[0m"
		@$(CC) $(CFLAG) $(FRAMEWORK_PATH) -c $< -o $@ -I $(LIBDIR)

all:  $(NAME)

$(NAME): $(OBJ)
		@echo "\033[0;32mCompile solution ...\033[0m"
		@echo "\033[0;32mCompile library ...\033[0m"
		@make -C $(LIBDIR)
		@$(CC) $(CFLAG) -lpthread -o $(NAME) $(OBJ) $(FRAMEWORK_PATH) $(FRAMEWORK) $(LIBDIR)/libft.a
		@echo "\033[0;32mProgram compiled : \033[0m\033[31m$(NAME)\033[0m"
		
$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)
		@mkdir $(OBJ_DIR)/parsing
		@mkdir $(OBJ_DIR)/warning
		@mkdir $(OBJ_DIR)/error

clean:
		@echo "\033[0;32mCleaning object files ...\033[0m"
		@make clean -C $(LIBDIR)
		@rm -rf $(OBJ_DIR)
		@rm -f $(OBJ)

fclean: clean
		@make fclean -C $(LIBDIR)
		@rm -f $(NAME)
		@echo "\033[31m$(NAME)\033[0m\033[0;32m was completely removed\033[0m"

re: $(REMAKE) fclean all

$(REMAKE):
		@echo "\033[0;32mRemaking project \033[0m\033[31m$(NAME)\033[0m" 
vpath %.c $(SRC_DIR)
