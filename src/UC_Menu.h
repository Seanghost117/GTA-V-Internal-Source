#include "stdafx.h"

extern int selectedPlayer;
void ScriptMain();

class HotkeyScript : public Script {
public:
	explicit HotkeyScript() = default;
	~HotkeyScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};

class ControlScript : public Script {
public:
	explicit ControlScript() = default;
	~ControlScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};

class UpdateScript : public Script {
public:
	explicit UpdateScript() = default;
	~UpdateScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};

class DisplayScript : public Script {
public:
	explicit DisplayScript() = default;
	~DisplayScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};
