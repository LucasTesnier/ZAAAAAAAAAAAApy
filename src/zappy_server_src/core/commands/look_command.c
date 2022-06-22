/*
** EPITECH PROJECT, 2022
** Project
** File description:
** look_command
*/

/// \file src/zappy_server_src/core/commands/look_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

bool command_look(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/look", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Get all the ressources in a tile and format it
/// \param tile The concerned tile
/// \param cases The tile ressources
/// \param res The result
static void get_tile_content_entities(tile_t *tile,
container_t *cases, char *res)
{
    int player_number = 0;
    int egg_number = 0;
    entity_t *tmp;

    for (unsigned int i = 0; i < cases->phiras; i++)
        strcat(res, "phiras ");
    for (unsigned int i = 0; i < cases->thystame; i++)
        strcat(res, "thystame ");
    TAILQ_FOREACH(tmp, &tile->entities, entities) {
        if (tmp->type == ENTITY_PLAYER_TYPE)
            player_number++;
        if (tmp->type == ENTITY_EGG_TYPE)
            egg_number++;
    }
    for (int i = 0; i < player_number - 1; i++)
        strcat(res, "player ");
    for (int i = 0; i < egg_number; i++)
        strcat(res, "egg ");
}

/// \brief Get all the ressources in a tile and format it
/// \param tile The concerned tile
/// \return The result
static char *get_tile_content(tile_t *tile)
{
    container_t *cases = tile->inventory;
    char *res = malloc(sizeof(char) * 10000);

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 0; i < cases->food; i++)
        strcat(res, "food ");
    for (unsigned int i = 0; i < cases->linemate; i++)
        strcat(res, "linemate ");
    for (unsigned int i = 0; i < cases->deraumere; i++)
        strcat(res, "deraumere ");
    for (unsigned int i = 0; i < cases->sibur; i++)
        strcat(res, "sibur ");
    for (unsigned int i = 0; i < cases->mendiane; i++)
        strcat(res, "mendiane ");
    get_tile_content_entities(tile, cases, res);
    res[strlen(res) - 1] = '\0';
    return res;
}

/// \brief Hold the look process
/// \param serv The serv informations
/// \param level The player level
/// \param position The player position
/// \param map The size of the map
/// \return char* The formated look result
static char *look_action(server_data_t *serv, player_t *player,
position_t position, position_t map)
{
    char *res = malloc(sizeof(char) * 4);
    char *temp = NULL;
    position_t *looked = compute_look_cmd(position, map,
    player->level, player->orientation);

    if (res == NULL || looked == NULL)
        return NULL;
    res[0] = '[';
    res[1] = '\0';
    for (int i = 0; looked[i].x != -1; i++) {
        temp = get_tile_content(
        (tile_t *)get_tile(serv->map, looked[i].x, looked[i].y)->data);
        res = realloc(res, sizeof(char) * (strlen(res) + strlen(temp) + 3));
        strcat(res, temp);
        free(temp);
        strcat(res, ",");
    }
    strcat(res, "]");
    free(looked);
    return res;
}

bool command_look_end(char *arg, player_list_t *player,
server_data_t *serv __attribute__((unused)))
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    char *res = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    res = look_action(serv, player_data, player_entity->position,
    (position_t) {serv->map->width, serv->map->height});
    pop_message(player->player_peer);
    print_retcode(215, res, player->player_peer, true);
    free(res);
    return true;
}
