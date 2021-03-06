#ifndef ___INANITY_GRAPHICS_DX11_ATTRIBUTE_BINDING_HPP___
#define ___INANITY_GRAPHICS_DX11_ATTRIBUTE_BINDING_HPP___

#include "AttributeBinding.hpp"
#include "d3d11.hpp"
#include "../ComPointer.hpp"
#include "../String.hpp"
#include <vector>

BEGIN_INANITY_GRAPHICS

class AttributeLayout;
class Dx11VertexShader;

/// Класс привязки атрибутов для DirectX.
/** В данный момент класс ущербный, так как не хранит ID3D11InputLayout.
API не позволяет создать input layout с прямым указанием входных регистров.
Так что тут просто хранятся данные для создания разметки, и кэш таких
разметок хранится в контексте. */
class Dx11AttributeBinding : public AttributeBinding
{
private:
	// структуры описания
	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	// строки для имён семантик
	std::vector<String> semanticNames;

public:
	void Initialize(ptr<AttributeLayout> layout);

	ComPointer<ID3D11InputLayout> CreateInputLayout(ID3D11Device* deviceInterface, Dx11VertexShader* vertexShader);
};

END_INANITY_GRAPHICS

#endif
