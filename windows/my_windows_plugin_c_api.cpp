#include "include/my_windows_plugin/my_windows_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "my_windows_plugin.h"

void MyWindowsPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  my_windows_plugin::MyWindowsPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
