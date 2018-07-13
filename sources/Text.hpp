class Text : public Sprite
{
public:
    bool antialias = true;

    Text(const std::wstring& text = L"", float fontSize = 16.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        Sprite::Initialize();
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);
        Create(text, fontSize, align, fontFace);
    }
    void Create(const std::wstring& text = L"", float fontSize = 16.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        if (text == L"")
            return;

        _brush.Reset();
        Graphics::GetContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), _brush.GetAddressOf());

        ComPtr<IDWriteTextFormat> textFormat = nullptr;
        Graphics::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(align);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        _textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), _textLayout.GetAddressOf());
        
        DWRITE_TEXT_METRICS textMetrics;
        _textLayout->GetMetrics(&textMetrics);

        _textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), textMetrics.width, textMetrics.height, _textLayout.GetAddressOf());

        std::unique_ptr<BYTE[]> buffer(new BYTE[int(textMetrics.width * textMetrics.height) * 4]);
        _texture.Create(buffer.get(), (int)textMetrics.width, (int)textMetrics.height);

        ComPtr<IDXGISurface> surface = nullptr;
        _texture.GetInterface().QueryInterface(surface.GetAddressOf());

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        _bitmap.Reset();
        Graphics::GetContext2D().CreateBitmapFromDxgiSurface(surface.Get(), bitmapProperties, _bitmap.GetAddressOf());

        _mesh.GetMaterial().SetTexture(0, &_texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        if (antialias)
            Graphics::GetContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);
        else
            Graphics::GetContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        Graphics::GetContext2D().SetTarget(_bitmap.Get());

        Graphics::GetContext2D().BeginDraw();

        Graphics::GetContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
        Graphics::GetContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), _textLayout.Get(), _brush.Get());

        Graphics::GetContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    ComPtr<ID2D1Bitmap1> _bitmap = nullptr;
    ComPtr<ID2D1SolidColorBrush> _brush = nullptr;
    ComPtr<IDWriteTextLayout> _textLayout = nullptr;
};