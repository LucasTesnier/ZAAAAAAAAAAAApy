/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** GUI
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <SFML/Graphics.hpp>
#include <string>

namespace gui {
class GUI {
   public:
    GUI(size_t width, size_t height);
    ~GUI();
    /// \brief create the window with a name
    void initWindow(std::string const &name = "ZappyGUI");
    /// \brief close the window
    void closeWindow();
    /// \brief clear the screen
    void clearScreen();
    /// \brief display all what as been drawn on the window
    void displayScreen();
    /// \brief display the GUI
    void displayGUI();
   protected:
   private:
    size_t _width;
    size_t _height;
    sf::RenderWindow _window;
};
}  // namespace gui

#endif /* !GUI_HPP_ */
