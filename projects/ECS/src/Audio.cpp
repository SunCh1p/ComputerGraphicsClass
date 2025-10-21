#include "AudioController.h"
#include <iostream>

void AudioController::registerSound(Audio audio, std::wstring path) {
	audioToPath[audio] = path;
}

void AudioController::playSoundInLoop(Audio audio) {
	//find the path for the audio
	auto it = audioToPath.find(audio);
	if (it != audioToPath.end()) {
		std::cout << "found" << std::endl;
		PlaySound(it->second.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}

void AudioController::playSound(Audio audio) {
	//find the path for the audio
	auto it = audioToPath.find(audio);
	if (it != audioToPath.end()) {
		PlaySound(it->second.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void AudioController::cancelSounds() {
	PlaySound(NULL, 0, 0);
}