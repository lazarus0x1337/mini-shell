#include "../minishell.h"

void ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    i = 0;
    if (dstsize == 0)
        return;
    while (src[i] && i < dstsize - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char *mystrdup(t_token *tokens, char *input)
{
    char *token;

    token = malloc(sizeof(char) * (tokens->len + 1));
    if (token == NULL)
        return (NULL);
    ft_strlcpy(token, input + tokens->index, tokens->len + 1);
    return (token);
}

void tokenisation(t_token **tokens, char *input)
{
    t_token *tmp;

    tmp = *tokens;
    while (tmp)
    {
        tmp->str = mystrdup(tmp, input);
        tmp = tmp->next;
    }
    tmp = NULL;
}

int is_qoutes(char c)
{
	if (c == '\"')
		return (2);
	if (c == '\'')
		return (1);
	return (0);
}

void handling_qoutes(t_token **tk)
{
	t_token *tmp;
	int i;
	int j;
	int flag;
	char stock[100];
	
	tmp = *tk;
	flag = 0;
	while (tmp)
	{
		j = 0;
		i = 0;
		while(tmp->str && tmp->str[i])
		{
			if ((flag = is_qoutes(tmp->str[i])))
				i++;
			while (tmp->str[i] && (!is_qoutes(tmp->str[i]) || (flag != is_qoutes(tmp->str[i]) && flag != 0)))
				stock[j++] = tmp->str[i++];
			if (tmp->str[i] && flag == is_qoutes(tmp->str[i++]))
				flag = 0;
		}
		stock[j] = '\0';
		free(tmp->str);
		tmp->str = NULL;
		tmp->str = ft_strdup(stock);
		tmp = tmp->next;
	}
}

void free_tokens(t_token **tokens)
{
    t_token *tmp;
    
    while (*tokens)
    {
        tmp = *tokens;
        *tokens = (*tokens)->next;
        free(tmp->str); 
        tmp->str = 0;
        free(tmp);
        tmp = 0;
    }
    tokens = 0;
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        //if (tokens->prev != NULL)
            //printf("\n prev : %s",tokens->prev->str);
        printf("\n--->%s _ type = %u\n", tokens->str , tokens->type);
        tokens = tokens->next;
    }
}

