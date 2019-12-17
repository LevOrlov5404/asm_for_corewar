# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnita <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 21:05:08 by pnita             #+#    #+#              #
#    Updated: 2019/12/10 21:05:09 by pnita            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FLAG = #-Wall -Wextra -Werror

FT_PRINTF = ft_printf

DIR_S = srcs

DIR_O = temporary

HEADER = include

SOURCES = assembler.c \
		  dop_functions.c \
		  error_exit.c \
		  name_comment.c \
		  get_name.c \
		  set_arg.c \
		  do_with_oper.c \
		  detect_op.c \
		  lbl.c \
		  oper.c \
		  arg.c \
		  lbl_arg.c \
		  join_s_to_buff.c \
		  do_with_buff.c \
		  delete.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

FORCE:		;

$(FT_PRINTF):	FORCE
	make -C $(FT_PRINTF)

$(NAME): $(FT_PRINTF) $(OBJS) $(FT_PRINTF)/libftprintf.a $(HEADER)/*.h
	gcc -o $(NAME) $(FLAG) $(SRCS) $(FT_PRINTF)/libftprintf.a -g

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p temporary
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	rm -rf $(DIR_O)
	rm -f $(OBJS)
	make clean -C $(FT_PRINTF)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(FT_PRINTF)

re: fclean all
