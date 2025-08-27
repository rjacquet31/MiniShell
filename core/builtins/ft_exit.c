/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:55:53 by rafael            #+#    #+#             */
/*   Updated: 2025/08/27 13:41:05 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					k;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	k = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			k = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((k == -1 && (ret - 1) > LONG_MAX) || \
		(k == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * k) % 256));
}

void	ft_exit(t_data *shell_data, char **args)
{
	int	ret;
	int	err;

	ret = 0;
	err = 0;
	if (args[1])
	{
		ret = almost_atoi(args[1], &err);
		if (err)
		{
			print_error("exit: ");
			print_error(args[1]);
			print_error(": numeric argument required\n");
			free_all(shell_data, NULL, 2);
		}
	}
	if (args[1] && args[2])
	{
		print_error("exit: too many arguments\n");
		shell_data->exit_code = 1;
		return ;
	}
	if (!args[1])
		free_all(shell_data, NULL, shell_data->exit_code);
	free_all(shell_data, NULL, ret);
}
