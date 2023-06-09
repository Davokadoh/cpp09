# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:07:13 by jleroux           #+#    #+#              #
#    Updated: 2023/06/23 14:23:42 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	PmergeMe

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \
				$(SRC_DIR)/PmergeMe.cpp \
				$(SRC_DIR)/Vec.cpp \
				$(SRC_DIR)/Deq.cpp \

INCS		=	inc

CXX			=	c++#g++-13
CXXFLAGS	=	-std=c++98 -O2
CPPFLAGS	=	-Wall -Wextra -Werror -pedantic \
				$(addprefix -I,$(INCS)) -MMD -MP \

RM			=	rm -rf

BUILD_DIR	=	bin
OBJS		=	$(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS        =	$(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

run: all
	clear
	./$(NAME) 7 5 3 1 6 4 2

test: all
	clear
	./$(NAME) 7
	./$(NAME) 7 5
	./$(NAME) 5 7
	./$(NAME) 7 5 3
	./$(NAME) 7 5 3 1
	./$(NAME) 7 5 3 1 6 4 2
	./$(NAME) 7 5 3 1 6 4 2 0
	./$(NAME) 6 5 6 1 6 4 6 0
	./$(NAME) 6 6 6 1 6 6 6 6
	./$(NAME) z e f d a

stress: all
	clear
	./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`

leaks: all
	clear
	-leaks -quiet -atExit -- ./$(NAME)
	-leaks -quiet -atExit -- ./$(NAME) 7
	-leaks -quiet -atExit -- ./$(NAME) 7 5
	-leaks -quiet -atExit -- ./$(NAME) 5 7
	-leaks -quiet -atExit -- ./$(NAME) 7 5 3
	-leaks -quiet -atExit -- ./$(NAME) 7 5 3 1
	-leaks -quiet -atExit -- ./$(NAME) 7 5 3 1 6 4 2
	-leaks -quiet -atExit -- ./$(NAME) 7 5 3 1 6 4 2 0
	-leaks -quiet -atExit -- ./$(NAME) 6 5 6 1 6 4 6 0
	-leaks -quiet -atExit -- ./$(NAME) 6 6 6 1 6 6 6 6
	-leaks -quiet -atExit -- ./$(NAME) z e f d a

.PHONY: all clean fclean re run leaks
