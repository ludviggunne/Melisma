#pragma once

#include <thread>
#include <chrono>

namespace melisma {

	template<typename InfoBlockType>
	class Profile {
	public:
		virtual Profile() final : m_Running(false) {}
		virtual ~Profile() final { if(m_Running) EndProfile(); }

		virtual void BeginProfile() final {
			m_Running = true;
			m_Thread = std::thread(&Profile::ThreadFunctionWrapper, this);
		}

		virtual void FrameUpdate(const InfoBlockType &infoBLock) final { m_InfoBlock = infoBLock; }
		virtual void EndProfile() final { m_Running = false; m_Thread.join(); }

	protected:
		virtual void ThreadFunction() = 0;
		virtual void ThreadFunctionWrapper() final {
			while (m_Running) ThreadFunction();
		}

		bool m_Running;
		InfoBlockType m_InfoBlock;
		std::thread m_Thread;
	};

}