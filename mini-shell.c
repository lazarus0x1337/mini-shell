#include "minishell.h"
#include "execution/execute.h"


// optimize lstadd_back
int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    t_env *env_list;

    tokens = NULL;
    env_copy(&env_list, env);

    while(1)
    {
        input = readline(YELLOW"➜ sh-mini ✗ "NC);
        if (!input)
            exit(0);
        if (ft_strlen(input) > 0)
            add_history(input);
        else 
            continue;
        //clear_history();

        SplitTokens(input, &tokens);
        tokenisation(&tokens,input);
	    handling_qoutes(&tokens);
        //print_tokens(tokens);

       
        //printf("\n\n\n");
        t_tree_node *tree = parse_command(&tokens, env_list);
        if (tree)
        {
            if (tree->type == REDIR || tree->type ==CMD)
                execute_simple(tree, env_list);
            else
                execute(tree, env_list);
        }
        // printf("%d",execute_tree(tree, env_list));
        
       if (ft_strncmp(input, "exit", 5) == 0)
            break;
        free_tokens(&tokens);
        free(input);
    }
}



// for environement :

//t_env *env_list;
//env_copy(&env_list, env);
//print_env(env_list, input); if have cmd == env



// this part of tree is not implemented yet
        // print_tokens(tokens);

        // t_token *tmp;
        // tmp = tokens;
        // t_token *righttokens;
        // righttokens = NULL;
        // while (tokens)
        // {
        //     if (tokens->type == PIPE)
        //     {
        //         righttokens = tokens->next;
        //         tokens->prev->next = NULL;
        //         break;
        //     }
        //     tokens = tokens->next;
        // }
        // printf("\n\n\n left : ");
        // print_tokens(tmp);
        // printf("\n\n\n right : ");
        // print_tokens(righttokens);
        //ft_clear(input);
