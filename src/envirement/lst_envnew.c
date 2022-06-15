#include "../minishell.h"

t_env_list	*lst_envnew(char *key, char *val)
{
	t_env_list	*new_list;

	new_list = (t_env_list *)malloc(sizeof(t_env_list));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->key = key;
	new_list->val = val;
	if (val)
		new_list->equal = 1;
	else
		new_list->equal = 0;
	new_list->next = (void *)0;
	return (new_list);
}
