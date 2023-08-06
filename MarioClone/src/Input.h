#pragma once

class Input {
public:
	static bool keys[1024];
	static bool keyUp[1024];
	static bool const GetKey(int key);
	static bool const GetKeyDown(int key);
};