/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajid <mnajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:23:17 by mnajid            #+#    #+#             */
/*   Updated: 2022/06/17 18:18:43 by mnajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env_list(int mode, t_env_list *env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_list)
	{
		if (!env_list->equal)
			j++;
		i++;
		env_list = env_list->next;
	}
	if (mode == 1)
		return (i);
	else
		return (i - j);
}

t_env_list	*get_env_elem(char *input)
{
	t_env_list	*elem;

	elem = (t_env_list *)malloc(sizeof(t_env_list));
	elem->equal = 0;
	if (elem == NULL)
		exit_with_error("error: in allocation!");
	elem->key = get_key(input);
	if (elem->key == NULL)
		exit_with_error("error: in allocation!");
	if (ft_strchr(input, '='))
	{
		elem->val = ft_strdup(ft_strchr(input, '=') + 1);
		if (elem->val == NULL)
			exit_with_error("error: in allocation!");
		elem->equal = 1;
	}
	else
		elem->val = NULL;
	elem->next = NULL;
	return (elem);
}

char	**collect_env(t_env_list *env_list)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	len = len_env_list(0, g_shell.env_list);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (env_list->equal)
			env[i] = collect_str_env (env_list);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

void	get_env_list(t_env_list **env_list, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		lst_envadd_back(env_list, get_env_elem(envp[i]));
	}
}

void	ft_init(char **env)
{
	g_shell.fd_read = -10;
	g_shell.fd_write = -10;
	g_shell.stdin = dup(STDIN_FILENO);
	g_shell.stdout = dup(STDOUT_FILENO);
	g_shell.status = 0;
	g_shell.env_list = NULL;
	get_env_list(&g_shell.env_list, env);
	g_shell.env = collect_env(g_shell.env_list);
	set_builtin_funcs(&g_shell);
	set_builtin_names(&g_shell);
}
