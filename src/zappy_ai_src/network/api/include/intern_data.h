/*
** EPITECH PROJECT, 2022
** Project
** File description:
** intern_data
*/

#ifndef INTERN_DATA_H_
    #define INTERN_DATA_H_

    #include "client_utils.h"

/// \brief Wraps the appplication and network sidde of the zappy server
typedef struct zappy_client_s {
    /// The network layer, imported from client_net_utils
    client_net_server_t *net_srv;

    /// Stop a connected client and destroy all associated ressources
    void (*stop)(void);
} zappy_client_t;

/// Pointer to the client network data
extern zappy_client_t *client_data;

/// \brief Stop a connected client and destroy all associated ressources
void stop_zappy_client(void);

#endif /* !INTERN_DATA_H_ */
