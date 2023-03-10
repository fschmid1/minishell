/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:32 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 13:56:34 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_size(t_token **tokens)
{
	int	size;

	size = 0;
	while (tokens[size])
		size++;
	return (size);
}

t_token	*new_token(char *args, enum e_token_type type)
{
	t_token	*new;

	if (!args || !*args)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = args;
	new->type = type;
	return (new);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		if (tokens[i]->value)
			free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
