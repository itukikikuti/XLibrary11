class Text
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;

    Text(const std::wstring text = L"", const wchar_t* const fontFace = L"")
    {
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

        LOGFONTW logFont = {};
        logFont.lfHeight = 256;
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
            DWORD size = GetGlyphOutlineW(dc, text[i], GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);

            std::unique_ptr<BYTE[]> glyph(new BYTE[size]);
            GetGlyphOutlineW(dc, text[i], GGO_GRAY4_BITMAP, &glyphMetrics, size, glyph.get(), &matrix);

            UINT width = (glyphMetrics.gmBlackBoxX + 3) / 4 * 4;
            UINT height = glyphMetrics.gmBlackBoxY;

            std::unique_ptr<DWORD[]> buffer(new DWORD[width * height]);

            for (UINT x = 0; x < width; x++)
            {
                for (UINT y = 0; y < height; y++)
                {
                    DWORD alpha = glyph[x + width * y] * 255 / 16;

                    buffer[x + width * y] = 0x00ffffff | (alpha << 24);
                }
            }

            Character* character = new Character();

            character->sprite.Create(reinterpret_cast<BYTE*>(buffer.get()), width, height);
            character->metrics = glyphMetrics;

            characters.push_back(std::unique_ptr<Character>(character));
        }

        SelectObject(dc, oldFont);
        ReleaseDC(nullptr, dc);

        SetPivot();
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

    std::vector<std::unique_ptr<Character>> characters;

    void SetPivot()
    {
        float origin = 0.0f;
        for (size_t i = 0; i < characters.size(); i++)
        {
            Sprite& s = characters[i]->sprite;
            GLYPHMETRICS& m = characters[i]->metrics;

            DirectX::XMINT2 size = s.GetSize();
            Float2 localPivot;
            localPivot.x = -1.0f - (float)m.gmptGlyphOrigin.x / size.x * 2.0f;
            localPivot.y = 1.0f - (float)m.gmptGlyphOrigin.y / size.y * 2.0f;
            float offset = origin / size.x * 2.0f;

            s.SetPivot(Float2(localPivot.x - offset, localPivot.y));

            origin += m.gmCellIncX;
        }
    }
};