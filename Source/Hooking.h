#pragma once
//hello everyone this is 1337 0w0 hooks, you don't need everything that's commented you will be fine and can compile, learn from this
//and learn how they work, arguments, etc. If you need help you can always leave a comment or message me

//gone for protection
typedef bool(* fpIsDLCPresent)(std::uint32_t dlcHash);
//0w0typedef Object(__cdecl*	fp_CreateObject)(Hash modelHash, Vector3* pos, BOOL isNetwork, BOOL thisScriptCheck, BOOL dynamic);
//removed typedef void(__cdecl* fpsetlobbyweather)(null);
//removed typedef int(__cdecl*	TriggerScriptEvent)(null); //Find on UC
//both removed (model bypass)
//been removed typedef void(__fastcall* tSET_ENTITY_MAX_HEALTH)(Entity entity, int value);
//removed typedef __int64(__cdecl* fpGetPlayerAddress)(Player);
typedef bool(__cdecl* GetEventData)(int eventGroup, int eventIndex, uint64_t* argStruct, int argStructSize);
//removed typedef bool(__cdecl* fpSetName)();
typedef bool(__cdecl* fpIncrementStatHook)(__int64 a1, __int64 a2, float a3);
//removed typedef void(__cdecl* addOwnedExplosion)(null);
//removed typedef bool(__cdecl* fpSetLobbyTime)(int, int, int);
typedef bool(__cdecl* fpStatSetInt)(Hash statName, int value, BOOL save);
//removed typedef BOOL(__cdecl* fpStatSetBool)(Hash statname, bool value, bool save);
//removed typedef BOOL(__cdecl* fpStatSetFloat)(Hash statname, float value, bool save);
typedef BOOL(__cdecl* fpCreateAmbientPickup)(DWORD pickupHash, Vector3* pos, int unk0, int value, DWORD modelHash, bool unk1, bool unk2);
typedef uint32_t*(*__cdecl fpFileRegister)(int*, const char*, bool, const char*, bool);
//removed typedef bool(__cdecl* fpSendMessage2)(null);
//removed typedef bool(__cdecl* fpAddTextCompSubstrPlayerName)(null);
//removed typedef bool(__cdecl* fpEndTextCmdDisplayText)(null);
//removed typedef bool(__cdecl* fpBeginTextCmdDisplayText)(null);
//removed typedef __int64(__cdecl* fpGetPlayerAddress)(Player player);
//removed typedef Entity(__cdecl* fpAddressToEntity)(__int64 address);
using fpGetLabelText = const char* (*) (void* this_, const char* label);
//removed struct clockTime { int hour, minute, second; };
//removed typedef void(__cdecl* fpSetSessionTime)(int, int);
//removed typedef char* (__cdecl* fpGetPlayerName)(Player player);
typedef BOOL(__cdecl*	fpStatGetInt)(DWORD hash, int* out, int unk0);
//removed typedef BOOL(__cdecl* fpIsPlayerFriend)(int* handle);


class Hooking
{
private:
	static BOOL InitializeHooks();
	static void FindPatterns();
	static void FailPatterns(const char* name);
	

public:
	static fpFileRegister            m_fileregister;
	static std::vector<LPVOID>		m_hooks;
	static uint64_t*				m_frameCount;
	static fpIsDLCPresent			is_DLC_present;
//removed	static fp_CreateObject          create_object;
//removed	static fpsetlobbyweather        set_lobby_weather;
//removed	static TriggerScriptEvent		trigger_script_event;
//removed	static fpSetName			    SetName;
	static BlipList * GetBlipList();
	static HMODULE                  scriptDLL;

	static fpGetLabelText GetLabelText;
//removed
	static GetEventData             get_script_event_data;
	static fpCreateAmbientPickup	create_ambient_pickup;
	static fpIncrementStatHook	    increment_stat_hook;

	static fpStatSetInt            stat_set_int;
	static fpStatGetInt			Hooking::stat_get_int;


	using fpGetLabelText = const char* (*) (void* this_, const char* label);

	static __int64* getGlobalPtr1(int index);
	static __int64* getTunable(int Tunable);
	static void setTunable(int Tunable, __int64 value);
	static Ped get_player_ped(Player player);
//removed 	static bool reportNotification;
	static bool rdev;
//removed	static bool found_idp;
//removed	static bool found_dce;
//removed	static bool found_ssi;
//removed	static bool found_sge;
//removed	static bool found_gcm;
//removed	static bool found_glt;
//removed	static bool found_gsh;
//removed	static bool found_ged;
//removed	static bool found_nts;
//removed	static bool found_prw;
	static void foundPtr(char* name);
	

	static void Start(HMODULE hmoduleDLL);
	static void __declspec(noreturn) Cleanup();
	static eGameState GetGameState();
	static uint64_t getWorldPtr();
	static void onTickInit();
	static bool HookNatives();
	static __int64** getGlobalPtr();
	//static __int64* getGlobalPtr1(int index);
	//static __int64* setTunable(int Tunable);
	static void defuseEvent(RockstarEvent e, bool toggle);


	//auto get_file_register() { return file_register; }
	//auto get_set_night_vision() { return set_night_vision; }
	// Native function handler type
	typedef void(__cdecl * NativeHandler)(scrNativeCallContext * context);
	struct NativeRegistrationNew
	{
		uint64_t nextRegistration1;
		uint64_t nextRegistration2;
		Hooking::NativeHandler handlers[7];
		uint32_t numEntries1;
		uint32_t numEntries2;
		uint64_t hashes;

		inline NativeRegistrationNew* getNextRegistration()
		{
			uintptr_t result;
			auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
			auto v12 = 2i64;
			auto v13 = v5 ^ nextRegistration2;
			auto v14 = (char *)&result - v5;
			do
			{
				*(DWORD*)&v14[v5] = (DWORD)(v13 ^ *(DWORD*)v5);
				v5 += 4i64;
				--v12;
			} while (v12);

			return reinterpret_cast<NativeRegistrationNew*>(result);
		}

		inline uint32_t getNumEntries()
		{
			return (uint32_t)(((uintptr_t)&numEntries1) ^ numEntries1 ^ numEntries2);
		}

		inline uint64_t getHash(uint32_t index)
		{

			auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
			auto v8 = 2i64;
			uint64_t nResult;
			auto v11 = (char *)&nResult - naddr;
			auto v10 = naddr ^  *(DWORD*)(naddr + 8);
			do
			{
				*(DWORD *)&v11[naddr] = (DWORD)(v10 ^ *(DWORD*)(naddr));
				naddr += 4i64;
				--v8;
			} while (v8);

			return nResult;
		}
	};
	static NativeHandler GetNativeHandler(uint64_t origHash);
};

void WAIT(DWORD ms);


enum eThreadState
{
	ThreadStateIdle = 0x0,
	ThreadStateRunning = 0x1,
	ThreadStateKilled = 0x2,
	ThreadState3 = 0x3,
	ThreadState4 = 0x4,
};

struct scrThreadContext
{
	int ThreadID;
	int ScriptHash;
	eThreadState State;
	int _IP;
	int FrameSP;
	int _SPP;
	float TimerA;
	float TimerB;
	int TimerC;
	int _mUnk1;
	int _mUnk2;
	int _f2C;
	int _f30;
	int _f34;
	int _f38;
	int _f3C;
	int _f40;
	int _f44;
	int _f48;
	int _f4C;
	int _f50;
	int pad1;
	int pad2;
	int pad3;
	int _set1;
	int pad[17];
};

struct scrThread
{
	void *vTable;
	scrThreadContext m_ctx;
	void *m_pStack;
	void *pad;
	void *pad2;
	const char *m_pszExitMessage;
};

struct ScriptThread : scrThread
{
	const char Name[64];
	void *m_pScriptHandler;
	const char gta_pad2[40];
	const char flag1;
	const char m_networkFlag;
	bool bool1;
	bool bool2;
	bool bool3;
	bool bool4;
	bool bool5;
	bool bool6;
	bool bool7;
	bool bool8;
	bool bool9;
	bool bool10;
	bool bool11;
	bool bool12;
	const char gta_pad3[10];
};

/*
//CPatternResult
*/

class CPatternResult
{
public:
	CPatternResult(void* pVoid);
	CPatternResult(void* pVoid, void* pBegin, void* pEnd);
	~CPatternResult();

	template <typename rT>
	rT*	get(int offset = 0)
	{
		rT*	ret = nullptr;
		if (m_pVoid != nullptr)
			ret = reinterpret_cast<rT*>(reinterpret_cast<char*>(m_pVoid) + offset);
		return ret;
	}

	template <typename rT>
	rT* get_rel(int offset = 0)
	{
		rT*		result = nullptr;
		int32_t	rel;
		char*	ptr = get<char>(offset);

		if (ptr == nullptr)
			goto LABEL_RETURN;

		rel = *(int32_t*)ptr;
		result = reinterpret_cast<rT*>(ptr + rel + sizeof(rel));

	LABEL_RETURN:
		return result;
	}

	template <typename rT>
	rT*	section_begin()
	{
		return reinterpret_cast<rT*>(m_pBegin);
	}

	template <typename rT>
	rT*	section_end()
	{
		return reinterpret_cast<rT*>(m_pEnd);
	}

protected:
	void*	m_pVoid = nullptr;
	void*	m_pBegin = nullptr;
	void*	m_pEnd = nullptr;
};

class CMetaData
{
public:
	static uint64_t	begin();
	static uint64_t	end();
	static DWORD	size();
	static void		init();
private:
	static uint64_t	m_begin;
	static uint64_t	m_end;
	static DWORD	m_size;
};

/*
//CPattern
*/

typedef	std::vector<CPatternResult>	vec_result;
class CPattern
{
public:
	CPattern(char* szByte, char* szMask);
	~CPattern();

	CPattern&		find(int i = 0, uint64_t startAddress = 0);		//scans for i patterns
	CPattern&		virtual_find(int i = 0, uint64_t startAddress = 0);
	CPatternResult	get(int i);				//returns result i

protected:
	char*			m_szByte;
	char*			m_szMask;
	bool			m_bSet;
	vec_result		m_result;

	bool		match(int i = 0, uint64_t startAddress = 0, bool virt = false);
	bool		byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask);
	uint64_t	find_pattern(uint64_t i64Address, uint64_t end, BYTE *btMask, char *szMask);
	uint64_t	virtual_find_pattern(uint64_t address, BYTE *btMask, char *szMask);
};

struct MinHookKeepalive
{
	MinHookKeepalive();
	~MinHookKeepalive();
};

extern MinHookKeepalive g_MinHookKeepalive;

extern HMODULE _hmoduleDLL;
