#include <EnginePhis2D/worldPhis2D.h>

namespace phis2D
{
    World2D::World2D(sf::RenderWindow& window) : gravity{ 0, 400.f }, win{window}
    {
        sf::FloatRect ramkaWindow = GetRamkaWindow();
        srand(time(NULL));
        std::string outMsg;
        cld::VirtualCollider* zemla = new cld::BoxCollider(v2f(500, 900), v2f(800, 100));
        AddColliderBady(zemla, true, 1, 2, 0.75f, outMsg);
        cout << outMsg;

        for (int i = 0; i < 1; i++)
        {

            AddRandomBady();
        }
        GetBadyByIndex(1, player);

    }
    FloatRect phis2D::World2D::GetRamkaWindow()
    {
        if(ramkaUpdateRequired)
            ramkaWindow = sf::FloatRect(win.getViewport(win.getView()));
        ramkaUpdateRequired = false;
        return ramkaWindow;
    }
    void World2D::Render(bool debug)
    {
        
        for (int i = 0; i < BadyInWorld.size(); i++)
            utility::draw::DrawBady(win, BadyInWorld[i], false, debug, debug, BadyInWorld[i]->isStatic ? sf::Color::Red : outlineColors[i]);
        
    }

    void phis2D::World2D::HandleEvent(float DT)
    {
        MsCoord = win.mapPixelToCoords(sf::Mouse::getPosition(win));
        float ForceMagnitude = 48.f;
        //input step
        v2f offset;
        if (Keyboard::isKeyPressed(Keyboard::A))
            offset.x += -300;
        if (Keyboard::isKeyPressed(Keyboard::D))
            offset.x += 300;
        if (Keyboard::isKeyPressed(Keyboard::W))
            offset.y += -300;
        if (Keyboard::isKeyPressed(Keyboard::S))
            offset.y += 300;

        if (Keyboard::isKeyPressed(Keyboard::Left))
            player->Rotate(-phis2D::PI * DT * 2.f);

        if (Keyboard::isKeyPressed(Keyboard::Right))
            player->Rotate(phis2D::PI * DT * 2.f);
        player->ApplyForce(offset * ForceMagnitude);

        if (Mouse::isButtonPressed(sf::Mouse::Left) && !pressLeft)
        {
            AddRandomBady(MsCoord, true);
            pressLeft = true;
        }
        if (!Mouse::isButtonPressed(sf::Mouse::Left))
            pressLeft = false;
        if (Mouse::isButtonPressed(sf::Mouse::Right) && !pressRight)
        {
            AddRandomBady(MsCoord, false);
            pressRight = true;
        }
        if (!Mouse::isButtonPressed(sf::Mouse::Right))
            pressRight = false;
    }
    void phis2D::World2D::WrapSpaceObj(const sf::FloatRect& ramka, cld::VirtualCollider* coll)
    {
        if (coll->CenterPosition.x < ramka.left) coll->Move(v2f(ramka.width, 0));
        if(coll->CenterPosition.x > ramka.left + ramka.width) coll->Move(v2f(-ramka.width, 0));

        if (coll->CenterPosition.y < ramka.top) coll->Move(v2f(0, ramka.height));
        if (coll->CenterPosition.y > ramka.top + ramka.height) coll->Move(v2f(0, -ramka.height));
    }
    //заверкта экрана по x и y
    void phis2D::World2D::WrapScreen()
    {
        sf::FloatRect bounderyWindow = GetRamkaWindow();
        for (int i = 0; i < BadyInWorld.size(); i++)
        {
            cld::VirtualCollider* collB = BadyInWorld[i]->ICollider;
            WrapSpaceObj(bounderyWindow, collB);
        }
    }
    bool phis2D::World2D::IsEmptyWorld()
    {
        return BadyInWorld.empty();
    }
    void phis2D::World2D::RemoveByIdBady(size_t id)
    {
        for (int i = 0; i < BadyInWorld.size(); i++)
            if (BadyInWorld[i]->id == id) {
                BadyInWorld.erase(BadyInWorld.begin() + i);
                return;
            }
    }
    bool phis2D::World2D::GetBadyById(size_t id, BaseBady2D*& outBady)
    {
        outBady = nullptr;
        for (int i = 0; i < BadyInWorld.size(); i++)
            if (BadyInWorld[i]->id == id) {
                outBady = BadyInWorld[i];
                return true;
            }
        return false;
    }
    bool phis2D::World2D::GetBadyByIndex(size_t index, BaseBady2D*& outBady)
    {
        outBady = nullptr;
        if (index < 0 || index >= BadyInWorld.size()) return false;
        outBady = BadyInWorld[index];
        return true;
       
    }
    const BaseBady2D* const& phis2D::World2D::GetBadyInPos(v2f position)
    {
        if (BadyInWorld.empty())
            return nullptr;
        return BadyInWorld[0];
    }

    void World2D::Step(float DT)
    {
        sf::FloatRect ramkaWindow = sf::FloatRect(win.getViewport(win.getView()));
        collider::BoxCollider ramka(ramkaWindow.getPosition(), ramkaWindow.getSize());
        //moving step
       
        for (int i = 0; i < BadyInWorld.size(); i++)
        {
            if(!BadyInWorld[i]->isStatic)
            {
                BadyInWorld[i]->Step(DT, gravity);
                WrapSpaceObj(ramkaWindow, BadyInWorld[i]->ICollider);
            }
        }
        
        //Collision step
        for (int i = 0; i < BadyInWorld.size() - 1; i++)
        {
            cld::VirtualCollider* colliderA = BadyInWorld[i]->ICollider;
            bool staticA = BadyInWorld[i]->isStatic;
            for (int j = i + 1; j < BadyInWorld.size(); j++)
            {
                cld::VirtualCollider* colliderB = BadyInWorld[j]->ICollider;
                bool staticB = BadyInWorld[j]->isStatic;
                if (staticA && staticB) continue;
                v2f normal;
                float depth;
                if (phis2D::Collision::IntersectColliders(
                    colliderA, colliderB, normal, depth))
                {
                    if (staticA)
                        colliderB->Move(normal * depth);
                    else if (staticB)
                        colliderA->Move(-normal * depth);
                    else
                    {
                        colliderA->Move(-normal * depth * 0.5f);
                        colliderB->Move(normal * depth * 0.5f);
                    }

                    Collision::ResolverCollision(BadyInWorld[i], BadyInWorld[j], normal, depth);
                }
            }
        }
    }
    size_t phis2D::World2D::AddRandomBady(bool isStatic)
    {
        string outMsg;
        cld::VirtualCollider* newColl = nullptr;
        sf::FloatRect bounderyWindow = GetRamkaWindow();

        utility::randCollider::GenerateRandCollider(v2f(
            utility::randNumber::getRandomNumber(bounderyWindow.left, bounderyWindow.left + bounderyWindow.width),
            utility::randNumber::getRandomNumber(bounderyWindow.top, bounderyWindow.top + bounderyWindow.height)),
            2.f, outMsg, newColl);
        size_t idRet = 0;
        if (newColl != nullptr)
        {
            idRet = AddColliderBady(newColl, isStatic, 2, 0.01f, 1, outMsg);
        }
        std::cout << outMsg;
        return idRet;
    }
    size_t phis2D::World2D::AddRandomBady(const v2f& Pos, bool isStatic)
    {
        string outMsg;
        cld::VirtualCollider* newColl = nullptr;
        sf::FloatRect bounderyWindow = GetRamkaWindow();

        utility::randCollider::GenerateRandCollider(Pos, 2.f, outMsg, newColl);
        size_t idRet = 0;
        if (newColl != nullptr)
        {
            idRet = AddColliderBady(newColl, isStatic, 2, 0.01f, 1, outMsg);
        }
        std::cout << outMsg;
        return idRet;
    }
    size_t World2D::AddBoxBady(const v2f& position, const v2f& size, bool isStatic, float density, float mass, float restition, std::string& outMessage)
    {
        std::string outMsg;
        BaseBady2D* badyOut;
        if (BaseBady2D::CreateBoxBady(position, size, isStatic, density, mass, restition, badyOut, outMsg))
        {
            BadyInWorld.push_back(badyOut);
            outMessage = "[AddBoxBady](Added){ Bse Norm. }\n";
            return badyOut->id;
        }
        outMessage = "[AddBoxBady](error 'CreateBoxBady'){\n\t" + outMsg + "}\n";
        return 0;
    }

    size_t World2D::AddCircleBady(const v2f& posCenter, float r, bool isStatic, float density, float mass, float restition, std::string& outMessage)
    {
        std::string outMsg;
        BaseBady2D* badyOut;
        if (BaseBady2D::CreateCircleBady(posCenter, r, isStatic, density, mass, restition, badyOut, outMsg))
        {
            BadyInWorld.push_back(badyOut);
            outMessage = "[AddBoxBady](Added){ Bse Norm. }\n";
            return badyOut->id;
        }
        outMessage = "[AddBoxBady](error 'CreateCircleBady'){\n\t" + outMsg + "}\n";
        return 0;
    }

    size_t World2D::AddColliderBady(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, std::string& outMessage)
    {
        std::string outMsg;
        BaseBady2D* badyOut;
        if (BaseBady2D::CreateColliderBady(collider, isStatic, density, mass, restition, badyOut, outMsg))
        {
            BadyInWorld.push_back(badyOut);
            outlineColors.push_back(utility::getRandomColor());
            outMessage = "[AddBoxBady](Added){ Bse Norm.Id: " + std::to_string(badyOut->id) + " }\n";
            return badyOut->id;
        }
        outMessage = "[AddBoxBady](error 'CreateColliderBady'){\n\t" + outMsg + "}\n";
        return 0;
    }
    phis2D::World2D::~World2D()
    {
        for(auto& o : BadyInWorld)
            delete o;

    }
}