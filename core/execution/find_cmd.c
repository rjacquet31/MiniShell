/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:56:26 by rafael            #+#    #+#             */
/*   Updated: 2025/08/27 13:38:08 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strslashjoin(char *dest, char *str, char *env, int *k)
{
	int			i;
	int			j;

	i = 0;
	while (*k < (PATH_MAX - 1) && env[(*k)] && env[(*k)] != ':')
		dest[i++] = env[(*k)++];
	++(*k);
	dest[i++] = '/';
	j = 0;
	while (j < (PATH_MAX - 1) && str[j])
		dest[i++] = str[j++];
	dest[i] = '\0';
	return (0);
}

static char	*create_paths(t_env *env, int len)
{
	t_env	*temp;

	temp = env;
	while (len--)
	{
		if (ft_strncmp(temp->str, "PATH=", 5) == 0)
			return (&(temp->str[5]));
		temp = temp->next;
	}
	return (NULL);
}

static char	*cmd_not_found(char *sentence)
{
	write(2, sentence, ft_strlen(sentence));
	write(2, " : command not found\n", 21);
	return (NULL);
}

char	*find_cmd(t_data *shell_data, char *sentence, t_env *env)
{
	char		*paths;
	char		path[PATH_MAX];
	int			i;
	int			len;

	paths = create_paths(env, len_list(env));
	if (!paths || ft_strlen(sentence) > PATH_MAX / 2)
		return (cmd_not_found(sentence));
	i = 0;
	len = ft_strlen(paths);
	while (i < len)
	{
		ft_strslashjoin(path, sentence, paths, &i);
		if (access(path, F_OK) == 0)
		{
			sentence = ft_strdup(path);
			if (!sentence)
			{
				print_error(ERR_MALLOC);
				shell_data->exit_code = -1;
			}
			return (sentence);
		}
	}
	return (cmd_not_found(sentence));
}
