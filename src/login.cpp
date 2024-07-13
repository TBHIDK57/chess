#pragma once
#include "../include/Login.hpp"
#include <iostream>

bool auth = false;

LoginSystem::LoginSystem() :
    window(sf::VideoMode(800, 600), "Login System"),
    focusedField(1),
    currentScreen(MainMenu) {
    if (!font.loadFromFile("/usr/share/fonts/truetype/hack/Hack-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    signInText.setFont(font);
    signInText.setString("Sign in");
    signInText.setCharacterSize(24);
    signInText.setFillColor(sf::Color::White);
    signInText.setPosition(350, 200);

    signUpText.setFont(font);
    signUpText.setString("Sign up");
    signUpText.setCharacterSize(24);
    signUpText.setFillColor(sf::Color::White);
    signUpText.setPosition(350, 250);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(350, 300);

    username1Text.setFont(font);
    username1Text.setCharacterSize(24);
    username1Text.setPosition(0, 0);

    password1Text.setFont(font);
    password1Text.setCharacterSize(24);
    password1Text.setPosition(0, 50);

    username2Text.setFont(font);
    username2Text.setCharacterSize(24);
    username2Text.setPosition(0, 100);

    password2Text.setFont(font);
    password2Text.setCharacterSize(24);
    password2Text.setPosition(0, 150);

    twoInOneText.setFont(font);
    twoInOneText.setCharacterSize(24);
    twoInOneText.setFillColor(sf::Color::White);
    twoInOneText.setPosition(0, 200);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(200, 200);
}

bool LoginSystem::Run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            HandleKeyboardInput(event);
            if(auth) return true;
            
        }

        window.clear(sf::Color::Black);

        switch (currentScreen) {
            case MainMenu:
                ShowMainMenu();
                break;
            case LoginScreen:
                
                ShowLogin("Login");
                break;
            case RegisterScreen:
                
                ShowLogin("Register");
                break;
        }

        window.display();
    }
    
}

void LoginSystem::ShowMainMenu() {
    signInText.setFillColor(focusedField == 1 ? sf::Color::Red : sf::Color::White);
    signUpText.setFillColor(focusedField == 2 ? sf::Color::Red : sf::Color::White);
    quitText.setFillColor(focusedField == 3 ? sf::Color::Red : sf::Color::White);

    window.draw(signInText);
    window.draw(signUpText);
    window.draw(quitText);
}

void LoginSystem::ShowLogin(const std::string& flag) {

    username1Text.setString("Player 1 Username: " + username1);
    password1Text.setString("Player 1 Password: " + std::string(password1.size(), '*'));
    username2Text.setString("Player 2 Username: " + username2);
    password2Text.setString("Player 2 Password: " + std::string(password2.size(), '*'));
    twoInOneText.setString(flag);

    if (focusedField == 1) {
        username1Text.setFillColor(sf::Color::Red);
    } else {
        username1Text.setFillColor(sf::Color::White);
    }

    if (focusedField == 2) {
        password1Text.setFillColor(sf::Color::Red);
    } else {
        password1Text.setFillColor(sf::Color::White);
    }

    if (focusedField == 3) {
        username2Text.setFillColor(sf::Color::Red);
    } else {
        username2Text.setFillColor(sf::Color::White);
    }

    if (focusedField == 4) {
        password2Text.setFillColor(sf::Color::Red);
    } else {
        password2Text.setFillColor(sf::Color::White);
    }

    if (focusedField == 5) {
        twoInOneText.setFillColor(sf::Color::Red);
    } else {
        twoInOneText.setFillColor(sf::Color::White);
    }

    if (focusedField == 6) {
        backButtonText.setFillColor(sf::Color::Red);
    } else {
        backButtonText.setFillColor(sf::Color::White);
    }

    window.draw(username1Text);
    window.draw(password1Text);
    window.draw(username2Text);
    window.draw(password2Text);
    window.draw(twoInOneText);
    window.draw(backButtonText);
}

void LoginSystem::HandleKeyboardInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            focusedField = (focusedField > 1) ? focusedField - 1 : 
                (currentScreen == MainMenu ? 3 : 6);
        } else if (event.key.code == sf::Keyboard::Down) {
            focusedField = (focusedField < (currentScreen == MainMenu ? 3 : 6)) ? 
                focusedField + 1 : 1;
        } else if (event.key.code == sf::Keyboard::Return) {
            if (currentScreen == MainMenu) {
                if (focusedField == 1) {
                    currentScreen = LoginScreen;
                    focusedField = 1;
                } else if (focusedField == 2) {
                    currentScreen = RegisterScreen;
                    focusedField = 1;
                } else if (focusedField == 3) {
                    window.close();
                }
            } else {
                if (focusedField == 5) {
                    auth = SendDetails(username1, password1, username2, password2, 
                        currentScreen == LoginScreen ? "Login" : "Register");
                    return;

                } else if (focusedField == 6) {
                    currentScreen = MainMenu;
                    focusedField = 1;
                    username1.clear();
                    password1.clear();
                    username2.clear();
                    password2.clear();
                }
            }
        } else if (event.key.code == sf::Keyboard::Backspace) {
            if (currentScreen != MainMenu) {
                if (focusedField == 1 && !username1.empty()) username1.pop_back();
                else if (focusedField == 2 && !password1.empty()) password1.pop_back();
                else if (focusedField == 3 && !username2.empty()) username2.pop_back();
                else if (focusedField == 4 && !password2.empty()) password2.pop_back();
            }
        } else if (event.key.code == sf::Keyboard::Escape) {
            if (currentScreen != MainMenu) {
                currentScreen = MainMenu;
                focusedField = 1;
                username1.clear();
                password1.clear();
                username2.clear();
                password2.clear();
            } else {
                window.close();
            }
        }
    } else if (event.type == sf::Event::TextEntered) {
        if (currentScreen != MainMenu && event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != ' ' && event.text.unicode != '\r') {
            if (focusedField == 1) username1 += static_cast<char>(event.text.unicode);
            else if (focusedField == 2) password1 += static_cast<char>(event.text.unicode);
            else if (focusedField == 3) username2 += static_cast<char>(event.text.unicode);
            else if (focusedField == 4) password2 += static_cast<char>(event.text.unicode);
        }
    }

    // Update text display after each input
    username1Text.setString("Player 1 Username: " + username1);
    password1Text.setString("Player 1 Password: " + std::string(password1.size(), '*'));
    username2Text.setString("Player 2 Username: " + username2);
    password2Text.setString("Player 2 Password: " + std::string(password2.size(), '*'));
}

bool LoginSystem::SendDetails(const std::string& username1, const std::string& password1, 
                              const std::string& username2, const std::string& password2, 
                              const std::string& flag) {
    if (username1.length() < 3 || username2.length() < 3 || username1 == username2) {
        ShowErrorDialog("Enter valid username");
        return false;
    }

    bool result = false;
    std::string errorMessage;

    try {
        if (flag == "Login") {
            result = db.Login(username1, password1, username2, password2);
            if (!result) {
                errorMessage = "Login failed!";
            }
        } else if (flag == "Register") {
            result = db.Register(username1, password1, username2, password2);
            if (!result) {
                errorMessage = "Registration failed.\nUsername may already exist.";
            }
        } else {
            errorMessage = "Invalid operation.";
        }
    } catch (const std::exception& e) {
        errorMessage = "Database error: " + std::string(e.what());
    }

    if (!result) {
        ShowErrorDialog(errorMessage);
    }

    return result;
}

void LoginSystem::ShowErrorDialog(const std::string& message) {
    DialogBox box(message, font);
    box.show();
}
