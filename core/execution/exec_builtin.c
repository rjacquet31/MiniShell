/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:56:38 by rafael            #+#    #+#             */
/*   Updated: 2025/08/27 13:34:55 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	run_builtin_command(int out, t_data *data, t_cmd *cmd)
{
	char	*commande;

	commande = cmd->cmd_param[0];
	if (!ft_strncmp("echo", commande, INT_MAX))
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", commande, INT_MAX))
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (!ft_strncmp("pwd", commande, INT_MAX))
		data->exit_code = ft_pwd();
	else if (!ft_strncmp("export", commande, INT_MAX))
		data->exit_code = ft_export(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("unset", commande, INT_MAX))
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("env", commande, INT_MAX))
		data->exit_code = ft_env(data->env);
	else if (!ft_strncmp("exit", commande, INT_MAX))
	{
		if (cmd->outfile >= 0)
		{
			dup2(out, 1);
			close(out);
		}
		ft_exit(data, cmd->cmd_param);
	}
}

bool	launch_builtin(t_data *data, t_cmd *cmd)
{
	int	out;

	out = -1;
	if (cmd->outfile >= 0)
	{
		out = dup(1);
		dup2(cmd->outfile, 1);
	}
	run_builtin_command(out, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(out, 1);
		close(out);
	}
	return (true);
}
