/*
** EPITECH PROJECT, 2022
** Project
** File description:
** authentification
*/

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>
#include <unistd.h>

zappy_client_t *client_data = NULL;

/// \brief Init the client_data structure and network info
/// \param host Server adress
/// \param port Port to connect
/// \return true When operation succeed
/// \return false When operation failed
static bool zappy_client_create(const char *host, long port)
{
    client_data = malloc(sizeof(zappy_client_t));

    if (!client_data)
        return false;
    client_data->net_srv = create_net_server(host, port);
    if (!client_data->net_srv)
        return false;
    client_data->stop = stop_zappy_client;
    client_data->net_srv->connected = true;
    return true;
}

bool c_interface_try_to_connect_to_server(char *host, long port)
{
    if (client_data != NULL) {
        dprintf(2, "You are already connected to the server.\n");
        return false;
    }
    if (!zappy_client_create(host, port)) {
        dprintf(2, "Error when initialize the server.\n");
        return false;
    }
    return true;
}

bool c_interface_try_to_disconnect_to_server(void)
{
    if (client_data == NULL) {
        dprintf(2, "You are already disconnected from the server.\n");
        return false;
    }
    client_data->stop();
    return true;
}

void stop_zappy_client(void)
{
    close(client_data->net_srv->sock_fd);
    free(client_data->net_srv);
    free(client_data);
    client_data = NULL;
}