#if false
#include <EnginePhis2D/createrObject.h>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

enum phis2D::CreaterObject::ObjCreated
{
	Box = 0,
	Circle,
	ObjCreatedCount
};
phis2D::CreaterObject::CreaterObject(AdderBody* adderBody) : adderBody(adderBody)
{
}
void phis2D::CreaterObject::DrawGUI()
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
			mass = "Mass: " + std::to_string(SizeObj.x * SizeObj.y * DensityObj / 1000.f);
			ImGui::Text(mass.c_str());
			ImGui::Text("BoxSetting");
			ImGui::SliderFloat("Width", &SizeObj.x, phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);
			ImGui::SliderFloat("Height", &SizeObj.y, phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);
		}

		else if (typeObj == Circle)
		{
			mass = "Mass: " + std::to_string(RadiusObj * RadiusObj * 3.141592f * DensityObj / 1000.f);
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

void phis2D::CreaterObject::changeState(ObjCreated new_state)
{
	typeObj = new_state;
}
const char* phis2D::CreaterObject::state_mode(ObjCreated state)
{
	const char* states[ObjCreatedCount] = {
		"Editing",
		"Simulating"
	};
	return states[state];
}
#endif