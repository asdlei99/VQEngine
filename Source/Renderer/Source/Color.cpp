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


#include "Color.h"
#include "utils.h"

using std::make_pair;

const Color Color::black		= XMFLOAT3(0.0f, 0.0f, 0.0f);
const Color Color::white		= XMFLOAT3(1.0f, 1.0f, 1.0f);
const Color Color::red			= XMFLOAT3(1.0f, 0.0f, 0.0f);
const Color Color::green		= XMFLOAT3(0.0f, 1.0f, 0.0f);
const Color Color::blue			= XMFLOAT3(0.0f, 0.0f, 1.0f);
const Color Color::yellow		= XMFLOAT3(1.0f, 1.0f, 0.0f);
const Color Color::magenta		= XMFLOAT3(1.0f, 0.0f, 1.0f);
const Color Color::cyan			= XMFLOAT3(0.0f, 1.0f, 1.0f);
const Color Color::gray			= XMFLOAT3(0.3f, 0.3f, 0.3f);
const Color Color::light_gray	= XMFLOAT3(0.45f, 0.45f, 0.45f);
const Color Color::orange		= XMFLOAT3(1.0f, 0.5f, 0.0f);
const Color Color::purple		= XMFLOAT3(0.31f, 0.149f, 0.513f);

const Color::ColorPalette Color::s_palette = {
	Color::black,	Color::white,
	Color::red,		Color::green,		Color::blue,
	Color::yellow,	Color::magenta,		Color::cyan,
	Color::gray,	Color::light_gray,
	Color::orange,	Color::purple
};


;

Color::Color() 
	: 
	value(white.Value())
{}


//const ColorPalette Color::Palette()
//{
//	return s_palette;
//}

const Color::ColorPalette Color::Palette()
{
	return s_palette;
}

XMFLOAT3 Color::RandColorF3()
{
	size_t i = RandU(0, Palette().size());
	return s_palette[i].Value();
}

XMVECTOR Color::RandColorV()
{
	size_t i = RandU(0, Palette().size());
	XMVECTOR v = XMLoadFloat3(&s_palette[i].Value());
	return v;
}

Color Color::RandColor()
{
	return s_palette[RandU(0, Palette().size())];
}



Color::Color(const XMFLOAT3& val)
	: 
	value(val)
{}

Color::Color(float r, float g, float b)
	:
	value(XMFLOAT3(r, g, b))
{}

Color & Color::operator=(const Color & rhs)
{
	this->value = rhs.Value();
	return *this;
}

Color & Color::operator=(const XMFLOAT3& flt)
{
	this->value = flt;
	return *this;
}

//Color Color::GetColorByName(std::string colorName)
//{
//	return colorRefTable.at(colorName);
//}
//std::string Color::GetNameByColor(Color c)
//{
//	for (ColorMap::iterator it = colorRefTable.begin(); it != colorRefTable.end(); it++)
//	{
//		if (it->second.value == c.value)
//			return it->first;
//	}
//
//	return "White";
//}
