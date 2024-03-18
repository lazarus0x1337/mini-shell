NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/ft_split.c \
tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c \
environnement/env.c environnement/utils.c\
builtins/builtins_functions.c mini-shell.c \
parsing/parsing.c execution/execute_tree.c \
execution/execute_simple_cmd.c \
execution/get_next_line.c execution/get_next_line_utils.c 
OBJS = $(SRCS:.c=.o)

all : $(NAME)

#%.o: %.c
#    cc $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	cc  -g3 $(CFLAGS)  -fsanitize=address -o $@ $^ -lreadline

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all
