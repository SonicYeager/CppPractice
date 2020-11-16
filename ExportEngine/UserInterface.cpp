#include "UserInterface.h"
#include <string>


class UserInterface : public IUserInterface
{
public:
	bool OpenProgress(const char* pHeader, __int64 maxProgress) override
	{
		if(pHeader == nullptr)
			return false;
		m_header = pHeader;
		m_progress = 0;
		return true;
	}

	void SetProgress(__int64 progress) override
	{
		m_progress = progress;
	}

	bool Aborted() const override
	{
		return false;
	}

	void CloseProgress() override
	{
		m_progress = m_maxProgress;
	}

	std::string m_header = {};
	__int64 m_progress = 0;
	__int64 m_maxProgress = 0;
};


IUserInterface* IUserInterface::Create()
{
	return new UserInterface;
}
