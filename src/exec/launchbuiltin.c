/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchbuiltin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:13:01 by rafael            #+#    #+#             */
/*   Updated: 2025/04/09 08:13:01 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_exit_builtin(int save_stdout, t_data *data, t_cmd *cmd)
{
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	ft_exit(data, cmd->cmd_param);
}

static void	exec_builtin(int save_stdout, t_data *data, t_cmd *cmd)
{
	char	*name;

	name = cmd->cmd_param[0];
	if (!name)
		return ;
	if (!ft_strncmp("echo", name, 4) && ft_strlen(name) == 4)
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", name, 2) && ft_strlen(name) == 2)
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (!ft_strncmp("pwd", name, 3) && ft_strlen(name) == 3)
		data->exit_code = ft_pwd();
	else if (!ft_strncmp("export", name, 6) && ft_strlen(name) == 6)
		data->exit_code = ft_export(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("unset", name, 5) && ft_strlen(name) == 5)
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("env", name, 3) && ft_strlen(name) == 3)
		data->exit_code = ft_env(data->env);
	else if (!ft_strncmp("exit", name, 4) && ft_strlen(name) == 4)
		handle_exit_builtin(save_stdout, data, cmd);
}

bool	launch_builtin(t_data *data, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	exec_builtin(save_stdout, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
	return (true);
}
