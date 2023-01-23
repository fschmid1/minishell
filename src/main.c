
#include "../include/minishell.h"
#include <stdlib.h>

int	main(void)
{
	t_options	*o;
	int		j;

	o = create_options();
	signal(SIGINT, ctrl_c_handler);
	while (1)
	{
		o->line = readline("minishell> ");
		if (!o->line || !ft_strncmp(o->line, "exit", 4))
			panic(o, 0);
		lexer(o);
		j = 0;
		while (o->tokens[j])
		{
			ft_printf("%s %d\n", o->tokens[j]->value, o->tokens[j]->type);
			j++;
		}
		if (o->line && *(o->line))
		{
			add_history(o->line);
			free(o->line);
			o->line = NULL;
		}
	}
	panic(o, 0);
}
