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

struct PSIn
{
	float4 position : SV_POSITION;
	float3 normal	: NORMAL;
	float2 texCoord : TEXCOORD0;
};

cbuffer renderConsts
{
	float gammaCorrection;
};

cbuffer perObject
{
	float3 color;
};

float4 PSMain(PSIn In) : SV_TARGET
{
	// gamma correction
	bool gammaCorrect = gammaCorrection > 0.99f;
	float gamma = 1.0/2.2;


	float2 uv = In.texCoord;
	float4 outColor = float4(uv,0,1);
	

	if(gammaCorrect)
		return pow(outColor, float4(gamma,gamma,gamma,1.0f));
	else
		return outColor;
}