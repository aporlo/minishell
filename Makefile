#variables
NAME = myshell
CC = gcc
FLAGS = -Wall -Wextra -Werror
LINKING = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE = -I${HOME}/.brew/opt/readline/include
SDIR = srcs/
LIB = libft
INC = include
RDIR = /usr/include

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

OBJS = $(addprefix $(SDIR), $(SRC_NAME:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ echo "$(YELLOW)Make libft.a library$(DEFCO)"
	@ make bonus -C $(LIB)
	@ echo "$(GREEN)libft.a created$(DEFCO)"
	@ $(CC) $(FLAGS) $^ -L $(LIB) -lft -I $(INC) -I $(LIB) -lreadline -o $(NAME)
	@ echo "$(GREEN)$(NAME) created$(DEFCO)" 

$(SDIR)%.o : $(SDIR)%.c
	@ $(CC) $(FLAGS) -c $< -o $@ -I $(INC) -I $(LIB)

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
