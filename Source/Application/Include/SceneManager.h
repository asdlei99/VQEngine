//	DX11Renderer - VDemo | DirectX11 Renderer
//	Copyright(C) 2016  - Volkan Ilbeyli
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.
//
//	Contact: volkanilbeyli@gmail.com

#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Skydome.h"
#include "Settings.h"

#include <vector>
#include <memory>

class Renderer;
class Camera;
class PathManager;
struct Path;

typedef int ShaderID;
struct RenderData;

using std::shared_ptr;

class SceneManager
{

public:
	SceneManager();
	~SceneManager();

	void Initialize(Renderer* renderer, const RenderData* rData, PathManager* pathMan);
	void SetCameraSettings(const Settings::Camera& cameraSettings);
	void Update(float dt);
	void Render();	// todo: const

private:
	void InitializeRoom();
	void InitializeLights();
	void InitializeObjectArrays();

	void UpdateCentralObj(const float dt);

	void RenderLights(const XMMATRIX& view, const XMMATRIX& proj) const;
	void RenderAnimated(const XMMATRIX& view, const XMMATRIX& proj) const;
	void RenderCentralObjects(const XMMATRIX& view, const XMMATRIX& proj); // todo: const

	void SendLightData() const;

private:
	Renderer*			m_pRenderer;
	shared_ptr<Camera>	m_pCamera;
	PathManager*		m_pPathManager; // unused

	// render data
	const RenderData*	m_renderData;
	ShaderID			m_selectedShader;
	bool				m_gammaCorrection;

	// scene variables
	Skydome				m_skydome;
	std::vector<Light>	m_lights;

	struct Room {
		friend class SceneManager;
		GameObject floor;
		GameObject wallL;
		GameObject wallR;
		GameObject wallF;
		GameObject ceiling;
		void Render(Renderer* pRenderer) const;
	} m_room;

	std::vector<GameObject> spheres;
	std::vector<GameObject> cubes;

	GameObject triangle;
	GameObject quad;
	GameObject grid;
	GameObject cylinder;


#ifdef ENABLE_ANIMATION
	// hierarchical model
	AnimatedModel m_model;
#endif

#ifdef ENABLE_VPHYSICS
	// physics simulation
	GameObject				m_anchor1;
	GameObject				m_anchor2;
	GameObject				m_physObj;
	std::vector<GameObject> m_vPhysObj;

	SpringSystem m_springSys;
#endif
};

// junkyard

#ifdef ENABLE_VPHYSICS
void InitializePhysicsObjects();
void UpdateAnchors(float dt);
#endif
#ifdef ENABLE_ANIMATION
void UpdateAnimatedModel(const float dt);
#endif
#define xENABLE_ANIMATION	
#define xENABLE_VPHYSICS
#ifdef ENABLE_ANIMATION
#include "../Animation/Include/AnimatedModel.h"
#endif
#ifdef ENABLE_VPHYSICS
#include "PhysicsEngine.h"
#endif