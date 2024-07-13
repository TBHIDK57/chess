class DialogBox {
public:
    DialogBox(const std::string& message, const sf::Font& font);
    void show();

private:
    sf::RenderWindow window;
    sf::Text text;
};