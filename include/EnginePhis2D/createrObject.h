#pragma once
#include <EnginePhis2D/adderObject.h>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
namespace phis2D
{
	class CreaterObject
	{
	public:
		CreaterObject(AdderBody* adderBody) : adderBody(adderBody)
		{

		}
		~CreaterObject() = default;
		enum ObjCreated
		{
			Box = 0,
			Circle,
			ObjCreatedCount
		};

		void DrawGUI()
		{
			if (ImGui::Begin("CreaterObject"))
			{
				ImGui::SliderFloat("Density", &DensityObj, phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity);
				ImGui::SliderFloat("Restitution", &RestitutionObj, 0.f, 1.f);
				if (ImGui::Button("Change Box"))
					changeState(Box);
				if (ImGui::Button("Change Circle"))
					changeState(Circle);
				ImGui::Checkbox("Dynamic", &StaticObj);
				std::string mass;
				if (typeObj == Box)
				{
					mass = "Mass: " + std::to_string(SizeObj.x * SizeObj.y * DensityObj / 10.f);
					ImGui::Text(mass.c_str());
					ImGui::Text("BoxSetting");
					ImGui::SliderFloat("Width", &SizeObj.x, phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);
					ImGui::SliderFloat("Height", &SizeObj.y, phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);
				}

				else if (typeObj == Circle)
				{
					mass = "Mass: " + std::to_string(RadiusObj * RadiusObj * 3.141592f * DensityObj / 10.f);
					ImGui::Text(mass.c_str());
					ImGui::Text("CircleSetting");
					ImGui::SliderFloat("Radius", &RadiusObj, phis2D::worldPhysicConstant::minRadius, phis2D::worldPhysicConstant::maxRadius);
				}

				if (ImGui::Button("Create"))
				{
					if (typeObj == Circle)
					{
						adderBody->AddCircle(v2f(0, 0), RadiusObj, DensityObj, RestitutionObj, !StaticObj);
					}
					else if (typeObj == Box)
					{
						adderBody->AddBox(v2f(0, 0), SizeObj, DensityObj, RestitutionObj, !StaticObj);
					}
				}
			}
			ImGui::End();
		}

		void changeState(ObjCreated new_state)
		{
			typeObj = new_state;
		}

	public:
		static const char* state_mode(ObjCreated state)
		{
			const char* states[ObjCreatedCount] = {
				"Editing",
				"Simulating"
			};
			return states[state];
		}
	private:
		AdderBody* adderBody;
		float DensityObj = worldPhysicConstant::MinDensity;
		bool StaticObj = false;
		float RestitutionObj = 1.f;
		v2f SizeObj = v2f(worldPhysicConstant::minSide, worldPhysicConstant::minSide);;
		float RadiusObj = worldPhysicConstant::minRadius;
		ObjCreated typeObj = (ObjCreated)0;
	};

}