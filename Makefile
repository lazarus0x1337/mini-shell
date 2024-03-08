NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/ft_split.c tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c environnement/env.c parsing/utils.c mini-shell.c 
OBJS = $(SRCS:.c=.o)

all : $(NAME)

#%.o: %.c
#    cc $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	cc  $(CFLAGS) -o $@ $^ -lreadline

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all
