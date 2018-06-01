class Text : public Sprite
{
public:
    Text(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        Sprite::Initialize();
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);
        Create(text, fontSize, fontFace);
    }
    void Create(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        if (text == L"")
            return;

        this->text = text;
        
        brush.Reset();
        App::GetGraphicsContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), brush.GetAddressOf());
        App::GetGraphicsContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        textFormat.Reset();
        App::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        textLayout.Reset();
        App::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), FLT_MAX, FLT_MAX, textLayout.GetAddressOf());
        
        DWRITE_TEXT_METRICS textMetrics;
        textLayout->GetMetrics(&textMetrics);

        textLayout.Reset();
        App::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), textMetrics.width, textMetrics.height, textLayout.GetAddressOf());

        std::unique_ptr<BYTE[]> buffer(new BYTE[textMetrics.width * textMetrics.height * 4]);
        texture.Create(buffer.get(), textMetrics.width, textMetrics.height);

        ATL::CComPtr<IDXGISurface> surface = nullptr;
        texture.GetInterface().QueryInterface(&surface);

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        bitmap.Release();
        App::GetGraphicsContext2D().CreateBitmapFromDxgiSurface(surface, bitmapProperties, &bitmap);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        App::GetGraphicsContext2D().SetTarget(bitmap);

        App::GetGraphicsContext2D().BeginDraw();

        App::GetGraphicsContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
        App::GetGraphicsContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), textLayout.Get(), brush.Get());

        App::GetGraphicsContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    std::wstring text;
    ATL::CComPtr<ID2D1Bitmap1> bitmap = nullptr;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush = nullptr;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
    Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
};