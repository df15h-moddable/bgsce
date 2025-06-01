#include "version.h"


void MyCallback()
{
	_MESSAGE("This task was implemented with a free function!");
}


extern "C" DLLEXPORT bool APIENTRY SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\MyFirstPlugin.log");
	SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
	SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
	SKSE::Logger::UseLogStamp(true);

	_MESSAGE("MyFirstPlugin v%s", MYFP_VERSION_VERSTRING);

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "MyFirstPlugin";
	a_info->version = MYFP_VERSION_MAJOR;

	if (a_skse->IsEditor()) {
		_FATALERROR("Loaded in editor, marking as incompatible!\n");
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		_FATALERROR("Unsupported runtime version %s!\n", ver.GetString().c_str());
		return false;
	}

	return true;
}


extern "C" DLLEXPORT bool APIENTRY SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	_MESSAGE("MyFirstPlugin loaded");

	if (!SKSE::Init(a_skse)) {
		return false;
	}

	auto task = SKSE::GetTaskInterface();

	// using free function
	task->AddTask(MyCallback);

	// using a lambda
	task->AddTask([]() {
		_MESSAGE("This is a task implemented with a lambda!");
	});

	return true;
}
