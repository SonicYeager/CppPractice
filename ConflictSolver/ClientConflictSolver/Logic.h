#pragma once

class Logic
{
public:
	virtual Table AddBalance(const Input&, const Table&) = 0;
	virtual Table Credit(const Input&, const Table&) = 0;
	virtual ~Logic() = default;
};
