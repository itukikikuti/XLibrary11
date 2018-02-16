#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <crtdbg.h>
#include <xaudio2.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Shlwapi.h>
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "Shlwapi.lib")
using namespace std;
using namespace DirectX;

bool endOfStream = false;
Microsoft::WRL::ComPtr<IMFSourceReader> sourceReader;
IXAudio2SourceVoice* sourceVoice;

void SubmitSourceBuffer() {
	static std::vector<BYTE> buffer;

	HRESULT r;

	Microsoft::WRL::ComPtr<IMFSample> sample;
	DWORD flags = 0;
	r = sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

	if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
		endOfStream = true;
		return;
	}

	Microsoft::WRL::ComPtr<IMFMediaBuffer> mediaBuffer;
	r = sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());

	DWORD audioDataLength = 0;
	BYTE* audioData;
	r = mediaBuffer->Lock(&audioData, nullptr, &audioDataLength);

	buffer.resize(audioDataLength);
	memcpy(&buffer[0], audioData, audioDataLength);

	r = mediaBuffer->Unlock();

	XAUDIO2_BUFFER audioBuffer = {};
	audioBuffer.AudioBytes = audioDataLength;
	audioBuffer.pAudioData = &buffer[0];
	audioBuffer.pContext = &buffer[0];
	r = sourceVoice->SubmitSourceBuffer(&audioBuffer);

	r = sourceVoice->Start();
}

class VoiceCallback : public IXAudio2VoiceCallback {
	PUBLIC void _stdcall OnBufferStart(void *pBufferContext) override {
		printf("OnBufferStart\n");
	}
	PUBLIC void _stdcall OnBufferEnd(void *pBufferContext) override {
		SubmitSourceBuffer();
		printf("OnBufferEnd\n");
	}
	PUBLIC void _stdcall OnLoopEnd(void *pBufferContext) override {
		printf("OnLoopEnd\n");
	}
	PUBLIC void _stdcall OnStreamEnd() override {
		printf("OnStreamEnd\n");
	}
	PUBLIC void _stdcall OnVoiceError(void *pBufferContext, HRESULT Error) override {
		printf("OnVoiceError\n");
	}
	PUBLIC void _stdcall OnVoiceProcessingPassStart(UINT32 BytesRequired) override {
		//printf("OnVoiceProcessingPassStart\n");
	}
	PUBLIC void _stdcall OnVoiceProcessingPassEnd() override {
		//printf("OnVoiceProcessingPassEnd\n");
	}
};

int main() {
	Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Camera camera;
	Mesh mesh;
	Texture tex(L"assets/box.jpg");

	camera.position = Float3(0.0f, 1.0f, -2.0f);
	camera.angles.x = 20.0f;
	mesh.CreateCube();
	mesh.Apply();
	mesh.material.SetTexture(0, &tex);

	HRESULT r;

	Microsoft::WRL::ComPtr<IXAudio2> audioEngine;
	r = XAudio2Create(audioEngine.GetAddressOf());

	IXAudio2MasteringVoice* masteringVoice = nullptr;
	r = audioEngine->CreateMasteringVoice(&masteringVoice);
	
	MFStartup(MF_VERSION);

	//std::basic_ifstream<BYTE> file("assets/music.mp3", std::basic_ios<BYTE>::in | std::basic_ios<BYTE>::binary);
	//if (file.fail()) {
	//	return 0;
	//}
	//file.seekg(0, std::basic_ios<BYTE>::end);
	//size_t size = static_cast<size_t>(file.tellg());

	//std::unique_ptr<BYTE[]> buffer(new BYTE[size]);
	//file.seekg(0, std::basic_ios<BYTE>::beg);
	//file.read(buffer.get(), size);

	//Microsoft::WRL::ComPtr<IStream> stream(SHCreateMemStream(buffer.get(), size));
	Microsoft::WRL::ComPtr<IStream> stream;
	r = SHCreateStreamOnFileW(L"assets/music.mp3", STGM_READ, stream.GetAddressOf());

	Microsoft::WRL::ComPtr<IMFByteStream> byteStream;
	r = MFCreateMFByteStreamOnStream(stream.Get(), byteStream.GetAddressOf());

	Microsoft::WRL::ComPtr<IMFAttributes> attributes;
	r = MFCreateAttributes(attributes.GetAddressOf(), 1);

	r = MFCreateSourceReaderFromByteStream(byteStream.Get(), attributes.Get(), sourceReader.GetAddressOf());

	Microsoft::WRL::ComPtr<IMFMediaType> mediaType;
	r = MFCreateMediaType(mediaType.GetAddressOf());
	r = mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	r = mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

	r = sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());

	mediaType.Reset();
	r = sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

	UINT32 waveFormatSize = 0;
	WAVEFORMATEX* waveFormat;
	r = MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &waveFormat, &waveFormatSize);

	VoiceCallback a;
	r = audioEngine->CreateSourceVoice(&sourceVoice, waveFormat, XAUDIO2_VOICE_NOPITCH, 1.0f, &a);

	SubmitSourceBuffer();

	while (App::Refresh()) {
		if (endOfStream) {
			sourceVoice->Stop();
			sourceVoice->FlushSourceBuffers();

			PROPVARIANT position = {};
			position.vt = VT_I8;
			position.hVal.QuadPart = 0;
			sourceReader->SetCurrentPosition(GUID_NULL, position);
			endOfStream = false;
			SubmitSourceBuffer();
		}

		camera.Update();

		mesh.angles.y += App::GetDeltaTime() * 50.0f;

		mesh.position = Float3(0.6f, 0.0f, 0.0f);
		mesh.Draw();

		mesh.position = Float3(-0.6f, 0.0f, 0.0f);
		mesh.Draw();
	}

	sourceVoice->DestroyVoice();
	masteringVoice->DestroyVoice();
	MFShutdown();
	audioEngine->StopEngine();

	return 0;
}
