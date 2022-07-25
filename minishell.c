#include "minishell.h"
#include "get_next_line/get_next_line.h"

void    print_free_blocks(char **block)
{
    int i = 0;
    if (!block)
    {
        printf("NULL\n");
        return ;
    }
    while(block[i])
    {
        printf("|%s|\n", block[i]);
        free(block[i]);
        i++;
    }
    free(block);
}
void    print_tab_of_tab(char ***pipe)
{
    int i;

    i = 0;
    while(pipe[i])
    {
        print_free_blocks(pipe[i]);
        printf("\n******************\n");
        i++;
    }
    free(pipe);
}


int *position_key(char *tab, int l, char c)
{
    int *pos;
    int i;
    int j;

    j = 0;
    i = 0;
    pos = malloc(sizeof(int) * l);
    while(tab[i])
    {
        if (tab[i] == c)
        {
            pos[j] = i;
            j++;
        }
        i++;
    }
    return(pos);
}
int check_key(char *tab, int pos, char c)
{
    if (tab[pos + 1] == c)
        return (1);
    pos = pos + 1;
    while(tab[pos])
    {
        if (tab[pos] == '<' || tab[pos] == '>')
            return(0);
        else if (tab[pos] != ' ' && tab[pos] != '\t')
            return (1);
        pos++;
    }
    return(0);
}

int check_triple_key(int *pos, int size)
{
    int i;

    i = 0;
    if (size < 3)
        return(1);
    while(i < size - 2)
    {
        if (pos[i] == pos[i + 1] - 1 && pos[i] == pos[i + 2] - 2)
            return (0);
        i++;
    }
    return (1);
}

int compare_key_error(char *tab, char c)
{
    int *pos;
    int l;
    int i;

    i = 0;
    l = counter(tab, c);
    if (!l)
        return(1);
    pos = position_key(tab, l, c);
    if (!check_triple_key(pos, l))
    {
        free(pos);
        return(0);
    }
    while(i < l)
    {
        if (!check_key(tab, pos[i], c))
        {
            free(pos);
            return(0);
        }
        i++;
    }
    free(pos);
    return (1);
}

int error_block_check(char ***pipe_block)
{
    int i;
    int j;

    i = 0;
    while(pipe_block[i])
    {
        j = 0;
        while(pipe_block[i][j])
        {
            if (pipe_block[i][j][ft_strlen(pipe_block[i][j]) - 1] == '\\')
            {
                printf("parse error near '\\'\n");
                return (0);
            }
            else if (!compare_key_error(pipe_block[i][j], '<'))
            {
                printf("parse error near '<'\n");
                return (0);
            }
            else if (!compare_key_error(pipe_block[i][j], '>'))
            {
                printf("parse error near '>'\n");
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}
void    free_pipe(int **pipe, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        free(pipe[i]);
        i++;
    }
    free(pipe);
}
int **allocate_pipe(int size)
{
    int i;
    int **pipe;

    i = 0;
    pipe = malloc(sizeof(int *) * size);
    while(i < size)
    {
        pipe[i] = malloc(sizeof(int) * 2);
        i++;
    }
    return (pipe);
}

int open_pipe(int **tube, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        if (pipe(tube[i]) == -1)
        {
            free_pipe(tube, size);
            return (0);
        }
        i++;
    }
    return (1);
}
void    close_pipe(int **tube, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        close(tube[i][1]);
        close(tube[i][0]);
        i++;
    }
    free_pipe(tube, size);
}

char *add_char(char *msg, char c)
{
    char *new;
    int i;

    i = 0;
    if (!msg)
    {
        msg = malloc(1);
        *msg = '\0';
    }
    new = malloc(sizeof(char) * (ft_strlen(msg) + 2));
    while(msg[i])
    {
        new[i] = msg[i];
        i++;
    }
    new[i] = c;
    i += 1;
    new[i] = '\0';
    return(new);
}

char *read_from_previous_pipe(int fd)
{
    char *c;
    char *tmp;
    char *buffer;

    buffer = malloc(0);
    c = get_next_line(fd);
    while(c)
    {
        tmp = buffer;
        buffer = ft_strjoin(buffer, c);
        free(tmp);
        free(c);
        c = get_next_line(fd);
    }
    return (buffer);
}

void    read_here_doc(char *limiter, char **buffer)
{
    char *c;
    char *tmp;
    char *cmp;

    cmp = ft_strjoin(limiter, "\n");
    write(1, "heredoc> ", 9);
    c = get_next_line(0);
    if (ft_cmp(c, cmp))
    {
        free(c);
        free(cmp);
        return ;
    }
    while(c)
    {
        tmp = *buffer;
        *buffer = ft_strjoin(*buffer, c);
        free(tmp);
        free(c);
        write(1, "heredoc> ", 9);
        c = get_next_line(0);
        if (ft_cmp(c, cmp))
        {
            free(c);
            free(cmp);
            return ;
        }
    }
}

char *read_open_file(char *file, char *buffer)
{
    int fd;
    char *c;
    char *tmp;

    fd = open(file, O_RDONLY);
    c = get_next_line(fd);
    while(c)
    {
        tmp = buffer;
        buffer = ft_strjoin(buffer, c);
        if (*tmp)
            free(tmp);
        free(c);
        c = get_next_line(fd);
    }
    return(buffer);
}

void    write_append(char *file, char *buffer)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    write(fd, buffer, ft_strlen(buffer));
}

void    write_overwrite(char *file, char *buffer)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, buffer, ft_strlen(buffer));
}

int     ft_cmp(char *s1, char *s2)
{
        int     i;

        i = 0;
        while (s2[i])
        {
                if (s1[i] != s2[i])
                        return (0);
                i++;
        }
        if (!s1[i])
                return (1);
        return (0);
}
char    **cmd_part(char **block)
{
    int i;
    int j;
    int len;
    char **cmd;

    len = 0;
    j = 0;
    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], ">") || ft_cmp(block[i], ">>") || ft_cmp(block[i], "<") || ft_cmp(block[i], "<<"))
            i += 2;
        else
        {
            i++;
            len++;
        }
    }
    cmd = malloc(sizeof(char *) * (len + 1));
    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], ">") || ft_cmp(block[i], ">>") || ft_cmp(block[i], "<") || ft_cmp(block[i], "<<"))
            i += 2;
        else
        {
            cmd[j] = block[i];
            i++;
            j++;
            len++;
        }
    }
    cmd[j] = NULL;
    return (cmd);
}
int	there_is_slash(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	fct_exec(char **path, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (there_is_slash(cmd[0]))
		execve(cmd[0], cmd, NULL);
	else
	{
		while (path[i])
		{
			tmp = ft_strjoin(path[i], cmd[0]);
			if (execve(tmp, cmd, NULL) == -1)
				i++;
			else
				free(tmp);
		}
	}
    write(2, "Commande not found a chabab\n", 29);
	//error message (commande not found)
	exit(22);
}

int check_out(char **block)
{
    int i;

    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], ">") || ft_cmp(block[i], ">>"))
            return (0);
        i++;
    }
    return(1);
}

void    block_execution(char **block, t_data crd, t_env exe) //t_data contains the index and len of the **pipe
{
    int i;
    char *buffer = NULL;
    char **cmd;
    char *tmp;
    int fd;
    int pp[2];

    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], "<"))
        {
            if(access(block[i + 1], R_OK) == -1)
            {
                write(2, "You have no right to access l had wati9a sir f7alk\n", 52);
                // error message (opening file)
                close_pipe(crd.tube, 2 * crd.len + 2);
                exit(11);
            }
        }
        i++;
    }
    if (crd.index)
    {
        close(crd.tube[crd.index][1]);
        buffer = read_from_previous_pipe(crd.tube[crd.index][0]);// reading and buffering
        write(crd.tube[crd.len + 1 + crd.index][1], &buffer, ft_strlen(buffer)); // writting the out of the previous pipe
    }
    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], "<"))
            buffer = read_open_file(block[i+1], buffer);
        else if (ft_cmp(block[i], "<<"))
            read_here_doc(block[i + 1], &buffer);
        i++;
    }
    if (buffer)
    {
        if (crd.index)
        {
            if (pipe(pp) == -1)
                exit(66);
            write(pp[1], &buffer, ft_strlen(buffer));
            dup2(pp[0], 0);
            close(pp[1]);
            close(pp[0]);
        }
        else
        {
            write(crd.tube[crd.index][0], &buffer, ft_strlen(buffer));
            dup2(crd.tube[crd.index][0], 0);
        }
        free(buffer);
    }
    if (crd.index != crd.len)
    {
        printf("hna %d\n", crd.index + 1);
        dup2(crd.tube[crd.index + 1][1], 1);
    }
    else if (crd.index == crd.len && !check_out(block))
        dup2(crd.tube[crd.len + 1 + crd.index][1], 1);
    close_pipe(crd.tube, 2 * crd.len + 2);
    cmd = cmd_part(block);
    fct_exec(exe.path, cmd);
}

void    writing_in_files(char *out, char **block)
{
    int i;

    i = 0;
    while(block[i])
    {
        if (ft_cmp(block[i], ">"))
            write_overwrite(block[i + 1], out);
        else if (ft_cmp(block[i], ">>"))
            write_append(block[i + 1], out);
        i++;
    }
}

char *copier_out_tube(int *tube)
{
    char c;
    int s;
    char *msg;
    char *tmp;

    close(tube[1]);
    while(read(tube[0], &c, 1))
    {
        tmp = msg;
        msg = add_char(msg, c);
        free(tmp);
    }
    close(tube[0]);
    return (msg);
}

int execution(char ***pipe_block, t_env exe)
{
    t_data crd;
    int i;
    int j;
    char **block;
    int pid;
    char *tmp;

    i = 0;
    while(pipe_block[i])
    {
        crd.index = 0;
        crd.len = ft_strlen_tab(pipe_block[i]) - 1;
        crd.tube = allocate_pipe(2 * crd.len + 2);
        if (!open_pipe(crd.tube, 2 * crd.len + 2))
            return (0);
        while(pipe_block[i][crd.index])
        {
            block = last_step_parsing(pipe_block[i][crd.index], exe.var);
            if (!block)
                return (0);
            pid = fork();
            if (pid == -1)
                return (0);
            if (!pid)
                block_execution(block, crd, exe);
            /*wait(NULL);
            printf("hna %d\n", crd.index + 1);
            tmp = read_from_previous_pipe(crd.tube[crd.index + 1][0]);
            printf("#%s#\n", tmp);
            free(tmp);*/
            free_tab(block, ft_strlen_tab(block));
            crd.index++;
        }
        j = 0;
        while(j < crd.index)
        {
            close(crd.tube[j][0]);
            close(crd.tube[j][1]);
            j++;
        }
        while(1)
        {
            if (wait(NULL) == -1)
                break ;
            printf("@\n");
        }
        /*j = 0;
        while(pipe_block[i][j])
        {
            block = last_step_parsing(pipe_block[i][j], exe.var);
            if (!block)
                return (0);
            close(crd.tube[crd.index][1]);
            tmp = read_from_previous_pipe(crd.tube[crd.index][0]);
            //printf("****%s******\n", tmp);
            free(tmp);
            writing_in_files(tmp, block);
            close(crd.tube[crd.index][0]);
            free_tab(block, ft_strlen_tab(block));
            crd.index++;
            j++;
        }*/
        i++;
    }
    return (1);
}
/*
int     quotes_check(char **block)
{
    int i;
    int j;

    i = 0;
    while(block[i])
    {
        j = 0;
        while(block[i][j])
        {
            if (block[i][j] == 34)
            {
                if (counter(block[i][j], 34) % 2)
                    return(0);
                else
                    return(1);
            }
            else if (block[i][j] == 39)
            {
                if (counter(block[i][j], 39) % 2)
                    return(0);
                else
                    return(1);
            }
        }
    }
}

int last_checking(char ***pipe_block, char *env[])
{
    char **block;
    int i;
    int j;

    i = 0;
    while(pipe_block[i])
    {
        j = 0;
        while(pipe_block[i][j])
        {
            block = last_step_parsing(pipe_block[i][j], env);
            if (!quotes_check(block))
            {
                free_tab(block, ft_strlen_tab(block));
                return (0);
            }
            free_tab(block, ft_strlen_tab(block));
            j++;
        }
        i++;
    }
    return(1);
}*/

int	checker_path(char *env, char *path)
{
	int	i;

	i = 0;
	while (env[i] == path[i] && env[i] && path[i])
		i++;
	if (i == ft_strlen(path))
		return (1);
	else
		return (0);
}

int	search_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (checker_path(env[i], "PATH="))
			return (i);
		i++;
	}
	return (-1);
}
char	**the_paths(char *oldenv)
{
	char	*newenv;
	int		i;
	char	**path;

	i = 0;
	newenv = malloc(sizeof(char) * (ft_strlen(oldenv) - 4));
	while (oldenv[i + 5])
	{
		newenv[i] = oldenv[i + 5];
		i++;
	}
	newenv[i] = '\0';
	path = ft_split(newenv, ':');
	free(newenv);
	i = 0;
	while (path[i])
	{
		newenv = path[i];
		path[i] = ft_strjoin(newenv, "/");
		free(newenv);
		i++;
	}
	return (path);
}
int main(int argc, char *argv[], char *env[])
{
    char *in;
    char **block;
    char ***pipe_block;
    t_env exe;
    int i;

    exe.var = env;
    i = search_path(env);
    if (argc != 1 || i == -1)
        return(1);
    exe.path = the_paths(exe.var[i]);
    in = readline("Minishell%% ");
    while(in)
    {
        block = special_split(in, ';');
        if (block)
        {
            
            pipe_block = parsing_by_pipe(block);
            free_tab(block, ft_strlen_tab(block));
            if (pipe_block)
            {
                if (!error_block_check(pipe_block))
                {
                    free_tab_of_tab(pipe_block, ft_strlen_tab_tab(pipe_block));
                    free(pipe_block);
                }
                else
                {
                    //last_checking(pipe_block, env); // to do
                    if (!execution(pipe_block, exe))
                        return (2);
                    
                    free_tab_of_tab(pipe_block, ft_strlen_tab_tab(pipe_block));
                    free(pipe_block);
                }
            }
        }
        free(in);
        in = readline("Minishell%% ");
    }
    return (0);
}