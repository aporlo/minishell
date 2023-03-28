#variables
NAME = myshell
CC = gcc
FLAGS = -Wall -Wextra -Werror
SDIR = srcs/
LIB = libft
LREAD = /usr/local/Cellar/readline/8.2.1
INC = include
INC_ALL = 	-I$(INC) \
			-I$(LIB) \
			-I$(LREAD)/include 
LINK = 	-lreadline -L$(LREAD)/lib \
		-lft -L$(LIB) \

#color
DEFCO = '\033[0m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
MAGENTA = '\033[0;35m'
CYAN = '\033[0;36m'

#sources
SRC_NAME = 	myshell_main.c \
			lexer.c \
			parser.c \
			executor.c \
			exe_single.c \
			exe_signal.c \
			exe_pipex.c \
			init.c \

OBJS = $(addprefix $(SDIR), $(SRC_NAME:.c=.o))

all : $(NAME)

$(SDIR)%.o : $(SDIR)%.c
	@ $(CC) $(FLAGS) $(INC_ALL) -c $< -o $@ 

$(NAME) : $(OBJS)
	@ echo "$(YELLOW)Make libft.a library$(DEFCO)"
	@ make -C $(LIB)
	@ echo "$(GREEN)libft.a created$(DEFCO)"
	@ $(CC) $(FLAGS) $(OBJS) $(LINK) -o $(NAME)
	@ echo "$(GREEN)$(NAME) created$(DEFCO)" 



clean:
	@ make clean -C $(LIB)
	@ echo "$(YELLOW)libft.a removed$(DEFCO)"
	@ rm $(SDIR)*.o 
	@ echo "$(GREEN)Object files removed$(DEFCO)"

fclean: clean
	@ rm -f $(NAME)
	@ make fclean -C $(LIB)
	@ echo "$(GREEN)$(NAME) removed$(DEFCO)"

re: fclean all

.PHONY: all clean fclean res
