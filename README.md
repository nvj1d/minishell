# minishell

### the structre of variables:  
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

### in the main :  
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














































































































































