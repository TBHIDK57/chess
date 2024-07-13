#pragma once
#include "chess.hpp"
#include "../include/Database.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class LoginSystem {
public:
    LoginSystem();
    std::string getUsername() {return (username1+"_"+username2);}
    std::string getUsername1() { return username1; }
    std::string getUsername2() { return username2; }
    bool Run();

private:
    void ShowMainMenu();
    void ShowLogin(const std::string& flag);
    void HandleKeyboardInput(sf::Event event);
    bool SendDetails(const std::string& username1, const std::string& password1, const std::string& username2, const std::string& password2, const std::string& flag);
    void ShowErrorDialog(const std::string& message);
    Database db;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text signInText;
    sf::Text signUpText;
    sf::Text quitText;
    sf::Text username1Text;
    sf::Text password1Text;
    sf::Text username2Text;
    sf::Text password2Text;
    sf::Text twoInOneText;
    sf::Text backButtonText;

    std::string username1;
    std::string password1;
    std::string username2;
    std::string password2;

    int focusedField;
    enum Screen { MainMenu, LoginScreen, RegisterScreen } currentScreen;
};