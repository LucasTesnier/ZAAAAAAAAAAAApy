/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include "SFML.hpp"

/// \brief The core of the zappy_gui. It's the most important part of the project.
class Core {
    public:
        Core(int ac, char **av);
        void run();
        ~Core();
    private:
        SFML _sfml;
};

#endif /* !CORE_HPP_ */