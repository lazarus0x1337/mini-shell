/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:54:53 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:54:54 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(t_node_type type, int len, char *str)
{
	if (type == PIPE)
		return (1);
	if (type == REDIR)
	{
		if (len == 2)
			return (4);
		if (str[0] == '>')
			return (2);
		else
			return (3);
	}
	return (0);
}

void	printf_error_syntax(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("`\n", 2);
}

int	handle_type(int type1, int type2, char *str)
{
	if (type2 == type1)
	{
		printf_error_syntax(str);
		return (1);
	}
	else if (type2 != 1)
	{
		printf_error_syntax(str);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *tok)
{
	int	type1;
	int	type2;

	while (tok)
	{
		type1 = is_operator(tok->type, tok->len, tok->str);
		if ((type1 && !tok->next) || (type1 == 1 && !tok->prev))
		{
			printf_error_syntax(tok->str);
			return (1);
		}
		if (tok->prev)
			type2 = is_operator(tok->prev->type, tok->prev->len,
					tok->prev->str);
		if (tok->prev && type1 && type2)
		{
			if (handle_type(type1, type2, tok->str))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}
