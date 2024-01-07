#pragma once
#include <EnginePhis2D/scenaPhis2D.h>
#include <EnginePhis2D/adderObject.h>
#include <EnginePhis2D/createrObject.h>

#include "Window.h"

enum State
{
    Pause = 0,
    Simulating,

    // keep this last
    StateCount
};
class Application
{
public:
    Application();

    // Called once in main
    void run();
    // Called before stopping execution
    void close();
    // key gets pressed down/released
    void handleEvent(const sf::Event& ev);
    // When button/key is pressed continuosly eg. moving map by dragging
    void handleInputBuffers(const sf::Vector2i& delta_mp);

    // Changes state of the application ex. Editing (MapBuilder) and Simulating (Moving cars, lights etc.)
    void changeState(State new_state);
    // Draws GUI eg. menu bar
    void drawGUI();

private:
    ps::Window window_;
    phis2D::CreaterObject createrObj;
    phis2D::Scena scena;
    phis2D::AdderBody adderBody;
    std::vector<std::string> logs_;
    State app_state_ = Pause;

    // Input buffers
    bool key_buffer_[sf::Keyboard::KeyCount]{ false };
    bool button_buffer_[sf::Mouse::ButtonCount]{ false };

    static Application* AppInstance;

public:
    static Application* GetInstance();
};

