#include "env.h"
#include "../minishell.h"

void util_add(char **key, char **value, int index, char *str)
{
    char *temp;
    int shl;

    ft_strlcpy(*key, str, index + 1);
    ft_strlcpy(*value, str + index + 1, ft_strlen(str) - index);
    if (!ft_strcmp(*key, "SHLVL"))
    {
        shl = my_atoi(*value);
        ft_free(value);
        *value = ft_itoa(shl + 1);
        
    }
} 
void ft_lstadd_back_env(t_env **lst, int index, char *str)
{
    t_env *new;
    t_env *p;

    new = malloc(sizeof(t_env));
    new->key = malloc(sizeof(char) * (index + 1));
    if(!new || !new->key)
        return ;
    new->value = malloc(sizeof(char) * (ft_strlen(str) - index));
    if (!new->value)
	{	    
		free(new->key);
		free(new);
        return ;
	}
    util_add(&new->key, &new->value, index, str);
    new->next = NULL;
    p = *lst;
    if (lst && *lst == NULL)
            *lst = new;
    else
    {
        while (p->next)
            p = p->next;
        p->next = new;
    }
}
static void add_env_first(t_env **env)
{
    char *str;
    char *pwd;

    pwd = getcwd(NULL, 0);
    str = ft_strjoin(pwd, "./minishell", 0);
    set_env_value(env, "SHLVL", "1");
    set_env_value(env, "PWD", pwd);
    set_env_value(env, "_", str);
    free(str);
    free(pwd);
}

void env_copy(t_env **env, char **environ)
{
    int i;
    char * sh;

    i = 0;
    sh = ft_getenv(*env, "SHLVL");
    if (!*environ)
    {
        add_env_first(env);
        return ;
    }
    while (environ[i])
    {
        ft_lstadd_back_env(env, ft_strchr(environ[i], '='), environ[i]);
        i++;
    }
    if (!sh)
        set_env_value(env, "SHLVL", "1");
    else
        free(sh);
}