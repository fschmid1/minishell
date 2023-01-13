/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:41:41 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/13 09:40:15 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*piped_tokens(char **piped)
{
	int 	i;
	char	**cmd;
	t_token	*tokens;

	i = 0;
	tokens = malloc(sizeof(t_token));
	while (piped[i])
	{
		cmd = ft_split(piped[i], ' ');
		tokens[i] = new_token(cmd);
		i++;
	}
	return (tokens);
}

t_token	*parse_input(char *line)
{
	char	**cmd;
	t_token	*tokens;

	if (!line)
		return (NULL);
	//if (has_qute(line))

	if (ft_strchr(line, '|'))
		return (piped_tokens(ft_split(line, '|')));
	cmd = ft_split(line, ' ');
	tokens = malloc(sizeof(t_token));
	tokens[0] = new_token(cmd);
	return (tokens);
}
