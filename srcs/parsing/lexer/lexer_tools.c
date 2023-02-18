/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:51 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 16:05:17 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/////////////////////////////// LINKED LIST TOOLS ////////////////////////////////////////

void init_list(t_data *data)
{
    data->tokens = malloc(sizeof(t_tokens));
    if (!data->tokens)
        exit_error(data, 1, "Minishell: Allocation failed.");
    data->tokens->next = NULL;
}

void add_new_node(t_data *data)
{
    t_tokens *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_error(data, 1, "Malloc: Allocation failed.");
    node->next = NULL;
    data->tokens->next = node;
}

void create_new_node(t_data *data, int *add_node)
{
    if (*add_node)
    {
        add_new_node(data);
        data->tokens = data->tokens->next;
    }
    else
        *add_node = 1;
}

void display_list(t_tokens *token)
{
    t_tokens    *head;
    int         n;

    head = token;
    n = 0;
    while (head != NULL)
    {
        printf("---- Node %d ----\n", n);
        printf("Lexeme: %s\n",head->lex);
        printf("Type: %d\n\n", head->type);
        n++;
        head = head->next;
    }
}