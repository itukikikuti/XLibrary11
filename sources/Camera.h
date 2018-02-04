class Camera {
	PROTECTED class CameraConstantBuffer : public ConstantBuffer {
		PUBLIC struct Data {
			PUBLIC DirectX::XMMATRIX view;
			PUBLIC DirectX::XMMATRIX projection;
		};

		Data data;

		PUBLIC CameraConstantBuffer() : ConstantBuffer(sizeof(Data)) {
		}
		PUBLIC void Attach(int slot) {
			ConstantBuffer::Attach(slot, &data);
		}
	};

	PUBLIC DirectX::XMFLOAT3 position;
	PUBLIC DirectX::XMFLOAT3 angles;
	PROTECTED float fieldOfView;
	PROTECTED float nearClip;
	PROTECTED float farClip;
	PROTECTED CameraConstantBuffer cbuffer;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;

	PUBLIC Camera() : cbuffer() {
		Initialize();
		Setup();
	}
	PUBLIC virtual ~Camera() {
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip) {
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		cbuffer.data.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC virtual void Update() {
		TryResize();

		cbuffer.data.view =
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.data.view = DirectX::XMMatrixInverse(nullptr, cbuffer.data.view);
		cbuffer.Attach(1);

		App::GetGraphicsContext().OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget.Get(), color);
	}
	PROTECTED void Initialize() {
		position = DirectX::XMFLOAT3(0.0f, 0.0f, -5.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);
	}
	PROTECTED void Setup() {
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(texture.GetAddressOf()));
		App::GetGraphicsDevice().CreateRenderTargetView(texture.Get(), nullptr, renderTarget.GetAddressOf());

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = (float)App::GetWindowSize().x;
		viewPort.Height = (float)App::GetWindowSize().y;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		App::GetGraphicsContext().RSSetViewports(1, &viewPort);
	}
	PROTECTED void TryResize() {
		for (UINT message : App::GetWindowMessages()) {
			if (message == WM_SIZE) {
				App::GetGraphicsContext().OMSetRenderTargets(1, nullptr, nullptr);
				renderTarget.Reset();
				texture.Reset();
				App::GetGraphicsContext().Flush();
				App::GetGraphicsMemory().ResizeBuffers(2, App::GetWindowSize().x, App::GetWindowSize().y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

				SetPerspective(fieldOfView, nearClip, farClip);
				Setup();
				break;
			}
		}
	}
};
