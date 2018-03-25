class Text
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;

    Text(const std::wstring text = L"", int fontSize = 16, const wchar_t* const fontFace = L"")
    {
        Create(text, fontSize, fontFace);
    }
    void Create(const std::wstring text = L"", int fontSize = 16, const wchar_t* const fontFace = L"")
    {
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

        size.y = fontSize;

        LOGFONTW logFont = {};
        logFont.lfHeight = fontSize;
        logFont.lfWeight = 500;
        logFont.lfCharSet = SHIFTJIS_CHARSET;
        logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
        logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        logFont.lfQuality = PROOF_QUALITY;
        logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
        wcscpy_s(logFont.lfFaceName, fontFace);
        HFONT font = CreateFontIndirectW(&logFont);

        HDC dc = GetDC(nullptr);
        HFONT oldFont = (HFONT)SelectObject(dc, font);


        for (size_t i = 0; i < text.length(); i++)
        {
            const MAT2 matrix = { { 0, 1 },{ 0, 0 },{ 0, 0 },{ 0, 1 } };
            GLYPHMETRICS glyphMetrics = {};
            DWORD bufferSize = GetGlyphOutlineW(dc, text[i], GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);

            std::unique_ptr<BYTE[]> buffer(new BYTE[bufferSize]);
            GetGlyphOutlineW(dc, text[i], GGO_GRAY4_BITMAP, &glyphMetrics, bufferSize, buffer.get(), &matrix);

            UINT width = (glyphMetrics.gmBlackBoxX + 3) / 4 * 4;
            UINT height = glyphMetrics.gmBlackBoxY;

            std::unique_ptr<DWORD[]> textureBuffer(new DWORD[width * height]);

            for (UINT x = 0; x < width; x++)
            {
                for (UINT y = 0; y < height; y++)
                {
                    DWORD alpha = buffer[x + width * y] * 255 / 16;
                    textureBuffer[x + width * y] = 0x00ffffff | (alpha << 24);
                }
            }

            size.x += glyphMetrics.gmCellIncX;

            Character* character = new Character();

            character->sprite.Create(reinterpret_cast<BYTE*>(textureBuffer.get()), width, height);
            character->metrics = glyphMetrics;

            characters.push_back(std::unique_ptr<Character>(character));
        }

        SelectObject(dc, oldFont);
        ReleaseDC(nullptr, dc);

        SetPivot(0.0f);
    }
    DirectX::XMINT2 GetSize() const
    {
        return size;
    }
    void SetPivot(Float2 pivot)
    {
        float origin = 0.0f;
        Float2 center;
        center.x = -GetSize().x / 2.0f;
        center.y = -GetSize().y / 2.0f;

        for (size_t i = 0; i < characters.size(); i++)
        {
            Sprite& s = characters[i]->sprite;
            GLYPHMETRICS& m = characters[i]->metrics;
            Float2 size = Float2(static_cast<float>(s.GetSize().x), static_cast<float>(s.GetSize().y));

            Float2 localPivot;
            localPivot.x = -(m.gmptGlyphOrigin.x + center.x + origin) / size.x * 2.0f;
            localPivot.y = -(m.gmptGlyphOrigin.y + center.y) / size.y * 2.0f;
            Float2 offset;
            offset.x = GetSize().x / size.x * pivot.x;
            offset.y = GetSize().y / size.y * pivot.y;

            s.SetPivot(Float2(-1.0f, 1.0f) + localPivot + offset);

            origin += m.gmCellIncX;
        }
    }
    void Draw()
    {
        for (size_t i = 0; i < characters.size(); i++)
        {
            characters[i]->sprite.position = position;
            characters[i]->sprite.angles = angles;
            characters[i]->sprite.scale = scale;
            characters[i]->sprite.color = color;
            characters[i]->sprite.Draw();
        }
    }
    void Load(const wchar_t* const filePath) = delete;

private:
    struct Character
    {
        Sprite sprite;
        GLYPHMETRICS metrics;
    };

    DirectX::XMINT2 size;
    std::vector<std::unique_ptr<Character>> characters;
};