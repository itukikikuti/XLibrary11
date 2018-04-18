class Text : public Sprite
{
public:
    Text(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"")
    {
        Sprite::Initialize();
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);
        Create(text, fontSize, fontFace);
    }
    void Create(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"")
    {
        if (text == L"")
            return;

        this->text = text;

        length = DirectX::XMINT2(0, 1);
        int maxLength = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == L'\n')
            {
                maxLength = 0;
                length.y++;
                continue;
            }

            maxLength++;

            if (length.x < maxLength)
            {
                length.x = maxLength;
            }
        }

        DirectX::XMINT2 textureSize(static_cast<int>(length.x * fontSize), static_cast<int>(length.y * fontSize * 1.5f));
        std::unique_ptr<BYTE[]> buffer(new BYTE[textureSize.x * textureSize.y * 4]);
        texture.Create(buffer.get(), textureSize.x, textureSize.y);

        ATL::CComPtr<IDXGISurface> surface = nullptr;
        texture.GetInterface().QueryInterface(&surface);

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        ATL::CComPtr<ID2D1Bitmap1> bitmap = nullptr;
        App::GetGraphicsContext2D().CreateBitmapFromDxgiSurface(surface, bitmapProperties, &bitmap);

        App::GetGraphicsContext2D().SetTarget(bitmap);

        brush.Reset();
        App::GetGraphicsContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), brush.GetAddressOf());
        App::GetGraphicsContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        textFormat.Reset();
        App::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        App::GetGraphicsContext2D().BeginDraw();
        App::GetGraphicsContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));

        Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
        App::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y), textLayout.GetAddressOf());

        App::GetGraphicsContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), textLayout.Get(), brush.Get());

        App::GetGraphicsContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    std::wstring text;
    DirectX::XMINT2 length;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush = nullptr;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
};