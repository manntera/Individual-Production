#pragma once

class Uncopyable
{
public:
	Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
};