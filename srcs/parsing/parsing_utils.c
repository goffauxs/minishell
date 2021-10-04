/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:54:29 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/04 14:59:50 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_filenames_null(t_command *commands, int max, t_token *head)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		commands[i].in.name = NULL;
		commands[i].out.name = NULL;
	}
	while (head)
	{
		head->content = remove_quotes(head->content);
		head = head->next;
	}
}

char	*ft_trim_quotes(char *str)
{
	char	*ret;
	char	c;
	int		newlen;

	c = str[0];
	newlen = ft_strlen(str) - 1;
	if (c == '\'' || c == '\"')
	{
		ret = malloc(sizeof(char) * newlen);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, (str + 1), newlen);
	}
	else
		ret = ft_strdup(str);
	return (ret);
}

static int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_cmd_count(char *line_buf)
{
	int		i;
	int		count;
	char	**split_str;

	if (!line_buf)
		return (0);
	count = 0;
	split_str = ft_split(line_buf, '|');
	i = 0;
	while (split_str[i])
	{
		if (check_spaces(split_str[i]))
			count++;
		i++;
	}
	while (i-- > 0)
		free(split_str[i]);
	free(split_str);
	return (count);
}

void	get_num_args(t_token *head, t_script *script)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < script->cmd_count)
	{
		script->commands[i].argc = 0;
		tmp = head;
		while (head && head->type != TOKEN_PIPE)
		{
			if (head->type == TOKEN_NAME && (tmp->type != TOKEN_REDIR_IN
					&& tmp->type != TOKEN_REDIR_OUT))
				script->commands[i].argc++;
			tmp = head;
			head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
}