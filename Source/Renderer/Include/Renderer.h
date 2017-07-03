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

#include <windows.h>
#include "GeometryGenerator.h"
#include "Shader.h"
#include "Texture.h"
//#include <string>
//#include <vector>

#include "Mesh.h"
#include "GameObject.h"

#include <memory>

// forward declarations
class D3DManager;
struct ID3D11Device;
struct ID3D11DeviceContext;

class BufferObject;
class Camera;
class Shader;

namespace DirectX { class ScratchImage; }

// typedefs
typedef int ShaderID;
typedef int BufferID;
typedef int TextureID;
typedef int RasterizerStateID;
typedef ID3D11RasterizerState RasterizerState;

enum RASTERIZER_STATE
{
	CULL_NONE = 0,
	CULL_FRONT,
	CULL_BACK,

	RS_COUNT
};

enum class TOPOLOGY
{
	POINT_LIST = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	TRIANGLE_LIST = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	LINE_LIST = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,

	TOPOLOGY_COUNT
};


struct DepthPass
{
	unsigned				m_shadowMapDimension;
	Texture					m_shadowMap;
	const Shader*			m_shadowShader;
	ID3D11RasterizerState*	m_drawRenderState;
	ID3D11RasterizerState*	m_shadowRenderState;
	D3D11_VIEWPORT			m_shadowViewport;
	void Initialize(Renderer* pRenderer, ID3D11Device* device);
};

struct RenderData
{
	ShaderID phongShader;
	ShaderID unlitShader;
	ShaderID texCoordShader;
	ShaderID normalShader;
	ShaderID tangentShader;
	ShaderID binormalShader;
	ShaderID lineShader;
	ShaderID TNBShader;

	DepthPass depthPass;
	TextureID errorTexture;
	TextureID loadingScrTex;
	TextureID exampleTex;		// load scr
	TextureID exampleNormMap;
};

class Renderer
{
	friend class Engine;
public:


	Renderer();
	~Renderer();

	bool		Initialize(int width, int height, HWND hwnd);
	void		Exit();
	HWND		GetWindow() const;
	float		AspectRatio() const;
	unsigned	WindowHeight() const;
	unsigned	WindowWidth() const;

	void		EnableAlphaBlending(bool enable);
	void		EnableZBuffer(bool enable);

	// resource interface
	ShaderID		AddShader(const std::string& shdFileName, const std::string& fileRoot, const std::vector<InputLayout>& layouts, bool geoShader = false);
	const Texture&	AddTexture(const std::string& shdFileName, const std::string& fileRoot = s_textureRoot);

	const Shader*	GetShader(ShaderID shader_id) const;
	const Texture&	GetTexture(TextureID) const;
	const ShaderID	GetLineShader() const;

	// state management
	void SetViewport(const unsigned width, const unsigned height);
	void SetCamera(Camera* m_camera);
	void SetShader(ShaderID);
	void SetBufferObj(int BufferID);
	void SetConstant4x4f(const char* cName, const XMMATRIX& matrix);
	void SetConstant3f(const char* cName, const vec3& float3);
	void SetConstant1f(const char* cName, const float data);
	void SetConstant1i(const char* cName, const int data);
	void SetConstantStruct(const char * cName, void* data);
	void SetTexture(const char* texName, TextureID tex);
	void SetRasterizerState(int stateID);
	
	void DrawIndexed(TOPOLOGY topology = TOPOLOGY::TRIANGLE_LIST);
	void Draw(TOPOLOGY topology = TOPOLOGY::POINT_LIST);
	void DrawLine();
	void DrawLine(const vec3& pos1, const vec3& pos2, const vec3& color = Color().Value());

	void Begin(const float clearColor[4]);
	void Reset();
	void Apply();
	void End();
	
	void PollShaderFiles();
private:

	void GeneratePrimitives();
	void LoadShaders();
	void PollThread();
	void OnShaderChange(LPTSTR dir);

	void InitRasterizerStates();
	void LoadAnimation();
	//=======================================================================================================================================================
public:
	static const bool FULL_SCREEN  = false;
	static const bool VSYNC = true;	

	static const char* s_shaderRoot;
	static const char* s_textureRoot;

	RenderData	m_renderData;

private:
	struct TextureSetCommand		{ TextureID texID; ShaderTexture shdTex; };

	D3DManager*						m_Direct3D;
	HWND							m_hWnd;
	ID3D11Device*					m_device;	// ?
	ID3D11DeviceContext*			m_deviceContext;

	GeometryGenerator				m_geom;			// maybe static functions? yes... definitely static functions. todo:

	// render data
	Camera*							m_mainCamera;
	D3D11_VIEWPORT					m_viewPort;

	friend class RigidBody;		// access to m_bufferObjs
	std::vector<BufferObject*>		m_bufferObjects;
	std::vector<Shader*>			m_shaders;
	std::vector<Texture>			m_textures;

	std::queue<TextureSetCommand>	m_texSetCommands;

	// state variables
	ShaderID						m_activeShader;
	BufferID						m_activeBuffer;
	
	std::vector<RasterizerState*>	m_rasterizerStates;
	
	// performance counters
	unsigned long long				m_frameCount;

	friend class IKEngine;	// temp hack
	friend class AnimatedModel;
	//std::vector<Point>				m_debugLines;
};
 
