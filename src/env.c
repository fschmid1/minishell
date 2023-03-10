/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:24 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/10 20:25:08 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_env(t_options *o, char *name, char *value)
{
	int		i;
	char	**env;

	if (!value)
		return ;
	env = malloc(sizeof(char *) * (split_size(o->env) + 2));
	i = -1;
	while (o->env[++i] != NULL)
		env[i] = ft_strdup(o->env[i]);
	env[i] = ft_strjoin_gnl(ft_strjoin(name, "="), value);
	env[i + 1] = NULL;
	split_free(o->env);
	o->env = env;
}

void	remove_env(t_options *o, char *name)
{
	int		i;
	int		j;
	size_t	l;
	char	**env;

	env = malloc(sizeof(char *) * (split_size(o->env) + 1));
	i = -1;
	j = 0;
	while (o->env[++i] != NULL)
	{
		l = ft_strchr(o->env[i], '=') - o->env[i];
		if (ft_strlen(name) > l)
			l = ft_strlen(name);
		if (ft_strncmp(o->env[i], name, l) == 0)
			continue ;
		env[j] = ft_strdup(o->env[i]);
		j++;
	}
	env[j] = NULL;
	split_free(o->env);
	o->env = env;
}
