# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 21:06:31 by rkaufman          #+#    #+#              #
#    Updated: 2022/08/21 17:55:27 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	containers

CC			:=	c++

SEED		:=	612345678901011

SRC_MYTEST	:=	main.cpp \
				tests/vector_test.cpp \
				tests/stack_test.cpp \
				tests/map_test.cpp \
				tests/set_test.cpp \
				tests/RBT_test.cpp

SRC_SUBJECT	:=	tests/subject_test.cpp

OBJS			:=	$(SRCS:%.cpp=%.o)
OBJS_MYTEST		:=	$(SRC_MYTEST:%.cpp=%.o)
OBJS_SUBJECT	:=	$(SRC_SUBJECT:%.cpp=%.o)

VECTOR		:=	-D TEST_VECTOR=1
STACK		:=	-D TEST_STACK=1
MAP			:=	-D TEST_MAP=1
SET			:=	-D TEST_SET=1
ALL			:=	-D TEST_ALL=1
STD			:=	-D TEST_STD=1
FT			:=	-D TEST_FT=1
RBT			:=	-D TEST_RBT=1

CFLAGS		=	-g -Wall -Wextra -Werror -std=c++98
DFLAG		:=	-g -D DEBUG=1
TFLAG		=	-D TEST_ALL=1
#TEST_ALL=1

all:	$(NAME)

$(NAME): $(OBJS_MYTEST)
	$(CC) $(CFLAGS) $(TFLAG) $(OBJS_MYTEST) -o $(NAME)

$(OBJS_MYTEST): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(TFLAG) $< -o $@

test: $(OBJS_SUBJECT)
	$(CC) $(CFLAGS) $(TFLAG) $(OBJS_SUBJECT) -o $(NAME)

$(OBJS_SUBJECT): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(TFLAG) $< -o $@

debug: CFLAGS += $(DFLAG)
debug: re
	./$(NAME)

clean:
	rm -fr $(OBJS_MYTEST) $(OBJS_SUBJECT)

fclean: clean
	rm -fr $(NAME) $(NAME).dSYM

re: fclean all

vector:	TFLAG = $(VECTOR)
vector:	re
	./$(NAME)

stack: TFLAG = $(STACK)
stack: re
	./$(NAME)

map: TFLAG = $(MAP)
map: re
	./$(NAME)

set: TFLAG = $(SET)
set: re
	./$(NAME)

test_std: TFLAG = $(STD)
test_std: clean test
	./$(NAME) $(SEED)

test_ft: TFLAG = $(FT)
test_ft: clean test
	./$(NAME) $(SEED)

rbt: TFLAG = $(RBT)
rbt: re
	./$(NAME)

#test: ft std
#	diff -y --suppress-common-lines ft.out std.out

#std: CFLAGS += $(TFLAG)
#std: re
#	./$(NAME) > std.out

#ft:
#	make re
#	./$(NAME) > ft.out

#val: CFLAGS += $(TFLAG)
val:
	valgrind --leak-check=full -s ./$(NAME)

leak:
	leaks --atExit -- ./$(NAME)

.PHONY: clean fclean re std ft test_ft test_std
