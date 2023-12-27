#include <EnginePhis2D/worldPhis2D.h>

namespace phis2D
{
    World2D::World2D() : gravity{0, 9.8f}
    {
        srand(time(NULL));
        for (int i = 0; i < 35; i++)
        {
            string outMsg;
            cld::VirtualCollider* newColl = nullptr;
            utility::randCollider::GenerateRandCollider(v2f(rand() % 1000 , rand() % 1000), outMsg, newColl);
            if (newColl != nullptr)
                AddColliderBady(newColl, false, 2, 10, 1, outMsg);
            std::cout << outMsg;
        }
    }

    void World2D::Render(RenderWindow& win)
    {
        for (auto& c : BadyInWorld)
            utility::draw::DrawCollider(win, c->ICollider, false, false);
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
        //moving step
        for (int i = 0; i < BadyInWorld.size(); i++)
            BadyInWorld[i]->Step(DT);
        
        //Collision step
        for (int i = 0; i < BadyInWorld.size() - 1; i++)
        {
            cld::VirtualCollider* colliderA = BadyInWorld[i]->ICollider;
            for (int j = i + 1; j < BadyInWorld.size(); j++)
            {
                cld::VirtualCollider* colliderB = BadyInWorld[j]->ICollider;
                v2f normal;
                float depth;
                if (phis2D::Collision::IntersectColliders(
                    colliderA, colliderB, normal, depth))
                {
                    colliderA->Move(-normal * depth * 0.5f);
                    colliderB->Move(normal * depth * 0.5f);
                    Collision::ResolverCollision(BadyInWorld[i], BadyInWorld[j], normal, depth);
                }
            }
        }
    }
    size_t World2D::AddBoxBady(const v2f& position, const v2f& size, bool isStatic, float density, float mass, float restition, std::string& outMessage)
    {
        std::string outMsg;
        BaseBady2D* badyOut;
        if (BaseBady2D::CreateBoxBady(position, size, isStatic, density, mass, restition, badyOut, outMsg))
        {
            BadyInWorld.emplace_back(badyOut);
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
            BadyInWorld.emplace_back(badyOut);
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
            BadyInWorld.emplace_back(badyOut);
            outMessage = "[AddBoxBady](Added){ Bse Norm. }\n";
            return badyOut->id;
        }
        outMessage = "[AddBoxBady](error 'CreateColliderBady'){\n\t" + outMsg + "}\n";
        return 0;
    }
}