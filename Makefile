# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 21:06:31 by rkaufman          #+#    #+#              #
#    Updated: 2022/07/20 11:02:39 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	containers

CC			:=	c++

SRCS		:=	main.cpp

OBJS		:=	$(SRCS:%.cpp=%.o)

CFLAGS		=	-g -Wall -Wextra -Werror -std=c++98
DFLAG		:=	-g -D DEBUG=1
TFLAG		:=	-g -D TEST=1

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

debug: CFLAGS += $(DFLAG)
debug: re
	./$(NAME)

clean:
	rm -fr $(OBJS)

fclean: clean
	rm -fr $(NAME) $(NAME).dSYM

re: fclean all

test: ft std
	diff -y --suppress-common-lines ft.out std.out

std: CFLAGS += $(TFLAG)
std: re
	./$(NAME) > std.out

ft:
	make re
	./$(NAME) > ft.out

#val: CFLAGS += $(TFLAG)
val: re
	valgrind --leak-check=full -s ./$(NAME)

leak:
	leaks --atExit -- ./$(NAME)

.PHONY: clean fclean re std ft test
