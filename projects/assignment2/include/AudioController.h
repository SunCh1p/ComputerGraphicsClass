#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>

enum class Audio {
	DANCEMUSIC,
	SPEAKSOUND
};

class AudioController {
public:
	//register sound in the hashmap
	void registerSound(Audio audio, std::wstring path);
	//play sound in loop from the hash map if it exists
	void playSoundInLoop(Audio audio);
	//play sound for recording duration from the hash map if it exists
	void playSound(Audio audio);
	//cancel all sounds
	void cancelSounds();
private:
	//hashmap for associationg audio scoped enum with sound path
	std::unordered_map<Audio, std::wstring> audioToPath;
};
