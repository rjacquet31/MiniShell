/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:32:33 by rafael            #+#    #+#             */
/*   Updated: 2025/04/08 10:32:33 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		return (true);
	return (false);
}
