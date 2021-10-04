/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:30 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/04 14:32:14 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_redir(t_script *s, int i, char **path_env)
{
	int	fdin;

	if (s->commands[i].in.flag >= 0)
	{
		fdin = open(s->commands[i].in.name, s->commands[i].in.flag);
		if (fdin == -1)
		{
			ft_putstr_fd(s->commands[i].in.name, 2);
			ft_putendl_fd(": No such file or directory", 2);
			free_cmds_path(s, path_env);
			exit(1);
		}
		else if (fdin != STDIN_FILENO)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
			{
				ft_putendl_fd("Error: dup2 failed", 2);
				close(fdin);
				free_cmds_path(s, path_env);
				exit(1);
			}
		}
	}
	else
		heredoc(s, i, path_env);
}

void	out_redir(t_script *s, int i, char **path_env)
{
	int	fdout;

	fdout = open(s->commands[i].out.name, s->commands[i].out.flag, 0644);
	if (fdout == -1)
	{
		ft_putstr_fd(s->commands[i].in.name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free_cmds_path(s, path_env);
		exit(1);
	}
	else if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			ft_putendl_fd("Error: dup2 failed", 2);
			close(fdout);
			free_cmds_path(s, path_env);
			exit(1);
		}
	}
	close(fdout);
}

void	close_pipes(int *pipe1, int *pipe2)
{
	close(pipe1[0]);
	close(pipe1[1]);
	if (pipe2)
	{
		close(pipe2[0]);
		close(pipe2[1]);
	}
}

int	pipe_dup(int *pipe, int mod, int std)
{
	if (pipe[mod] != std)
	{
		if (dup2(pipe[mod], std) == -1)
		{
			write(2, "Error: dup2 failed\n", 19);
			return (1);
		}
	}
	return (0);
}

void	cmd_builtin(t_script *script, char **path_env, int ret, int i)
{
	char	*tmp;

	if (!ret)
	{
		tmp = script->commands[i].argv[0];
		exec_cmd(path_env, script->commands[i].argv, script->envp);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(": command not found", 2);
		free_cmds_path(script, path_env);
		exit(127);
	}
	else
		handle_builtin(ret, script, i);
}
