#include "builtin.h"

int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}   




size_t my_atoi(const char *str) {
    size_t res;
    int sign;
    size_t tmp;

    res = 0;
    sign = 1;
    while (ft_isspace(*str))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        tmp = res * 10 + (*str - '0');
        // Check for overflow/underflow
        if (sign == 1 && tmp > LONG_MAX) {
            return LONG_MAX;
        }
        if (sign == -1 && -tmp < LONG_MIN) {
            return LONG_MIN;
        }
        res = tmp;
        str++;
    }
    return sign * res;
}

int ft_error_exit(char *arg, int flag)
{
    ft_putstr_fd("minishell: exit: ", 2);
   
    if(flag)
    { 
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        return (255);
    }
    else
    {
        ft_putstr_fd(": too many arguments\n", 2);
        return (1);
    }

}
void ft_exit(t_cmd_node *cmd, t_env *env)
{
    int i;
    size_t j;

    i = 0;
    j = 0;
    free_env_list(env);
    if(count_len(cmd->arguments) == 1 )
    {
        //  !cmd for handle signal 
        ft_putstr_fd("exit\n", 2);

        // check grobal variable for exit code
        system("leaks minishell");
        exit(EXIT_CODE);
    }
    if (cmd->arguments[1])
    {
        while (cmd->arguments[1][i])
        {
            if (!ft_isdigit(cmd->arguments[1][i]) && cmd->arguments[1][i] != '-')
                exit(ft_error_exit(cmd->arguments[1], 1));
            i++;
        }
        if (cmd->arguments[2])
        {
            ft_error_exit(cmd->arguments[1], 0);
            return ;
        }
        j = my_atoi(cmd->arguments[1]);
        if ((j < 0 && cmd->arguments[1][i] != '-') || (j > 0 && cmd->arguments[1][i] == '-') || j == 9223372036854775807)
            exit(ft_error_exit(cmd->arguments[1], 1));
        EXIT_CODE = j % 256;
        exit(EXIT_CODE);
    }
}