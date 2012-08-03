#ifndef ___INANITY_GRAPHICS_DX_DEVICE_HPP___
#define ___INANITY_GRAPHICS_DX_DEVICE_HPP___

#include "Device.hpp"
#include "../ComPointer.hpp"
#include "d3d.hpp"

BEGIN_INANITY_GRAPHICS

class DxSystem;
class DxContext;

/// Класс графического устройства DirectX 11.
class DxDevice : public Device
{
private:
	/// Графическая система.
	ptr<DxSystem> system;
	/// 3D-устройство.
	ComPointer<ID3D11Device> device;
	/// Основной графический контекст.
	ptr<DxContext> context;

public:
	DxDevice(ptr<DxSystem> system, ComPointer<ID3D11Device> device, ptr<DxContext> context);

	// методы Device
	ptr<System> GetSystem() const;
	ptr<Presenter> CreatePresenter(ptr<Output> output, const PresentMode& mode);
	ptr<Context> GetContext();
	ptr<RenderBuffer> CreateRenderBuffer(size_t width, size_t height, PixelFormat pixelFormat);
	ptr<VertexShader> CreateVertexShader(ptr<File> file);
	ptr<PixelShader> CreatePixelShader(ptr<File> file);
	ptr<UniformBuffer> CreateUniformBuffer(size_t size);
	ptr<VertexBuffer> CreateVertexBuffer(ptr<File> file, size_t vertexStride);
	ptr<IndexBuffer> CreateIndexBuffer(ptr<File> file, size_t indexSize);
	ptr<Texture> CreateStaticTexture(ptr<File> file);

	/// Получить интерфейс устройства DirectX 11.
	ID3D11Device* GetDeviceInterface() const;
};

END_INANITY_GRAPHICS

#endif