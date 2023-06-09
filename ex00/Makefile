# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:07:13 by jleroux           #+#    #+#              #
#    Updated: 2023/06/23 14:24:57 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	btc

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \
				$(SRC_DIR)/BitcoinExchange.cpp \
				$(SRC_DIR)/KV.cpp \

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
	clear
	@echo --- School tests ---
	-./$(NAME)
	@echo
	./$(NAME) input.txt
	@echo
	@echo --- My tests ---
	./$(NAME) myTests.txt

leaks: all
	clear
	leaks -quiet -atExit -- ./$(NAME) inputfile

.PHONY: all clean fclean re run leaks
