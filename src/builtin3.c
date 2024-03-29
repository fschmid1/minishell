/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:21 by fschmid           #+#    #+#             */
/*   Updated: 2023/03/20 11:11:19 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	g_global;

void	ft_cd(t_options *o, t_parse_cmd *cmd)
{
	char	*path;

	if (!cmd->args)
		return ;
	if (!cmd->args[0])
		path = ft_getenv(o, "HOME");
	else
		path = ft_strdup(cmd->args[0]);
	remove_env(o, "OLDPWD");
	add_env(o, "OLDPWD", o->pwd);
	if (chdir(path) != 0)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		g_global.status = 256;
		free(path);
		return ;
	}
	free(path);
	free(o->pwd);
	o->pwd = get_pwd();
	g_global.status = 0;
}

char	*ft_getenv(t_options *o, char *name)
{
	int		i;
	char	*res;
	char	**tmp;
	char	*tmp2;
	int		length;

	i = -1;
	res = NULL;
	while (o->env[++i])
	{
		tmp = ft_split(o->env[i], '=');
		tmp2 = tmp[0];
		if (ft_strlen(tmp2) > ft_strlen(name))
			length = ft_strlen(tmp2);
		else
			length = ft_strlen(name);
		if (tmp[1] && ft_strncmp(tmp2, name, length) == 0)
		{
			res = ft_strdup(tmp[1]);
			split_free(tmp);
			break ;
		}
		split_free(tmp);
	}
	return (res);
}

char	*show_status(void)
{
	char	*color;
	char	*res;

	res = "";
	if (g_global.status == 0)
		color = "\033[32m";
	else
		color = "\033[31m";
	res = ft_strjoin(color, "➜\033[0m ");
	return (res);
}

void	ft_exit(t_options *o, t_parse_cmd *cmd)
{
	int	code;
	int	i;

	code = 0;
	if (cmd->args && cmd->args[0])
	{
		i = -1;
		while (cmd->args[++i])
			if (!ft_isdigit(cmd->args[0][i]))
				panic(o, 255);
		code = ft_atoi(cmd->args[0]);
	}
	panic(o, code);
}

void	print_export_error(t_options *o)
{
	int		i;
	char	**tmp;

	i = -1;
	while (o->env[++i])
	{
		tmp = ft_split(o->env[i], '=');
		ft_printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
		split_free(tmp);
	}
}
