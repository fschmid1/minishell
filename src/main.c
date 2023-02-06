#include "../include/minishell.h"

int	g_in_executer;

void	history(t_options *o)
{
	free_tokens(o->tokens);
	free_table(o->tables);
	o->tokens = NULL;
	o->tables = NULL;
	if (o->line)
	{
		if (ft_strlen(o->line))
			add_history(o->line);
		free(o->line);
		o->line = NULL;
	}
	unlink("here_doc");
}

void	shell(t_options *o)
{
		char			*folder;
		int				j;

		g_in_executer = 0;
		folder = get_current_folder(o);
		o->line = readline(folder);
		if (!o->line)
			panic(o, 0);
		free(folder);
		if (lexer(o) == -1)
			return (history(o));
		j = 0;
		// while (o->tokens[j])
		// {
		// 	ft_printf("%s %d\n", o->tokens[j]->value, o->tokens[j]->type);
		// 	j++;
		// }
		if (parser(o) == -1)
			return (history(o));
		// if (o->tables)
		// {
		// 	j = 0;
		// 	while (o->tables[j])
		// 	{
		// 		ft_printf("%s, %s, %s, %s, %i, %i\n", o->tables[j]->cmd->cmd, o->tables[j]->cmd->opt, o->tables[j]->cmd->opt2, o->tables[j]->cmd->args ? o->tables[j]->cmd->args[0] : NULL, o->tables[j]->in, o->tables[j]->out);
		// 		j++;
		// 	}
		// }
		evaluator(o);
		// j = 0;
		// while (o->tables[j])
		// {
		// 		ft_printf("%s, %s, %s, %s, %i, %i\n", o->tables[j]->cmd->cmd, o->tables[j]->cmd->opt, o->tables[j]->cmd->opt2, o->tables[j]->cmd->args ? o->tables[j]->cmd->args[0] : NULL, o->tables[j]->in, o->tables[j]->out);
		// 	j++;
		// }
		executer(o);
		history(o);
}

int	main(void)
{
	t_options		*o;

	o = create_options();
	if (o->is_shell)
		ft_printf("\e[1;1H\e[2J");
	else
		return (ft_putendl_fd("Use a shell, dude!", 2), panic(o, 1), 0);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		shell(o);
	panic(o, 0);
}
