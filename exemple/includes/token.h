/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:26 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 17:12:26 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "mini_shell.h"

typedef enum s_token_type
{
	END_TOKEN = 0,
	CHAR_TOKEN = 1,
	SPACE_TOKEN = 2,
	PAREN_TOKEN = 3,
	SINGLE_QUOTE = 4,
	DOUBLE_QUOTE = 5,
	PIPE = 6,
	O_DIR = 7,
	I_DIR = 8,
	OA_DIR = 9,
	DI_DIR = 10,
	DOLLAR = 11
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*lexeme;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef enum e_node_type
{
	PAIR_NODE = 0,
	STR_NODE = 1
}						t_node_type;

typedef struct s_node	t_node;

typedef struct s_pair_value
{
	t_node				*left;
	t_node				*right;
	char				*opera;
	char				*heredoc;
}						t_pair_value;

typedef union u_node_value
{
	t_pair_value		pair;
	char				*str;
}						t_node_value;

typedef struct s_ctxt
{
	int					infile;
	int					outfile;
	int					end[2];
	int					is_first_o;
	int					is_first_i;
}						t_ctxt;

struct					s_node
{
	t_node_type			type;
	t_node_value		data;
};

typedef struct s_all
{
	t_node				*node;
	t_token				*token_list;
	char				*str;
	int					is_child;
	int					boucle;
}						t_all;

#endif
