/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:53:05 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/10 15:25:12 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "lexer.h"
# include "parser.h"
# include "evaluator.h"
# include "executer.h"

# ifndef LIBFT_H
#  include "../libft/libft.h"
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_options
{
	char			**env;
	int				is_shell;
	char			*pwd;
	char			*line;
	t_token			**tokens;
	int				last_status;
	t_parse_table	**tables;
	char			**paths;
	int				pipes;
}	t_options;

typedef struct s_replace_options
{
	char	*str;
	char	*old;
	char	*new_value;
	int		start;
	int		end;
}	t_replace_options;

extern int	g_in_executer;

int			get_out_fd(t_parse_table **tables, int i);
void		close_fd(int *fd);
char		*read_first_line(int fd);
int			lexer(t_options *o);
char		**split_join(char **str);
void		split_free(char **str);
char		*strjoinn(char **arr, char *c, int start, int end);
size_t		getnext_whitespace(char *str);
size_t		getafter_option(char *str);
void		ctrl_c_handler(int sig);
int			is_whitespace(char c);
t_options	*create_options(void);
void		free_options(t_options *o);
char		*get_pwd(void);
char		*str_prefix(char *str, char *prefix);
char		*str_replace(t_replace_options options);
char		*replace_join(char *one, char *two);
char		*str_remove_char(char *str, char c);
char		*ft_getenv(t_options *o, char *name);
char		*get_current_folder(t_options *o);
void		add_env(t_options *o, char *name, char *value);
void		remove_env(t_options *o, char *name);
char		**split_first(char *str, char c);
#endif
