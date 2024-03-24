#include "builtin.h"

static int util(t_cmd_node *cmd, int index)
{
    int i;

    i = 0;
    if(cmd->arguments[index])
    {
        while (cmd->arguments[index][i])
        {
            if (!isalpha_num(cmd->arguments[index][i]) && cmd->arguments[index][i] != '_')
            {
                ft_putstr_fd("minishell: unset: `", 2);
                ft_putstr_fd(cmd->arguments[index], 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
                return (1);
            }
            i++;
        }
    }
    return (0);
}

static void remove_env(t_env **env, char *key)
{
    t_env *tmp;
    t_env *prev;

    tmp = *env;
    prev = NULL;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
        {
            if (prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int ft_unset(t_env *env, t_cmd_node *cmd)
{
    int i;

    i = 1;
    while (cmd->arguments[i])
    {
        if (util(cmd, i))
            return (1);
        remove_env(&env, cmd->arguments[i]);
        i++;
    }
    return (0);
}