#include "Arrangement.h"
#include "Video.h"
#include "Audio.h"
#include "Title.h"
#include "Tracer.h"
#include "FindAll.h"
#include <memory>
#include <cassert>

int main()
{
	//Arrangment arrangment;
	//arrangment.AddClip(1, std::make_shared<Audio>(Audio(100ms, 2000ms, L"audio/Trumpets.mp3", 100)));
	//arrangment.AddClip(1, std::make_shared<Video>(Video(1000ms, 500ms, L"video/Alice.m2ts")));
	//arrangment.AddClip(1, std::make_shared<Title>(Title(2500ms, 200ms, "Hello World!", 12)));
	//arrangment.AddClip(2, std::make_shared<Title>(Title(500ms, 500ms, "Small Subtitle...", 10)));
	//arrangment.AddClip(2, std::make_shared<Audio>(Audio(1000ms, 500ms, L"video/Alice.wav", 80)));
	//arrangment.AddClip(2, std::make_shared<Title>(Title(2600ms, 500ms, "Smaller Subtitle...", 8)));
	//arrangment.AddClip(3, std::make_shared<Video>(Video(3100ms, 1500ms, L"video/Testy.mov")));
	//arrangment.AddClip(3, std::make_shared<Video>(Video(4000ms, 1000ms, L"video/OneSecond.mp4")));
	//arrangment.AddClip(3, std::make_shared<Video>(Video(4500ms, 500ms, L"video/Shorty.m2ts")));

	//arrangment.Visit(new Tracer());

	//auto clip = arrangment.FindByNumber(3);
	//clip->Visit(new Tracer());
	//auto vids = arrangment.FindAllVideos();
	//auto titles = arrangment.FindAllTitle();

	//std::cout << arrangment.TotalLength().count();

	//ALEX//

	Arrangment arrangment;
	arrangment.AddClip(1, std::make_shared<Audio>(100ms, 2000ms, L"audio/Trumpets.mp3", 100));
	arrangment.AddClip(1, std::make_shared<Video>(2200ms, 500ms, L"video/Alice.m2ts"));
	arrangment.AddClip(1, std::make_shared<Title>(1000ms, 200ms, "Hello World!", 12));
	arrangment.AddClip(2, std::make_shared<Title>(500ms, 500ms, "Small Subtitle...", 10));
	arrangment.AddClip(2, std::make_shared<Audio>(1000ms, 500ms, L"video/Alice.wav", 80));
	arrangment.AddClip(3, std::make_shared<Title>(2600ms, 500ms, "Smaller Subtitle...", 8));

	assert(6 == arrangment.clips.size());
	assert(3 == arrangment.tracks.size());
	assert(2302ms == arrangment.clips[1]->start);
	assert(500ms == arrangment.clips[5]->length);

	Tracer tracer;
	arrangment.Visit(&tracer);

	assert(arrangment.clips[3] == arrangment.FindByNumber(4));
	assert(arrangment.clips[5] == arrangment.FindByNumber(6));
	assert(nullptr == arrangment.FindByNumber(7));
	assert(arrangment.clips[2] == arrangment.tracks[1]->FindByNumber(3));
	assert(nullptr == arrangment.tracks[2]->FindByNumber(2));


	ClipPtrs expected = {arrangment.clips[1]};
	assert(expected == arrangment.FindAllVideos());
	expected = {arrangment.clips[2], arrangment.clips[3], arrangment.clips[5]};
	assert(expected == arrangment.FindAllTitle());

	assert(3100ms == arrangment.TotalLength());
	return 0;
}
