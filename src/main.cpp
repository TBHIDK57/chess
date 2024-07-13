#pragma once
#include "chess.hpp"
#include "../include/Login.hpp"
int main() {
        std::string filename,whitePlayerName,blackPlayerName;
        try{
            LoginSystem system;
            system.Run();
            filename = system.getUsername();
            whitePlayerName = system.getUsername1();
            blackPlayerName = system.getUsername2();
        } catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
        }

        try{
            Game<sf::Texture> game;
            game.setFilename(filename);
            game.setUsernames(whitePlayerName, blackPlayerName);
            game.run();
        } catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
        }
            

    return 0;
}
