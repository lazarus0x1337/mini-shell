/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:50:57 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:50:58 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environnement/env.h"
#include "parsing.h"

char	*parse_exec(t_token **tokens, char *executable, int *flag_env,
		int *flag_quote)
{
	char	*exec;

	exec = 0;
	if (!executable)
	{
		*flag_env = (*tokens)->flag_env;
		*flag_quote = (*tokens)->type_qoutes;
		exec = ft_strdup((*tokens)->str);
		consume(tokens);
	}
	if (!exec)
		return (executable);
	return (exec);
}

int	is_special_char(char *c, int *flag_redir)
{
	if (c)
	{
		if (*c == '>' || *c == '<' || *c == '|')
		{
			*flag_redir = 1;
			return (1);
		}
	}
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	isalpha_num(char c)
{
	if (is_alpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
