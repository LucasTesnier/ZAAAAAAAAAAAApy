/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core
*/

/// \file src/zappy_gui_src/Core/Core.hpp

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include "SFML.hpp"

namespace gui {
    /// \brief The core of the zappy_gui. It's the most important part of the project.
    class Core {
        public:

            /// \brief Constructor of the Core.
            Core() = default;

            /// \brief Destructor of the Core.
            ~Core() = default;

            /// \brief Run the core. It's the main loop of the program.
            void run();

            /// \brief Setup the core with the given parameters.
            void setup(int ac, char **av);
        private:

            /// \brief Get the parameters of the program and set the core with them.
            /// \param ac The number of parameters.
            /// \param av The parameters.
            void _getArgs(int ac, char **av);

            /// \brief The port of the server.
            std::string _port;

            /// \brief The ip of the server.
            std::string _machine;

            /// \brief An instance of the sfml graphical part.
            SFML _sfml;
    };
} // namespace gui

#endif /* !CORE_HPP_ */
