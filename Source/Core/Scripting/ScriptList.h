// Copyright 2023 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include "Scripting/ScriptingEngine.h"
#include <unordered_map>

namespace Scripts
{

void StartPendingScripts();
void StopAllScripts();
void StartScript(std::string file_path);
void StopScript(std::string file_path);

// extern so that different translation units can access a global instance of these vars
// i.e. DolphinLib needs to access these variables even though they're housed in the Scripting unit
extern std::unordered_map<std::string, Scripting::ScriptingBackend*> g_scripts;
extern bool g_scripts_started;
//Those list are for scripts that need to get their check icon updated
extern std::unordered_map<std::string, bool*> g_pending_activated_scripts;
extern std::unordered_map<std::string, bool*> g_pending_canceled_scripts;
}
