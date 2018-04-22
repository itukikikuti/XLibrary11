#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <sstream>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

using namespace std;
using namespace DirectX;

int main()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetPerspective(60.0f, 0.1f, 100.0f);

    Texture texture(L"assets/box.jpg");

    Mesh mesh;
    mesh.GetMaterial().SetTexture(0, &texture);

    Text text(L"菊池いつきです。\n今日は天気も良くおならが出そうです。\n何を言ってるのかわからないですよね、僕もわからないです！\nabcdefghijklmnopqrstuvwxyz", 16.0f);
    //text.SetPivot(Float2(-1.0f, 1.0f));
    text.position.y = 2.0f;
    text.scale = 1.0f / 50.0f;

    Text number(L"0", 100.0f);
    number.position.y = 3.0f;
    number.scale = 1.0f / 100.0f;
    number.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);

    Sound music(L"assets/music.mp3");
    //music.SetLoop(true);
    //music.SetVolume(0.5f);
    //music.Play();

    Sound sound(L"assets/sound.wav");

    Sprite sprite(L"assets/clock.png");
    sprite.position.z = 100.0f;
    sprite.scale = 0.1f;






	ATL::CComPtr<IDirectSound8> device = nullptr;
	DirectSoundCreate8(nullptr, &device, nullptr);

	device->SetCooperativeLevel(App::GetWindowHandle(), DSSCL_PRIORITY);

	MFStartup(MF_VERSION);

	ATL::CComPtr<IStream> stream = nullptr;
	SHCreateStreamOnFileW(L"assets/music.mp3", STGM_READ, &stream);
	//SHCreateStreamOnFileW(L"assets/sound.wav", STGM_READ, &stream);

	ATL::CComPtr<IMFByteStream> byteStream = nullptr;
	MFCreateMFByteStreamOnStream(stream, &byteStream);

	ATL::CComPtr<IMFAttributes> attributes = nullptr;
	MFCreateAttributes(&attributes, 1);

	ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
	MFCreateSourceReaderFromByteStream(byteStream, attributes, &sourceReader);

	ATL::CComPtr<IMFMediaType> mediaType = nullptr;
	MFCreateMediaType(&mediaType);
	mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	//mediaType->SetUINT32(MF_MT_FIXED_SIZE_SAMPLES, 1);

	sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);
	mediaType.Release();
	sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

	UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
	WAVEFORMATEX* waveFormat;
	MFCreateWaveFormatExFromMFMediaType(mediaType, &waveFormat, &waveFormatSize);

	ATL::CComPtr<IMFSample> sample = nullptr;
	DWORD flags = 0;
	sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

	ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
	sample->ConvertToContiguousBuffer(&mediaBuffer);

	DWORD _kjnk;
	mediaBuffer->GetMaxLength(&_kjnk);

	DSBUFFERDESC bufferDesc = {};
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	//bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
	bufferDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2;
	bufferDesc.dwBufferBytes = (_kjnk - waveFormat->nBlockAlign) * 2;
	bufferDesc.lpwfxFormat = waveFormat;

	DWORD size = bufferDesc.dwBufferBytes / 2;

	//mediaType.Release();
	//sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);
	//mediaType->SetUINT32(MF_MT_SAMPLE_SIZE, size);
	//sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);

	ATL::CComPtr<IDirectSoundBuffer> soundBuffer = nullptr;
	device->CreateSoundBuffer(&bufferDesc, &soundBuffer, nullptr);

	auto Temp = [&](void* buffer, DWORD size)
	{
		if (buffer == nullptr)
			return;

		memset(buffer, 128, size);

		//mediaType.Release();
		//sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

		//mediaType->SetUINT32(MF_MT_FIXED_SIZE_SAMPLES, 1);
		//mediaType->SetUINT32(MF_MT_SAMPLE_SIZE, size);

		//sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);

		ATL::CComPtr<IMFSample> sample = nullptr;
		DWORD flags = 0;
		sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			PROPVARIANT position = {};
			position.vt = VT_I8;
			position.hVal.QuadPart = 0;
			sourceReader->SetCurrentPosition(GUID_NULL, position);

			sample.Release();
			sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
		}

		DWORD wief;
		mediaBuffer->GetCurrentLength(&wief);

		ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
		sample->ConvertToContiguousBuffer(&mediaBuffer);
		mediaBuffer->SetCurrentLength(size);

		BYTE* temp = nullptr;
		mediaBuffer->Lock(&temp, nullptr, &size);
		memcpy(buffer, temp, size);
		mediaBuffer->Unlock();
		printf("%d %d\n", temp[0], temp[size - 1]);
	};

	soundBuffer->Play(0, 0, DSBPLAY_LOOPING);




    while (App::Refresh())
    {
        camera.Update();



		DWORD position;
		static int index = 0;
		soundBuffer->GetCurrentPosition(&position, 0);
		void* buffer1 = 0;
		DWORD bufferSize1 = 0;
		void* buffer2 = 0;
		DWORD bufferSize2 = 0;
		if (index == 0 && position < size)
		{
			soundBuffer->Lock(size, size * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
			Temp(buffer1, bufferSize1);
			soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
			index = 1;
		}
		if (index == 1 && position >= size)
		{
			soundBuffer->Lock(0, size, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
			Temp(buffer1, bufferSize1);
			soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
			index = 0;
		}




		if (App::GetKeyDown(VK_SPACE))
		{
			//sound.Play();
		}

        if (!App::GetKey('2'))
        {
            text.angles.z += 1.0f;
            text.Draw();

            number.Draw();
        }
        else
        {
            wstringstream ss;
            ss << App::GetTime();
            number.Create(ss.str(), 100.0f);
            number.Draw();
        }

        mesh.angles.y += 1.0f;
        mesh.Draw();

        if (App::GetKey('1'))
            App::SetMousePosition(0.0f, 0.0f);

        sprite.position.x = App::GetMousePosition().x / 5.0f;
        sprite.position.y = App::GetMousePosition().y / 5.0f;
        sprite.Draw();
    }




	MFShutdown();




    return 0;
}
