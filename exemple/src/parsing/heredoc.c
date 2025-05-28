/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:40:16 by alama             #+#    #+#             */
/*   Updated: 2025/01/20 16:51:28 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*trim_heredoc(char *node)
{
	char	*str;
	int		last;

	str = NULL;
	if (node == NULL)
		return (NULL);
	last = ft_strlen(node) - 1;
	while (node[last] == ' ')
		last--;
	if (node[0] == '\"' && node[last] == '\"')
		str = ft_strtrim(node, "\"");
	else if (node[0] == '\'' && node[last] == '\'')
		str = ft_strtrim(node, "\'");
	else
		str = ft_strdup(node);
	return (str);
}

void	gnl_heredoc(char *delimiter, int fd)
{
	char	*str;

	child_signals();
	str = NULL;
	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
			break ;
		if (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	exit(g_excode);
}

static int	create_heredoc_file(char **lexeme, char **doc)
{
	int		fd;
	char	*trim;

	trim = trim_heredoc(*lexeme);
	*doc = ft_strjoin(".", trim);
	if (!(*doc))
		return (-1);
	fd = open(*doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open heredoc fails\n");
		free(*doc);
		return (-1);
	}
	free(*lexeme);
	*lexeme = trim;
	return (fd);
}

void	heredoc_parse(t_token **token)
{
	t_token	*tmp;
	int		fd;
	int		status;
	char	*doc;
	int		pid;

	doc = NULL;
	tmp = (*token)->next;
	while (tmp->type == SPACE_TOKEN)
		tmp = tmp->next;
	fd = create_heredoc_file(&tmp->lexeme, &doc);
	if (fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
		gnl_heredoc(tmp->lexeme, fd);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
	free(tmp->lexeme);
	tmp->lexeme = doc;
	initialize_signals();
}
