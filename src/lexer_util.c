/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:50 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 08:13:23 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_len(char *str)
{
	int	end;
	int	i;

	end = 1;
	i = 0;
	if (str[i] == '\'')
		while (str[end] && (str[end] != '\'' || (str[end] == '\''
					&& str[end - 1] == '\\')))
			end++;
	else if (str[0] == '\"')
		while (str[end] && (str[end] != '\"' || (str[end] == '\"'
					&& str[end - 1] == '\\')))
			end++;
	else
		return (0);
	if (str[end] != '\"' && str[end] != '\'')
		return (0);
	return (end);
}

int	quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == ' ')
		return (0);
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	single_quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == ' ')
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	is_word(char *str, int end)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && i < end)
	{
		if (str[i] == '\\' && str[i + 1] != '\0' && (i + 1) < end
			&& ft_strchr("%=+’”()$/_-.\?*~\"", str[i + 1]))
		{
			++i;
			continue ;
		}
		if (ft_isalnum(str[i]) || ft_strchr("_$.{}[]~/!@=?+-\"\'", str[i])
			|| (str[i] == ' ' && quote_count(str) % 2 == 0)
			|| (str[i] == ' ' && single_quote_count(str) % 2 == 0))
			continue ;
		return (0);
	}
	return (1);
}
