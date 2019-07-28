#pragma once
#include "stdafx.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

namespace ScriptPtr {
	//std::shared_ptr<[CLASS]> [NAME];
	//In dllmain:
	//[NAME] = std::make_shared<[CLASS]>();
	//Thread::AddScript([NAME]);
	//In Hooking::OnTickInit:
	//Thread::OnTick();
};

class Script {
public:
	virtual ~Script() noexcept = default;
	virtual bool IsInitialized() = 0;
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void Tick() = 0;
protected:
	Script() = default;
};

class Thread {
public:
	explicit Thread();
	~Thread() noexcept;
	static void AddScript(std::shared_ptr<Script> script);
	static void RemoveScript(Script* script);
	static void OnTick();
	template <typename T> static std::shared_ptr<T> classToPtr();
	template <typename T> static void addClass();
private:
	static std::mutex s_mutex;
	static std::vector<std::shared_ptr<Script>> s_scripts;
};


class AbstractCallback
{
public:
	virtual ~AbstractCallback() noexcept = default;
	AbstractCallback(AbstractCallback const&) = delete;
	AbstractCallback& operator=(AbstractCallback const&) = delete;
	AbstractCallback(AbstractCallback&&) = delete;
	AbstractCallback& operator=(AbstractCallback&&) = delete;

	virtual bool IsDone() = 0;
	virtual void OnSuccess() = 0;
	virtual void OnFailure() = 0;
protected:
	AbstractCallback() = default;
};

class ModelCallback : public AbstractCallback
{
public:
	explicit ModelCallback(std::uint32_t model, std::function<void()> action) :
		m_Model(model),
		m_Action(std::move(action))
	{
	}

	bool IsDone() override
	{
		return STREAMING::HAS_MODEL_LOADED(m_Model);
	}

	void OnSuccess() override
	{
		if (m_Action)
			std::invoke(m_Action);
	}

	void OnFailure() override
	{
		STREAMING::REQUEST_MODEL(m_Model);
	}
private:
	std::uint32_t m_Model;
	std::function<void()> m_Action;
};

class NetworkControlCallback : public AbstractCallback
{
public:
	explicit NetworkControlCallback(std::int32_t entity, std::function<void()> action) :
		m_Entity(entity),
		m_Action(std::move(action))
	{
	}

	bool IsDone() override
	{
		return NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(m_Entity);
	}

	void OnSuccess() override
	{
		if (m_Action)
			std::invoke(m_Action);
	}

	void OnFailure() override
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_Entity);
	}
private:
	std::int32_t m_Entity;
	std::function<void()> m_Action;
};

class CallbackScript : public Script
{
public:
	explicit CallbackScript() = default;
	~CallbackScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;

	template <typename CallbackType, typename ...TArgs>
	void AddCallback(TArgs&&... args)
	{
		m_Callbacks.push_back(std::make_unique<CallbackType>(std::forward<TArgs>(args)...));
	}
private:
	bool m_Initialized{};
	std::vector<std::unique_ptr<AbstractCallback>> m_Callbacks;
};