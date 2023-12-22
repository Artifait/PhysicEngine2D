#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <v2f.h>
#include <SimulateData.h>

namespace utility
{
    namespace draw
    {
        void DrawVector(sf::RenderWindow& win, const sf::Vector2f& vec, const sf::Vector2f& pos = sf::Vector2f(), sf::Color col = sf::Color(120, 120, 120))
        {
            sf::VertexArray liDraw(sf::Lines, 2);
            liDraw[0].color = col;
            liDraw[1].color = col;
            liDraw[0].position = pos;
            liDraw[1].position = pos + vec;
            win.draw(liDraw);
        }
        void DrawVector(sf::RenderWindow& win, const v2f& vec, const v2f& pos = v2f(), sf::Color col = sf::Color(120, 120, 120))
        {
            sf::VertexArray liDraw(sf::Lines, 2);
            liDraw[0].color = col;
            liDraw[1].color = col;
            liDraw[0].position = pos;
            liDraw[1].position = pos + vec;
            win.draw(liDraw);
        }
        void DrawDirVector(sf::RenderWindow& win, const sf::Vector2f& vec, sf::Color col = sf::Color(120, 120, 120), sf::Color colDir = sf::Color::Red, const sf::Vector2f& pos = sf::Vector2f())
        {
            float angl = phis2D::ToRadian(45.f);
            sf::Vector2f norm = v2f::Normalize(vec);
            sf::VertexArray liDraw(sf::Lines, 2);
            liDraw[1].position = pos;
            liDraw[0].position = pos + vec;
            liDraw[0].color = liDraw[1].color = col;
            win.draw(liDraw);
            liDraw[0].color = liDraw[1].color = colDir;

            liDraw[1].position = liDraw[0].position - sf::Vector2f(v2f::RotateVector(norm, angl) * 17.f);
            win.draw(liDraw);
            liDraw[1].position = liDraw[0].position - sf::Vector2f(v2f::RotateVector(norm, -angl) * 17.f);
            win.draw(liDraw);
        }
        void DrawDirVector(sf::RenderWindow& win, const v2f& vec, const sf::Vector2f& pos = sf::Vector2f(), sf::Color col = sf::Color(120, 120, 120), sf::Color colDir = sf::Color::Red)
        {
            float angl = phis2D::ToRadian(45.f);
            sf::Vector2f norm = vec.getNormalized();
            sf::VertexArray liDraw(sf::Lines, 2);
            liDraw[1].position = pos;
            liDraw[0].position = vec + pos;
            liDraw[0].color = liDraw[1].color = col;
            win.draw(liDraw);
            liDraw[0].color = liDraw[1].color = colDir;

            liDraw[1].position = liDraw[0].position - sf::Vector2f(v2f::RotateVector(norm, angl) * 17.f);
            win.draw(liDraw);
            liDraw[1].position = liDraw[0].position - sf::Vector2f(v2f::RotateVector(norm, -angl) * 17.f);
            win.draw(liDraw);
        }
        void DrawPoint(sf::RenderWindow& win, const sf::Vector2f& pos, float r, const sf::Color& col = sf::Color::Red, size_t countPoint = 24)
        {
            sf::VertexArray circ(sf::TriangleFan, countPoint + 1);
            float offsetAngl = phis2D::ToRadian(360.f / (countPoint - 1));
            float anglNow = 0.f;
            circ[0].position = pos;
            circ[0].color = col;
            for (int i = 1; i < countPoint; i++)
            {
                circ[i].position = sf::Vector2f(cos(anglNow) * r, sin(anglNow) * r) + pos;
                circ[i].color = col;
                anglNow += offsetAngl;
            }
            circ[countPoint] = circ[1];
            win.draw(circ);
        };
        void DrawPoint(sf::RenderWindow& win, const v2f& pos, float r, const sf::Color& col = sf::Color::Red, size_t countPoint = 24)
        {
            sf::VertexArray circ(sf::TriangleFan, countPoint + 1);
            float offsetAngl = phis2D::ToRadian(360.f / (countPoint - 1));
            float anglNow = 0.f;
            circ[0].position = pos;
            circ[0].color = col;
            for (int i = 1; i < countPoint; i++)
            {
                circ[i].position = v2f(cos(anglNow) * r, sin(anglNow) * r) + pos;
                circ[i].color = col;
                anglNow += offsetAngl;
            }
            circ[countPoint] = circ[1];
            win.draw(circ);
        };
        void DrawVPoint(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray p(sf::Points, 1);
            p[0] = sf::Vertex(pos, col);
            win.draw(p);
        }
        void DrawVPoint(sf::RenderWindow& win, const v2f& pos, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray p(sf::Points, 1);
            p[0] = sf::Vertex(pos, col);
            win.draw(p);
        }
        void DrawCircLine(sf::RenderWindow& win, const sf::Vector2f& pos, float r, const sf::Color& col = sf::Color::Red, size_t countPoint = 24)
        {
            sf::VertexArray circ(sf::LineStrip, countPoint + 1);
            float offsetAngl = phis2D::ToRadian(360.f / (countPoint));
            float anglNow = 0.f;

            for (int i = 0; i < countPoint; i++)
            {
                circ[i].position = sf::Vector2f(cos(anglNow) * r, sin(anglNow) * r) + pos;
                circ[i].color = col;
                anglNow += offsetAngl;
            }
            circ[countPoint] = circ[0];
            win.draw(circ);
        }

        void DrawBox(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray box(sf::Quads, 4);
            box[0] = box[1] = box[2] = box[3] = sf::Vertex(pos, col);
            box[1].position.x += size.x;
            box[3].position.y += size.y;
            box[2].position += size;
            win.draw(box);
        }

        void DrawBox(sf::RenderWindow& win, const v2f& pos, const v2f& size, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray box(sf::Quads, 4);
            box[0] = box[1] = box[2] = box[3] = sf::Vertex(pos, col);
            box[1].position.x += size.x;
            box[3].position.y += size.y;
            box[2].position += sf::Vector2f(size.x, size.y);
            win.draw(box);
        }
        void DrawBox(sf::RenderWindow& win, const sf::FloatRect& rect, const sf::Color& col = sf::Color::Red)
        {
            DrawBox(win, rect.getPosition(), rect.getSize(), col);
        }

        void DrawBoxLine(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray box(sf::LinesStrip, 5);
            box[0] = box[1] = box[2] = box[3] = sf::Vertex(pos, col);
            box[1].position.x += size.x;
            box[3].position.y += size.y;
            box[2].position += size;
            box[4] = box[0];
            win.draw(box);
        }

        void DrawBoxLine(sf::RenderWindow& win, const v2f& pos, const v2f& size, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray box(sf::LinesStrip, 5);
            box[0] = box[1] = box[2] = box[3] = sf::Vertex(pos, col);
            box[1].position.x += size.x;
            box[3].position.y += size.y;
            box[2].position += sf::Vector2f(size.x, size.y);
            box[4] = box[0];
            win.draw(box);
        }
        void DrawBoxLine(sf::RenderWindow& win, const sf::FloatRect& rect, const sf::Color& col = sf::Color::Red)
        {
            sf::VertexArray box(sf::LinesStrip, 5);
            box[0] = box[1] = box[2] = box[3] = sf::Vertex(rect.getPosition(), col);
            box[1].position.x += rect.width;
            box[3].position.y += rect.top;
            box[2].position += rect.getSize();
            box[4] = box[0];
            win.draw(box);
        }
    }

}