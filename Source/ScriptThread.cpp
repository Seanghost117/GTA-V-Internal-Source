#include "stdafx.h"
#include <mutex>
#include <shared_mutex>

std::vector<std::shared_ptr<Script>> Thread::s_scripts;
std::mutex Thread::s_mutex;

Thread::Thread() {

}

Thread::~Thread() noexcept {
	for (auto&& script : s_scripts)
	{
		script->Destroy();
	}
}

void Thread::AddScript(std::shared_ptr<Script> script) {
	std::lock_guard<std::mutex> lock(s_mutex);
	s_scripts.push_back(std::move(script));
}

void Thread::RemoveScript(Script* script) {
	std::lock_guard<std::mutex> lock(s_mutex);
	for (auto it = s_scripts.begin(), end = s_scripts.end(); it != end; ++it)
	{
		if (it->get() == script)
		{
			(*it)->Destroy();
			s_scripts.erase(it);
			return;
		}
	}
}

void Thread::OnTick() {
	std::lock_guard<std::mutex> lock(s_mutex);
	for (auto&& script : s_scripts)
	{
		if (!script->IsInitialized())
			script->Initialize();
		script->Tick();
	}
}

template <typename T>
std::shared_ptr<T> Thread::classToPtr() {
	std::shared_ptr<T> ptr;
	ptr = std::make_shared<T>();
	return ptr;
}

template <typename T>
void Thread::addClass() {
	std::shared_ptr<T> ptr;
	ptr = Thread::classToPtr<T>();
	std::stringstream sstream;
	sstream << std::hex << rndInt(1, 1337);
	std::string hex = sstream.str();
	std::ostringstream ss;
	ss << "Added Script_" << hex << " to Queue";
	Log::Msg(ss.str().c_str());
	Thread::AddScript(ptr);
}


bool CallbackScript::IsInitialized()
{
	return m_Initialized;
}

void CallbackScript::Initialize()
{
	m_Initialized = true;
}

void CallbackScript::Destroy()
{
}

void CallbackScript::Tick()
{
	for (auto it = m_Callbacks.begin(); it != m_Callbacks.end(); ++it)
	{
		auto&& cb = *it;
		if (cb->IsDone())
		{
			cb->OnSuccess();
			it = m_Callbacks.erase(it);
		}
		else
		{
			cb->OnFailure();
		}
	}
}