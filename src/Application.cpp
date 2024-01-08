#include <Application.h>

#include <memory>
#include <iostream>
#include <string>
#include <utility>
    
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"


Application* Application::AppInstance = nullptr;

Application::Application() : scena(window_.getRenderWindow()), adderBody(&scena, logs_), createrObj(&adderBody)
{
    AppInstance = this;
    window_.setZoom(1.f);
}

void Application::run()
{
    sf::Vector2i delta_mouse_pos = sf::Mouse::getPosition();

    //Main loop
    while (window_.isOpen())
    {
        window_.pollEvent();

        handleInputBuffers(delta_mouse_pos - sf::Mouse::getPosition());
        delta_mouse_pos = sf::Mouse::getPosition();
        scena.Step();
        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        scena.Render(false);
        createrObj.DrawGUI();
        drawGUI();
        window_.display();
    }
}

void Application::changeState(State new_state)
{
    app_state_ = new_state;
    switch (app_state_)
    {
    case Pause:

        break;
    case Simulating:

        break;
    default:
        break;
    }
}

const char* state_mode(State state)
{
    const char* states[StateCount] = {
        "Pause",
        "Simulating"
    };
    return states[state] ;
}

void Application::drawGUI()
{
    ImGui::Begin("Log");
    ImGui::BeginChild("");
    for (unsigned int i = logs_.size(); i > 0; --i)
    {
        ImGui::Text("Log: %s", logs_[i - 1].c_str());
    }
    ImGui::EndChild();
    ImGui::End();
    if (app_state_ == Simulating)
    {

    }
    if (app_state_ == Pause)
    {
    }
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode"))
        {
            for (int i = 0; i < State::StateCount; i++)
            {
                State new_state = static_cast<State>(i);
                if (ImGui::MenuItem(state_mode(new_state), "", app_state_ == new_state))
                    changeState(new_state);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scale"))
        {
            if (ImGui::MenuItem("Scale: 100%", "Ctrl+1", ImGui::GetFont()->Scale == 1.f))
                ImGui::GetFont()->Scale = 1.f;
            if (ImGui::MenuItem("Scale: 125%", "Ctrl+2", ImGui::GetFont()->Scale == 1.25f))
                ImGui::GetFont()->Scale = 1.25f;
            if (ImGui::MenuItem("Scale: 150%", "Ctrl+3", ImGui::GetFont()->Scale == 1.5f))
                ImGui::GetFont()->Scale = 1.5f;
            if (ImGui::MenuItem("Scale: 200%", "Ctrl+4", ImGui::GetFont()->Scale == 2.f))
                ImGui::GetFont()->Scale = 2.f;
            if (ImGui::MenuItem("Scale: 250%", "Ctrl+5", ImGui::GetFont()->Scale == 2.5f))
                ImGui::GetFont()->Scale = 2.5f;
            if (ImGui::MenuItem("Scale: 300%", "Ctrl+6", ImGui::GetFont()->Scale == 3.f))
                ImGui::GetFont()->Scale = 3.f;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}


void Application::handleEvent(const sf::Event& ev)
{
    //builder_.handleInput(ev);
    //statistics_.handleInput(ev);
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        key_buffer_[ev.key.code] = true;
        break;
    case sf::Event::KeyReleased:
        key_buffer_[ev.key.code] = false;
        break;
    case sf::Event::MouseButtonPressed:
        button_buffer_[ev.mouseButton.button] = true;
        break;
    case sf::Event::MouseButtonReleased:
        button_buffer_[ev.mouseButton.button] = false;
        break;
    default:
        break;
    }
    // Shortcuts
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Num1 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.f;
        else if (ev.key.code == sf::Keyboard::Num2 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.25f;
        else if (ev.key.code == sf::Keyboard::Num3 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.5f;
        else if (ev.key.code == sf::Keyboard::Num4 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.f;
        else if (ev.key.code == sf::Keyboard::Num5 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.5f;
        else if (ev.key.code == sf::Keyboard::Num6 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 3.f;

        //else if (ev.key.code == sf::Keyboard::S && key_buffer_[sf::Keyboard::LControl])
        //    data_.saveMap(data_.getCurrentFileName(), map_.grid_);
        //else if (ev.key.code == sf::Keyboard::O && key_buffer_[sf::Keyboard::LControl])
        //{
        //    //data_.loadMap("test.csv", builder_, map_.grid_);
        //}

        else if (ev.key.code == sf::Keyboard::Up && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = { 1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f };
            if (window_.gui_zoom_index < 5)
            {
                window_.gui_zoom_index++;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
        else if (ev.key.code == sf::Keyboard::Down && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = { 1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f };
            if (window_.gui_zoom_index > 0)
            {
                window_.gui_zoom_index--;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
    }
}

void Application::handleInputBuffers(const sf::Vector2i& delta_mp)
{
    // LEFT mouse button is pressed down
    if (button_buffer_[sf::Mouse::Left])
    {
        // store temporarily selected "radio button" option such as "Add Road"

        // if left control is down add a road
        if (key_buffer_[sf::Keyboard::LControl] && app_state_ == Pause)
        {
            //builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), AddRoad);
        }

        // if left shift is down remove road or building
        else if (key_buffer_[sf::Keyboard::LShift] && app_state_ == Pause)
        {
            //builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), Remove);
        }

        // if no control or shift keys pressed move map
        else
        {
            window_.moveView(delta_mp);
        }
    }
}

void Application::close()
{
    ImGui::SFML::Shutdown();
}

Application* Application::GetInstance()
{
    return AppInstance;
}
