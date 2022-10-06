# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbenjami <nbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 13:53:16 by ksaffron          #+#    #+#              #
#    Updated: 2022/10/05 19:44:29 by nbenjami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

GCC = gcc

LIBFT = ./libft_l/libft.a

LIB_BINARY = -L ./libft_l -lft -lreadline -ledit

CFLAGS = -Wall -Wextra

INCLUDE_SYS = ~/Users/nbenjami/.brew/opt/readline/include

LIB_SYS = ~/Users/nbenjami/.brew/opt/readline/lib

SRCS = main.c \
	ft_split.c \
	ft_split_utils.c \
	utils_1.c \
	inits.c \
	errors.c \
	com_check.c \
	1cd.c \
	ft_command_split.c \
	1env.c \
	1pwd.c \
	1exit.c \
	ft_command_split_utils.c \
	1export.c \
	1unset.c \
	com_check_utils.c \
	1echo.c \
	split_wquots.c \
	com_check_reddir.c \
	ft_rebildredir.c \
	ft_rebildredir_utils.c  \
	signal_utils.c \
	ft_del_quot_1.c \
	creater_of_cmd.c \
	pipex.c \
	pipex_utils.c \
	execute.c \
	redirs.c \
	creater_of_cmd_utils.c \
	pipex_utils_1.c \
	utils_cd.c \
	utils_2.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) ./libft_l/libft.a $(NAME)

$(NAME): $(OBJS) $(LIBFT) minishell.h Makefile
	$(GCC) $(CFLAGS) $(OBJS) -L $(LIB_SYS) $(LIB_BINARY) -o $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_SYS)

$(LIBFT):
	make -C ./libft_l/ bonus

clean:
	rm -f $(OBJS) $(OBJSB)
	make -C ./libft_l/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
