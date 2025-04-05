// Copyright 2023 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "Scripting/ScriptList.h"

namespace Scripts
{
void StartPendingScripts()
{
  // NOTE: This may enable scripts in an arbitrary order
  for (auto it = g_scripts.begin(); it != g_scripts.end(); it++)
  {
    if (!it->second)
      it->second = new Scripting::ScriptingBackend(it->first);
  }
  g_scripts_started = true;
}

// called on game close
// maintain enabled flag, but delete backends
void StopAllScripts()
{
  for (auto it = g_scripts.begin(); it != g_scripts.end(); it++)
  {
    if (it->second)
    {
      delete it->second;
      it->second = nullptr;
    }
  }
  g_scripts_started = false;
}

void StopScript(std::string file_path)
{
  if (g_scripts.find(file_path) != g_scripts.end())
  {
    // Disable the script
    delete g_scripts[file_path];
    g_scripts.erase(file_path);

    bool* boolean = nullptr;
    boolean = new bool(true);
    g_pending_canceled_scripts[file_path] = boolean;
  }
}

void StartScript(std::string file_path)
{
  if (g_scripts.find(file_path) != g_scripts.end())
  {
    // Start the script
    Scripting::ScriptingBackend* backend = nullptr;
    if (g_scripts_started)
      backend = new Scripting::ScriptingBackend(file_path);
    g_scripts[file_path] = backend;

    bool* boolean = nullptr;
    boolean = new bool(true);
    g_pending_activated_scripts[file_path] = boolean;
  }
}

std::unordered_map<std::string, bool*> g_pending_activated_scripts = {};
std::unordered_map<std::string, bool*> g_pending_canceled_scripts = {};
std::unordered_map<std::string, Scripting::ScriptingBackend*> g_scripts = {};
bool g_scripts_started = false;
}  // namespace Scripts
