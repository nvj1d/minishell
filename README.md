
##  the structre of variables:  
this is the sructure of our shell wich will be our only global variable:  
```c
typedef struct s_minishell  
{  
	int				stdin; //fd input 
	int				stdout; //fd output  
	char			**env; //2D envirement array  
	int				status; /* the status */   
	int				env_changed;  
	void			*temp;  
	int				**fds;  
	int				fd_write; //fd to write to   
	int				fd_read; //fd to read from  
	char			**builtin_names; //the names of our funcs  
	void			(*builtin_funcs[7])(void); // array of our funcs  
	pid_t			*pids;  
	t_env_list		*env_list;  
	struct s_cmd	*cmd_list;  
	struct s_cmd	*cmd_list_head;  
}  			t_minishell;  
```
the declaration of the variable (in the header) will be like this:  
```c
t_minishell g_shell;  
```	
the envirement strcture will be like this:  
```c 
typedef struct s_env_list  
{
	char				*key; //the identifier of the env variable  
	char				*val; //the value -- key:val  
	int					equal;  
	struct s_env_list	*next; //the next env variable  
}				t_env_list;  
```
and this is the structure of our command:  
```c
typedef struct s_cmd
{
	char			**args; //the arguments of the command
	int				pipe_in;
	int				pipe_out;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next; // the next one 
}				t_cmd;
```

## in the main :  
int the main function we have three arguments 
 ```c
int main(int ac, char **av,char **env)
```
the number of arguments (ac) the input from the terminal (av) and the (env) wich is a 2D array    with the envirement variable  

we have the command that we gonna get  
```c
char	*cmd;
```
we won't use the av  
```c
(void)av;
```
then we gonna check the number of arguments:  
```c
if (ac != 1)
	{
		print_error(av[1], "No such file or directory");
		return (127);
	}
```
if it's not **one** we will display an error **""no such file or directory""** and return a value of **127** which means that the command is not found in the **path** system variable  

then we call **ft_head()** that gonna clear the screen with the string **"\e[1;1H\e[2J"** the **"
\e"** is escape and what that printf() line is telling the terminal to move the cursor to line 1 column 1 **"\e[1;1H"** and to move all the text currently in the terminal to the scrollback buffer **"\e[2J"** then display an **ASCII text banner** if it's the first time  

after that we call **ft_init(env)**:  

## init the g_shell:

```c
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

```
this function goal is to initiate the shell's variables  
the read and write fds:  
```c
	g_shell.fd_read = -10;
	g_shell.fd_write = -10;

```
the fds of input and output:
```c
	g_shell.stdin = dup(STDIN_FILENO);
	g_shell.stdout = dup(STDOUT_FILENO);
```

the status of the shell:  
```c
	g_shell.status = 0;
```
the evirement list with **NULL**
```c
	g_shell.env_list = NULL;
```
getting the envirement variables from **env** to **g_shell.env_list**
```c
	get_env_list(&g_shell.env_list, env);
```
getting the envirement list into a 2D array variable:
```c
	g_shell.env = collect_env(g_shell.env_list);
```
getting the builtins functions into the **void			(*builtin_funcs[7])(void);**
```c
	set_builtin_funcs(&g_shell);
```
getting the builtins functions names into the **char			**builtin_names;**
```c
	set_builtin_names(&g_shell);
```

### get_env_list(t_env_list **env_list, char **envp)
```c
void	get_env_list(t_env_list **env_list, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		lst_envadd_back(env_list, get_env_elem(envp[i]));
	}
}
```
this functions takes the address of the env **linked list** and the **env** of the system as arguments  
then it gets every variable in the **env** using the **get_env_elem(envp[i])** function and add him in the back of to this list
### t_env_list	*get_env_elem(char *input)
```c
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
```
in the structure of the linked list we have three variables the **equal**,the **key**, and the **val**.
we initialise equal with 0  
and we get the key using the **get_key(input);** function  
then we get the value after **'='** after getting this value succefully we set the equal value to 1  

### char	*get_key(char *var)
```c
char	*get_key(char *var)
{
	int	i;

	i = 0;
	if (!ft_strchr(var, '='))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}
```
the **get_key** fucntion takes a string as an argument if it has **'='** then return the caracters before him if not then return all the string  
 
### void	lst_envadd_back(t_env_list **list, t_env_list *new)
```c
void	lst_envadd_back(t_env_list **list, t_env_list *new)
{
	t_env_list	*tmp;

	if (list)
	{
		if (*list)
		{
			tmp = lst_envlast(*list);
			tmp->next = new;
		}
		else
		{
			*list = new;
		}
	}
}

```
this functions takes two arguments the address of the linked list and the element we get 
if the linked list is not empty we get the last element in this list then his next gonna be our new element if not we simply affect the new element to the list  


to return the last element of this linked list we use this function:
```c
t_env_list	*lst_envlast(t_env_list *lst)
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

```
### char	**collect_env(t_env_list *env_list)
```c
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
```
this fuction purpose is to extract a 2D array from the liked list created previously 
we get the length of the list using **len_env_list(0, g_shell.env_list);**
we allocate an array with a length of **len + 1**
then for every element in this list we get the pair **key:value** if **equal == 1**
using the fuction **collect_str_env (env_list);**  

#### int	len_env_list(int mode, t_env_list *env_list)
```c
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
```
#### char	*collect_str_env(t_env_list *elem)
```c
char	*collect_str_env(t_env_list *elem)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}

```

## builtins:
### void	set_builtin_names(t_minishell *shell)
```c
void	set_builtin_names(t_minishell *shell)
{
	char	*all_builtins;

	all_builtins = ft_strdup("cd env echo exit export pwd unset");
	if (all_builtins == NULL)
		exit_with_error("minishell: malloc error");
	shell->builtin_names = ft_split(all_builtins, ' ');
	free(all_builtins);
	if (shell->builtin_names == NULL)
		exit_with_error("minishell: malloc error");
}
```
there is **7** builtins functions which are **cd,env,echo,exit,export,pwd and unset**  
in the **set_builtins names** we set there names  
and in **set_builtins_functs** we store those functions 

### void	set_builtin_funcs(t_minishell *shell)
```c
void	set_builtin_funcs(t_minishell *shell)
{
	shell->builtin_funcs[0] = change_dir;
	shell->builtin_funcs[1] = env;
	shell->builtin_funcs[2] = echo;
	shell->builtin_funcs[3] = ft_exit;
	shell->builtin_funcs[4] = export;
	shell->builtin_funcs[5] = pwd;
	shell->builtin_funcs[6] = unset;
}
```
//ad builtins here!
