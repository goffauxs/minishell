/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:50:02 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/04 17:01:43 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **envp)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, MAX_PATH_LEN);
	if (!buff)
	{
		free(buff);
		buff = get_env_content("PWD", envp);
		ft_putendl_fd(buff, 1);
	}
	else
		ft_putendl_fd(buff, 1);
	free(buff);
	return (0);
}
