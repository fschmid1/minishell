#include "../include/minishell.h"

void	ft_export(t_options *o, t_parse_cmd *cmd)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (o->env[++i] != NULL)
		env[i] = o->env[i];
	size = 0;
	env[i] = ft_strdup(cmd->args[0]);
	env[i + 1] = NULL;
	free(o->env);
	o->env = env;
	o->last_status = 0;
}

void	ft_cd(t_options *o, t_parse_cmd *cmd)
{
	if (chdir(cmd->args[0]) != 0)
	{
		ft_printf("cd: No such file or directory\n");
		o->last_status = 1;
		return ;
	}
	free(o->pwd);
	o->pwd = get_pwd();
	o->last_status = 0;
}

char *ft_getenv(t_options *o, char *name)
{
	int		i;
	char	*res;
	char	**tmp;
	char	*tmp2;

	i = -1;
	res = NULL;
	while (o->env[++i])
	{
		tmp = ft_split(o->env[i], '=');
		tmp2 = tmp[0];
		if (ft_strncmp(tmp2, name, ft_strlen(tmp2)) == 0)
		{
			res = ft_strdup(tmp[1]);
			split_free(tmp);
			break ;
		}
		split_free(tmp);
	}
	return (res);
}

static int	find_git(void)
{
	int	i;
	int fd;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = ft_strdup(".git/HEAD");
	fd = open(pwd, O_RDONLY);
	while (fd < 2 && i < 20)
	{
		tmp = ft_strjoin("../", pwd);
		free(pwd);
		pwd = tmp;
		fd = open(pwd, O_RDONLY);
		i++;
	}
	free(pwd);
	return (fd);
}

static char	*get_current_branch(void)
{
	char	**tmp;
	char	*res;
	char	*line;
	int		i;
	int		fd;

	fd = find_git();
	if (fd < 2)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	close(fd);
	tmp = ft_split(line, '/');
	free(line);
	i = 0;
	while (tmp[i])
		i++;
	res = ft_strtrim(tmp[i -1], "\n");
	split_free(tmp);
	return (res);
}

char	*get_current_folder(t_options *o)
{
	char	**tmp;
	char	*res;
	char	*color;
	int		i;
	char	*branch;

	tmp = ft_split(o->pwd, '/');
	i = 0;
	while (tmp[i])
		i++;
	if (o->last_status == 0)
		color = "\033[32m";
	else
		color = "\033[31m";
	res = ft_strjoin(color, "➜\033[0m ");
	res = ft_strjoin_gnl(res, tmp[i - 1]);
	split_free(tmp);
	branch = get_current_branch();
	if (branch)
	{
		res = ft_strjoin_gnl(res, " \033[0;35mgit:(");
		res = ft_strjoin_gnl(res, "\033[31m");
		res = replace_join(res, branch);
		res = ft_strjoin_gnl(res, "\033[0;35m)\033[0;0m");
	}

	res = ft_strjoin_gnl(res, " > ");
	return (res);
}