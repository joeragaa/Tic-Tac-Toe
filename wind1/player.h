#pragma once
class player
{
private:
	bool mark; //X is 1 and O is 0
	int score;
public:
	player(bool var)
	{
		mark = var;
		score = 0;
	}
	void IncrementScore()
	{
		score++;
	}
	int getscore()
	{
		return score;
	}
	bool getMark()
	{
		return mark;
	}

};
