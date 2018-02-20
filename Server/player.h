#pragma once
#include <string>
#include <list>

class Player {
public:
	Player(std::string, unsigned __int64);
	~Player();

	void setLocation(float x, float y, float z);

	inline float getX() { return x_; };
	inline float getY() { return y_; };
	inline float getZ() { return z_; };
	inline std::list<Player *>& getClosePlayers() { return closePlayers_; };

	unsigned __int64 getClientId() { return serverClientId_; };
private:
	std::string username_;
	float x_, y_, z_;
	unsigned __int64 serverClientId_;
	std::list<Player *> closePlayers_;
};