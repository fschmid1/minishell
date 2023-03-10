/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:48 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 14:00:56 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*get_quoted(char *str)
{
	int		end;

	end = 1;
	if (str[0] == '\'')
		while (str[end] && (str[end] != '\'' || (str[end] == '\''
					&& str[end - 1] == '\\')))
			end++;
	else if (str[0] == '\"')
		while (str[end] && (str[end] != '\"' || (str[end] == '\"'
					&& str[end - 1] == '\\')))
			end++;
	else
		return (NULL);
	if (str[end] != '\"' && str[end] != '\'')
		return (NULL);
	while (!is_whitespace(str[end]) && str[end])
		end++;
	return (new_token(ft_substr(str, 0, end), WORD));
}

t_token	*get_option(char *str)
{
	if (ft_strchr(str, '='))
		return (new_token(ft_substr(str, 0, getafter_option(str)), OPTION2));
	return (new_token(ft_substr(str, 0, getafter_option(str)), OPTION));
}

t_token	*get_io(char *str)
{
	if (ft_strchr("<>#", str[0]))
	{
		if (str[1] == str[0])
			return (new_token(ft_substr(str, 0, 2), IO));
		else
			return (new_token(ft_substr(str, 0, 1), IO));
	}
	return (NULL);
}

t_token	*get_pipe(char *str)
{
	if (str[0] == '|')
		return (new_token(ft_substr(str, 0, 1), PIPE));
	return (NULL);
}
