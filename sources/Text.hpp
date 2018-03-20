class Text
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;

    Text(const std::wstring text = L"", const wchar_t* fontFamily = L"")
    {
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

        for (size_t i = 0; i < text.length(); i++)
        {
            LOGFONTW logFont = {};
            logFont.lfHeight = 256;
            logFont.lfWidth = 0;
            logFont.lfEscapement = 0;
            logFont.lfOrientation = 0;
            logFont.lfWeight = 0;
            logFont.lfItalic = false;
            logFont.lfUnderline = false;
            logFont.lfStrikeOut = false;
            logFont.lfCharSet = SHIFTJIS_CHARSET;
            logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
            logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            logFont.lfQuality = PROOF_QUALITY;
            logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
            wcscpy_s(logFont.lfFaceName, fontFamily);
            HFONT font = CreateFontIndirectW(&logFont);

            HDC dc = GetDC(nullptr);
            HFONT oldFont = (HFONT)SelectObject(dc, font);
            UINT code = text[i];

            TEXTMETRICW textMetrics = {};
            GetTextMetricsW(dc, &textMetrics);
            GLYPHMETRICS glyphMetrics = {};
            const MAT2 matrix = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
            DWORD size = GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);
            std::unique_ptr<BYTE[]> glyph(new BYTE[size]);
            GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, size, glyph.get(), &matrix);

            SelectObject(dc, oldFont);
            DeleteObject(font);
            ReleaseDC(nullptr, dc);

            UINT width = glyphMetrics.gmCellIncX;
            UINT height = textMetrics.tmHeight;

            std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

            DirectX::XMINT2 origin;
            origin.x = glyphMetrics.gmptGlyphOrigin.x;
            origin.y = textMetrics.tmAscent - glyphMetrics.gmptGlyphOrigin.y;
            DirectX::XMINT2 bitmapSize;
            bitmapSize.x = glyphMetrics.gmBlackBoxX + (4 - (glyphMetrics.gmBlackBoxX % 4)) % 4;
            bitmapSize.y = glyphMetrics.gmBlackBoxY;
            const int LEVEL = 17;
            memset(buffer.get(), 0, width * 4 * height);

            for (int y = origin.y; y < origin.y + bitmapSize.y; y++)
            {
                for (int x = origin.x; x < origin.x + bitmapSize.x; x++)
                {
                    DWORD alpha = (255 * glyph[x - origin.x + bitmapSize.x * (y - origin.y)]) / (LEVEL - 1);
                    DWORD color = 0x00ffffff | (alpha << 24);
                    memcpy(&buffer[(width * 4) * y + 4 * x], &color, sizeof(DWORD));
                }
            }

            Sprite sprite;
            sprites.push_back(sprite);

            sprites[i].GetTexture().Create(buffer.get(), width, height);
            sprites[i].GetMaterial().SetBuffer(2, &color, sizeof(Float4));
            sprites[i].GetMaterial().SetTexture(0, &sprites[i].GetTexture());

            sprites[i].SetPivot(0.0f);
        }
    }
    void Draw()
    {
        for (int i = 0; i < sprites.size(); i++)
        {
            sprites[i].position = position;
            sprites[i].angles = angles;
            sprites[i].scale = scale;
            sprites[i].Draw();
        }
    }
    void Load(const wchar_t* const filePath) = delete;

private:
    std::vector<Sprite> sprites;
};