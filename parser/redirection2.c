void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast_redir(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if ((void *)0 == lst)
		return ((void *)0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_redir	*ft_lstnew_redir(void *content, int type)
{
	t_redir	*new_list;

	new_list = (t_redir *)malloc(sizeof(t_redir));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->filename = content;
	new_list->type_redr = type;
	new_list->next = (void *)0;
	return (new_list);
}