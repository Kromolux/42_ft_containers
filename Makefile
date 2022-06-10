# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 21:06:31 by rkaufman          #+#    #+#              #
#    Updated: 2022/06/10 19:18:42 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	containers

CC			:=	c++

SRCS		:=	main.cpp

OBJS		:=	$(SRCS:%.cpp=%.o)

CFLAGS		=	-Wall -Wextra -Werror -std=c++98
DFLAG		:=	-g -D DEBUG=1
TFLAG		:=	-D TEST=1

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
	rm -fr $(NAME)

re: fclean all

test: re
		./$(NAME) > ft.out
test: CFLAGS += $(TFLAG)
test: re
		./$(NAME) > std.out
		diff ft.out std.out

std: CFLAGS += $(TFLAG)
std: re
	./$(NAME)

ft: re
	./$(NAME)

val:
	valgrind --leak-check=full -s ./$(NAME)

leak:
	leaks --atExit -- ./$(NAME)

.PHONY: clean fclean re
