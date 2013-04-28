#pragma once

#include <exception>
#include <string>

using namespace std;

namespace Exception {
	
	enum Code {
		
		general = 0,
		initialization_failure = 1,
		bad_config = 2,
		bad_config_value = 3,
		config_section_not_found = 4,
		config_key_not_found = 5,
		object_not_found = 6,
		texture_not_found = 7,
		sprite_not_found = 8,
		face_not_found = 9,
		sound_not_found = 10,
		stage_not_found = 11,
		bad_render = 20,
		bad_audio_play = 30,
		overflow = 96,
		game_loop_end = 97,
		bad_object = 98,
		should_not_be_reached = 99
	};
	
	class Base : public exception {
	public:
		Base(const Code code, const char* message);
		Base(const Code code, const char* message, const char* info);
		virtual ~Base() throw();
		const char* what() const throw();
	protected:
		Code code;
		string message;	
	};
	
	class General : public Base {
	public:
		General() : Base(general, "General Exception") {};
	};
	
	class ShouldNotBeReached : public Base {
	public:
		ShouldNotBeReached() : Base(should_not_be_reached, "Code should not be reached") {};
		ShouldNotBeReached(const char* place) : Base(should_not_be_reached, "Code should not be reached", place) {};
	};
	
	class BadObject : public Base {
	public:
		BadObject() : Base(bad_object, "Bad Object") {};
		BadObject(const char* objName) : Base(bad_object, "Bad Object", objName) {};
	};
	
	class GameLoopEnd : public Base {
	public:
		GameLoopEnd() : Base(game_loop_end, "Game Loop End") {};
	};
	
	class Overflow : public Base {
	public:
		Overflow() : Base(overflow, "Overflow") {};
		Overflow(const char* resourceName) : Base(overflow, "Overflow", resourceName) {};
	};
	
	class InitializationFailure : public Base {
	public:
		InitializationFailure() : Base(initialization_failure, "Initialization Failure") {};
	};
	
	class BadConfig: public Base {
	public:
		BadConfig() : Base(bad_config, "Bad Config") {};
		BadConfig(const char* cfg) : Base(bad_config, "Bad Config", cfg) {};
	};
	
	class BadConfigValue: public Base {
	public:
		BadConfigValue() : Base(bad_config_value, "Bad Config Value") {};
		BadConfigValue(const char* value) : Base(bad_config_value, "Bad Config Value", value) {};
	};
	
	class ConfigSectionNotFound : public Base {
	public:
		ConfigSectionNotFound() : Base(config_section_not_found, "Config Section Not Found") {};
		ConfigSectionNotFound(const char* section) : Base(config_section_not_found, "Config Section Not Found", section) {};
	};
	
	class ConfigKeyNotFound : public Base {
	public:
		ConfigKeyNotFound() : Base(config_key_not_found, "Config Key Not Found") {};
		ConfigKeyNotFound(const char* key) : Base(config_key_not_found, "Config Key Not Found", key) {};
	};
	
	class TextureNotFound : public Base {
	public:
		TextureNotFound() : Base(texture_not_found, "Texture Not Found") {};
		TextureNotFound(const char* textureId) : Base(texture_not_found, "Texture Not Found", textureId) {};
	};
		
	class SpriteNotFound : public Base {
	public:
		SpriteNotFound() : Base(sprite_not_found, "Sprite Not Found") {};
		SpriteNotFound(const char* spriteId) : Base(sprite_not_found, "Sprite Not Found", spriteId) {};
	};
	
	class FaceNotFound : public Base {
	public:
		FaceNotFound() : Base(face_not_found, "Face Not Found") {};
		FaceNotFound(const char* faceId) : Base(face_not_found, "Face Not Found", faceId) {};
	};
	
	class SoundNotFound : public Base {
	public:
		SoundNotFound() : Base(sound_not_found, "Sound Not Found") {};
		SoundNotFound(const char* soundId) : Base(sound_not_found, "Sound Not Found", soundId) {};
	};
		
	class StageNotFound : public Base {
	public:
		StageNotFound() : Base(stage_not_found, "Stage Not Found") {};
		StageNotFound(const char* stageId) : Base(stage_not_found, "Stage Not Found", stageId) {};
	};
		
	class ObjectNotFound : public Base {
	public:
		ObjectNotFound() : Base(object_not_found, "Object Not Found") {};
		ObjectNotFound(const char* objectId) : Base(object_not_found, "Object Not Found", objectId) {};	
	};
	
	class BadRender : public Base {
	public:
		BadRender() : Base(bad_render, "Error Rendering Object") {};
		BadRender(const char* spriteId) : Base(bad_render, "Texture Not Found", spriteId) {};
	};
	
	class BadAudioPlay : public Base {
	public:
		BadAudioPlay() : Base(bad_audio_play, "Error Playing Audio") {};
		BadAudioPlay(const char* soundId) : Base(bad_audio_play, "Texture Not Found", soundId) {};
	};

}
