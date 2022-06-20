/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Map.cpp

#include "Map.hpp"

using namespace gui;

Map::Map()
{
    _tileSelected = -1;
    _tileHover = -1;
    _mapSize = {10, 10};
    _zoom = 1;
}

void Map::_updateTileVectorSize()
{
    while (_mapSize.x * _mapSize.y < _tile.size())
        _tile.pop_back();
    while (_mapSize.x * _mapSize.y > _tile.size()) {
        _tile.push_back(std::make_unique<Tile>());
        _tile.back()->setPosition(sf::Vector2f((_tile.size() - 1) % (int)_mapSize.x, (_tile.size() - 1) / (int)_mapSize.x));
        _tile.back()->setSize(sf::Vector2f(100, 100));
        if (_tile.size() == 1)
            _tile.back()->setTexture("assets/season1_ground1.png");
        else
            _tile.back()->setTexture(_tile[0]->getTexture());
    }
    _pushEntityInTile();
}

void Map::_updateMoveMap()
{
    int value = 10;
    sf::Vector2f moveMap = {0, 0};

    if (_event->isKeyPressed(sf::Keyboard::Z))
        moveMap.y = value;
    if (_event->isKeyPressed(sf::Keyboard::Q))
        moveMap.x = value;
    if (_event->isKeyPressed(sf::Keyboard::S))
        moveMap.y = -value;
    if (_event->isKeyPressed(sf::Keyboard::D))
        moveMap.x = -value;
    for (auto &it : _tile) {
        if (moveMap.x || moveMap.y)
            it->setOrigin(it->getOrigin() + moveMap);
    }
}

bool Map::_tileMustBeDisplayed(const sf::FloatRect &area, const sf::Vector2u windowSize, std::size_t &tmp, sf::Vector2f &mapSize, std::size_t &i)
{
    if (area.left > windowSize.x && area.top > windowSize.y)
        return false;
    if (area.left < 0 && area.top > windowSize.y)
        return false;
    if (area.left + area.width < 0)
        return false;
    if (area.left > windowSize.x && tmp) {
        i = tmp + mapSize.x - 2;
        tmp = 0;
        return false;
    }
    if (area.top + area.height < 0)
        return false;
    if (area.top > windowSize.y && tmp) {
        i = tmp + mapSize.x - 2;
        tmp = 0;
        return false;
    }
    return true;
}

void Map::display()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*_window.get());
    sf::FloatRect area;
    std::size_t tmp = 0;
    sf::CircleShape _playerRepresentation;

    _playerRepresentation.setFillColor(sf::Color::Green);
    _playerRepresentation.setRadius(10);
    _updateMoveMap();
    for (std::size_t i = 0; i < _tile.size(); i++) {
        area = _tile[i]->getGlobalBound();
        if (!_tileMustBeDisplayed(area, _window->getSize(), tmp, _mapSize, i))
            continue;
        if (i % (int)_mapSize.x == 0)
            tmp = i + 1;
        if (tmp == 0)
            tmp = i;
        if (_tile[i]->isOnTile(mouse)) {
            _tileHover = i;
            if (_event->isButtonPressed()) {
                _tileSelected = i;
            }
        }
        _tile[i]->setColor(sf::Color(255, 255, 255));
        _window->draw(_tile[i]->getShape());
        if (_tile[i]->getPlayers().size()) {
            _playerRepresentation.setPosition({_tile[i]->getGlobalBound().left + _tile[i]->getGlobalBound().width, _tile[i]->getGlobalBound().top});
            _window->draw(_playerRepresentation);
        }
    }
    if (_tileSelected < _mapSize.x * _mapSize.y) {
        _tile[_tileSelected]->setColor(sf::Color(100, 100, 100, 100));
        _window->draw(_tile[_tileSelected]->getShape());
    }
    if (_tileHover < _mapSize.x * _mapSize.y) {
        _tile[_tileHover]->setColor(sf::Color(200, 200, 200, 200));
        _window->draw(_tile[_tileHover]->getShape());
    }
}

void Map::_pushEntityInTile()
{
    for (auto &it : _players) {
        _tile[itop(sf::Vector2f(it.getPosition().first, it.getPosition().second))]->addPlayer(it);
    }
}

Map::~Map()
{

}
