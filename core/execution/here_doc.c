/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:56:30 by rafael            #+#    #+#             */
/*   Updated: 2025/08/27 13:38:29 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	read_in_stdin(t_data *shell_data, int fd, char *word)
{
	char	*buff;

	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (!buff)
		{
			print_error("warning: here doc delimited by eof ");
			print_error("(wanted '");
			print_error(word);
			print_error("')\n");
			break ;
		}
		if (!ft_strncmp(word, buff, INT_MAX))
			break ;
		if (!replace_dollar(&buff, shell_data))
			free_all(shell_data, ERR_MALLOC, EXT_MALLOC);
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
	close(fd);
	return (true);
}

int	here_doc(t_data *shell_data, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(shell_data, fd, word))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
