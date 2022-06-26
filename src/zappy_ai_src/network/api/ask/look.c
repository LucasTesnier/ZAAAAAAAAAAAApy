/*
** EPITECH PROJECT, 2022
** Project
** File description:
** look
*/

/// \file src/zappy_ai_src/network/api/ask/look.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_ask_look(void)
{
    if (client_data == NULL || client_data->net_srv->pending_write
    || !c_interface_get_network_state())
        return false;
    return send_request("look", NULL);
}