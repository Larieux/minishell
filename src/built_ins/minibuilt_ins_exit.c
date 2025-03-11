/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:33:43 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 16:19:39 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit_no_arg(t_minist *minis)
{
	printf("exit\n");
	free_minist();
	free(minis);
	exit(EXIT_SUCCESS);
}

void	handle_exit_with_code(t_minist *minis, long code)
{
	printf("exit\n");
	code %= 256;
	if (code < 0)
		code += 256;
	free_minist();
	free(minis);
	exit(code);
}

void	handle_exit_non_num(t_minist *minis, char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd(P_AQUA"minishell: "P_ORANGE"exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n"RESET, 2);
	free_minist();
	free(minis);
	exit(2);
}

void	handle_exit_too_many_arg(t_minist *minis)
{
	set_error(minis->err, ERR_UNKNOWN, "exit: too many arguments");
	show_error(minis->err);
	minis->exit_code = 2;
	free_minist();
	free(minis);
	exit(EXIT_FAILURE);
}

bool	ft_exit(t_minist *minis, char **str)
{
	int	i;
	int	n;
	int	err;

	i = 0;
	n = 0;
	err = 0;
	while (str && *str && *(str + i))
		i++;
	if (i == 1)
		return (handle_exit_no_arg(minis), true);
	if (is_num_ok(*(str + 1)))
	{
		n = ft_atol_protecc(*(str + 1), &err);
		if (err == 1)
			return (handle_exit_non_num(minis, *(str + 1)), false);
		if (i == 2)
			return (handle_exit_with_code(minis, n), false);
		return (handle_exit_too_many_arg(minis), false);
	}
	return (handle_exit_non_num(minis, *(str + 1)), false);
}
