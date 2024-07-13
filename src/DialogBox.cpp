#pragma once
#include "chess.hpp"
DialogBox::DialogBox(const std::string& message, const sf::Font& font) {
    window.create(sf::VideoMode(400, 200), "Game Result", sf::Style::Titlebar | sf::Style::Close);

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Center the text in the window
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void DialogBox::show() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}