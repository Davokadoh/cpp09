# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:07:13 by jleroux           #+#    #+#              #
#    Updated: 2023/04/26 10:37:38 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RPC

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \

INCS		=	inc

CXX			=	g++-12
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
	./$(NAME) "1 + 1"
	./$(NAME) "+ 1 1"
	./$(NAME) "1 1 +"
	./$(NAME) 1 2 +
	./$(NAME) 1 2 + 4 -
	./$(NAME) "1 2 + 4 -"
	./$(NAME) 1 2 + 4 \* 3 +
	./$(NAME) 3 4 1 2 + \* +
	@echo
	@echo From PDF
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	./$(NAME) "(1 + 1)"

leaks: all
	clear
	leaks -atExit -- ./$(NAME)

.PHONY: all clean fclean re run leaks
