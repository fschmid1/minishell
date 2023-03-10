/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:53:02 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 08:13:20 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# ifndef LIBFT_H
#  include "../libft/libft.h"
# endif

enum	e_token_type
{
	IO,
	PIPE,
	OPTION,
	OPTION2,
	WORD,
	VARIABLE
};

typedef struct s_token
{
	char				*value;
	enum e_token_type	type;
}	t_token;

t_token		*new_token(char *args, enum e_token_type type);
void		free_tokens(t_token **tokens);
int			token_size(t_token **tokens);

t_token		*get_quoted(char *str);
t_token		*get_option(char *str);
t_token		*get_io(char *str);
t_token		*get_pipe(char *str);

int			is_word(char *str, int end);
int			quote_len(char *str);
int			quote_count(char *str);
int			single_quote_count(char *str);

#endif
