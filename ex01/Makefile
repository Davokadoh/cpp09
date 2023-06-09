# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:07:13 by jleroux           #+#    #+#              #
#    Updated: 2023/06/23 15:15:08 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RPN

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \
				$(SRC_DIR)/RPN.cpp \

INCS		=	inc

CXX			=	c++#g++-13
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
	-clear
	-@echo From PDF
	-./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	-./$(NAME) "7 7 * 7 -"
	-./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	-./$(NAME) "(1 + 1)"
	-@echo
	-@echo My Tests
	-./$(NAME) "1 + 1"
	-./$(NAME) "+ 1 1"
	-./$(NAME) "1 1 +"
	-./$(NAME) 1 2 + 4 -
	-./$(NAME) "1 2 + 4 -"
	-./$(NAME) "1 2 + 4 * 3 +"
	-./$(NAME) "3 4 1 2 + * +"
	-./$(NAME) "3 4 7 +"
	-./$(NAME) "3 0 /"
	-./$(NAME) "3 a +"
	-./$(NAME) 5
	-./$(NAME) 

leaks: all
	-clear
	-@echo From PDF
	-leaks -quiet -atExit -- ./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	-leaks -quiet -atExit -- ./$(NAME) "7 7 * 7 -"
	-leaks -quiet -atExit -- ./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	-leaks -quiet -atExit -- ./$(NAME) "(1 + 1)"
	-@echo
	-@echo My Tests
	-leaks -quiet -atExit -- ./$(NAME) "1 + 1"
	-leaks -quiet -atExit -- ./$(NAME) "+ 1 1"
	-leaks -quiet -atExit -- ./$(NAME) "1 1 +"
	-leaks -quiet -atExit -- ./$(NAME) 1 2 + 4 -
	-leaks -quiet -atExit -- ./$(NAME) "1 2 + 4 -"
	-leaks -quiet -atExit -- ./$(NAME) 1 2 + 4 * 3 +
	-leaks -quiet -atExit -- ./$(NAME) 3 4 1 2 + * +
	-leaks -quiet -atExit -- ./$(NAME) 3 4 7 +
	-leaks -quiet -atExit -- ./$(NAME) 

.PHO-NY: all clean fclean re run leaks
