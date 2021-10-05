/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:56:59 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/05 13:24:59 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
	else if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_fork(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
	else if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
	}
}
