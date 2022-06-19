/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajid <mnajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:15:09 by mnajid            #+#    #+#             */
/*   Updated: 2022/06/19 17:15:10 by mnajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_redir_list(t_redir *redir)
{
	t_redir	*tmp_list;

	if (redir)
	{
		while (redir)
		{
			tmp_list = redir->next;
			free(redir->filename);
			free(redir);
			redir = tmp_list;
		}
	}	
}

void	clean_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp_list;

	if (cmd_list)
	{
		while (cmd_list)
		{
			tmp_list = cmd_list->next;
			clean_redir_list(cmd_list->redir_in);
			clean_redir_list(cmd_list->redir_out);
			free(cmd_list);
			cmd_list = tmp_list;
		}
	}
	cmd_list = NULL;
}

void	clean_env_list(t_env_list *list)
{
	t_env_list	*temp_list;

	while (list)
	{
		temp_list = list->next;
		free(list->key);
		if (list->equal)
			free(list->val);
		free (list);
		list = temp_list;
	}
}

void	clear_all(t_minishell *shell)
{
	close(shell->stdout);
	close(shell->stdin);
	clean_cmd_list(shell->cmd_list_head);
	clean_env_list(shell->env_list);
	memclean(shell->builtin_names, len_2d_str(shell->builtin_names));
	memclean(shell->env, len_2d_str(shell->env));
}

char	*collect_str_env(t_env_list *elem)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}
