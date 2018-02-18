//class Text : public Sprite {
//	PUBLIC Text(const wchar_t* text = L"", const wchar_t* fontFamily = L"") {
//		if (text == L"") {
//			text = L"\uFFFD";
//		}
//
//		LOGFONTW logFont = {};
//		logFont.lfHeight = 256;
//		logFont.lfWidth = 0;
//		logFont.lfEscapement = 0;
//		logFont.lfOrientation = 0;
//		logFont.lfWeight = 0;
//		logFont.lfItalic = false;
//		logFont.lfUnderline = false;
//		logFont.lfStrikeOut = false;
//		logFont.lfCharSet = SHIFTJIS_CHARSET;
//		logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
//		logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
//		logFont.lfQuality = PROOF_QUALITY;
//		logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
//		StringCchCopyW(logFont.lfFaceName, 32, fontFamily);
//		HFONT font = CreateFontIndirectW(&logFont);
//
//		HDC dc = GetDC(nullptr);
//		HFONT oldFont = (HFONT)SelectObject(dc, font);
//		UINT code = text[0];
//
//		TEXTMETRICW textMetrics = {};
//		GetTextMetricsW(dc, &textMetrics);
//		GLYPHMETRICS glyphMetrics = {};
//		const MAT2 matrix = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
//		DWORD size = GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);
//		BYTE* textureBuffer = new BYTE[size];
//		GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, size, textureBuffer, &matrix);
//
//		SelectObject(dc, oldFont);
//		DeleteObject(font);
//		ReleaseDC(nullptr, dc);
//
//		width = glyphMetrics.gmCellIncX;
//		height = textMetrics.tmHeight;
//
//		D3D11_TEXTURE2D_DESC textureDesc = {};
//		textureDesc.Width = width;
//		textureDesc.Height = height;
//		textureDesc.MipLevels = 1;
//		textureDesc.ArraySize = 1;
//		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		textureDesc.SampleDesc.Count = 1;
//		textureDesc.SampleDesc.Quality = 0;
//		textureDesc.Usage = D3D11_USAGE_DYNAMIC;
//		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//		textureDesc.MiscFlags = 0;
//
//		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, nullptr, texture.GetAddressOf());
//
//		D3D11_MAPPED_SUBRESOURCE mapped;
//		App::GetGraphicsContext().Map(texture.Get(), D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE_DISCARD, 0, &mapped);
//
//		BYTE* bits = (BYTE*)mapped.pData;
//		DirectX::XMINT2 origin;
//		origin.x = glyphMetrics.gmptGlyphOrigin.x;
//		origin.y = textMetrics.tmAscent - glyphMetrics.gmptGlyphOrigin.y;
//		DirectX::XMINT2 bitmapSize;
//		bitmapSize.x = glyphMetrics.gmBlackBoxX + (4 - (glyphMetrics.gmBlackBoxX % 4)) % 4;
//		bitmapSize.y = glyphMetrics.gmBlackBoxY;
//		const int LEVEL = 17;
//		memset(bits, 0, mapped.RowPitch * textMetrics.tmHeight);
//
//		for (int y = origin.y; y < origin.y + bitmapSize.y; y++) {
//			for (int x = origin.x; x < origin.x + bitmapSize.x; x++) {
//				DWORD alpha = (255 * textureBuffer[x - origin.x + bitmapSize.x * (y - origin.y)]) / (LEVEL - 1);
//				DWORD color = 0x00ffffff | (alpha << 24);
//				memcpy((BYTE*)bits + mapped.RowPitch * y + 4 * x, &color, sizeof(DWORD));
//			}
//		}
//
//		App::GetGraphicsContext().Unmap(texture.Get(), D3D11CalcSubresource(0, 0, 1));
//		delete[] textureBuffer;
//	}
//};
