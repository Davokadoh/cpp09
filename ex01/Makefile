# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:07:13 by jleroux           #+#    #+#              #
#    Updated: 2023/04/27 11:35:42 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RPC

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \

INCS		=	inc

CXX			=	c++#g++-12
CXXFLAGS	=	-std=c++98
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
	@echo From PDF
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	./$(NAME) "(1 + 1)"
	@echo
	@echo My Tests
	./$(NAME) "1 + 1"
	./$(NAME) "+ 1 1"
	./$(NAME) "1 1 +"
	./$(NAME) 1 2 +
	./$(NAME) 1 2 + 4 -
	./$(NAME) "1 2 + 4 -"
	./$(NAME) 1 2 + 4 \* 3 +
	./$(NAME) 3 4 1 2 + \* +
	./$(NAME) 3 4 7 + 
	./$(NAME) 3 0 /
	./$(NAME) 5
	./$(NAME) 

leaks: all
	clear
	@echo From PDF
	leaks -atExit -- ./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	leaks -atExit -- ./$(NAME) "7 7 * 7 -"
	leaks -atExit -- ./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	leaks -atExit -- ./$(NAME) "(1 + 1)"
	@echo
	@echo My Tests
	leaks -atExit -- ./$(NAME) "1 + 1"
	leaks -atExit -- ./$(NAME) "+ 1 1"
	leaks -atExit -- ./$(NAME) "1 1 +"
	leaks -atExit -- ./$(NAME) 1 2 +
	leaks -atExit -- ./$(NAME) 1 2 + 4 -
	leaks -atExit -- ./$(NAME) "1 2 + 4 -"
	leaks -atExit -- ./$(NAME) 1 2 + 4 \* 3 +
	leaks -atExit -- ./$(NAME) 3 4 1 2 + \* +
	leaks -atExit -- ./$(NAME) 3 4 7 +
	leaks -atExit -- ./$(NAME) 

.PHONY: all clean fclean re run leaks
