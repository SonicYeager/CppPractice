#pragma once

class IUserInterface
{
public:
	virtual bool OpenProgress(const char* header, __int64 maxProgress) = 0;
	virtual void SetProgress(__int64 progress) = 0;
	virtual bool Aborted() const = 0;
	virtual void CloseProgress() = 0;
	virtual ~IUserInterface() = default;

	static IUserInterface* Create();
};
