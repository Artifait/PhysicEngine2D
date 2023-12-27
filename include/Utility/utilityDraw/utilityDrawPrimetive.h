#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <StructData/v2f.h>

#include <StructData/v2fRect.h>

#include <SimulateData.h>

namespace utility
{
    namespace draw
    {
        void DrawVertices(sf::RenderWindow& win, const v2f* vertices, size_t sizeV, const size_t* triangle, 
            size_t sizeT, sf::Color col = sf::Color(120, 120, 120));

        void DrawVerticesLine(sf::RenderWindow& win, const v2f* vertices, size_t sizeV, const size_t* triangle, size_t sizeT,
            sf::Color col = sf::Color(120, 120, 120));

        void DrawVector(sf::RenderWindow& win, const sf::Vector2f& vec, const sf::Vector2f& pos = sf::Vector2f(),
            sf::Color col = sf::Color(120, 120, 120));

        void DrawVector(sf::RenderWindow& win, const v2f& vec, const v2f& pos = v2f(), 
            sf::Color col = sf::Color(120, 120, 120));

        void DrawDirVector(sf::RenderWindow& win, const sf::Vector2f& vec, sf::Color col = sf::Color(120, 120, 120), 
            sf::Color colDir = sf::Color::Red, const sf::Vector2f& pos = sf::Vector2f());

        void DrawDirVector(sf::RenderWindow& win, const v2f& vec, const sf::Vector2f& pos = sf::Vector2f(), 
            sf::Color col = sf::Color(120, 120, 120), sf::Color colDir = sf::Color::Red);

        void DrawPoint(sf::RenderWindow& win, const sf::Vector2f& pos, float r, 
            const sf::Color& col = sf::Color::Red, size_t countPoint = 24);

        void DrawPoint(sf::RenderWindow& win, const v2f& pos, float r, 
            const sf::Color& col = sf::Color::Red, size_t countPoint = 24);

        void DrawVPoint(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Color& col = sf::Color::Red);

        void DrawVPoint(sf::RenderWindow& win, const v2f& pos, const sf::Color& col = sf::Color::Red);

        void DrawCircLine(sf::RenderWindow& win, const sf::Vector2f& pos, float r, 
            const sf::Color& col = sf::Color::Red, size_t countPoint = 24);

        void DrawBox(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Vector2f& size, 
            const sf::Color& col = sf::Color::Red);

        void DrawBox(sf::RenderWindow& win, const v2f& pos, const v2f& size, const sf::Color& col = sf::Color::Red);

        void DrawBox(sf::RenderWindow& win, const sf::FloatRect& rect, const sf::Color& col = sf::Color::Red);

        void DrawBoxLine(sf::RenderWindow& win, const sf::Vector2f& pos, 
            const sf::Vector2f& size, const sf::Color& col = sf::Color::Red);

        void DrawBoxLine(sf::RenderWindow& win, const v2f& pos, const v2f& size, const sf::Color& col = sf::Color::Red);
        void DrawBoxLine(sf::RenderWindow& win, const sf::FloatRect& rect, const sf::Color& col = sf::Color::Red);
        void DrawBoxLine(sf::RenderWindow& win, const v2fRect& rect, const sf::Color& col = sf::Color::Red);
    }

}