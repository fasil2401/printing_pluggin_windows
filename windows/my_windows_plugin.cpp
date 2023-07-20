#include "my_windows_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace my_windows_plugin {

// static
void MyWindowsPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "my_windows_plugin",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<MyWindowsPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

MyWindowsPlugin::MyWindowsPlugin() {}

MyWindowsPlugin::~MyWindowsPlugin() {}

void MyWindowsPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else {
    result->NotImplemented();
  }
}

  if (method_call.method_name().compare("printBytes") == 0) {
    const auto arguments = std::get<MapValue>(*method_call.arguments());
    const auto bytes_value = arguments.find(EncodableValue("bytes"));
    const auto filename_value = arguments.find(EncodableValue("filename"));

    if (bytes_value != arguments.end() && bytes_value->second.is_list()) {
      const auto bytes_list = bytes_value->second.ListValue();
      std::vector<BYTE> byte_data;
      for (const auto &byte_value : bytes_list) {
        byte_data.push_back(byte_value.IntValue());
      }

      if (filename_value != arguments.end() && filename_value->second.is_string()) {
        std::wstring filename = flutter::ConvertUTF8ToWide(filename_value->second.StringValue());

        // Implement the Windows printing API calls here.
        // For example, you can use the "CreateDC" and "StartDoc" APIs
        // to create a device context and start the print job.
        // Then, use the "StartPage" and "EndPage" APIs to handle each page of the print job.
        // Finally, use the "EndDoc" and "DeleteDC" APIs to complete the print job.
import ctypes
from ctypes import wintypes

# Constants
PRINTER_DEFAULTS = {"DesiredAccess": winspool.PRINTER_ACCESS_USE}
RAW_DATA_TYPE = "RAW"

# Windows API functions
winspool = ctypes.windll.winspool.drv

def print_raw_data(printer_name, data):
    # Open the printer
    hPrinter = wintypes.HANDLE(0)
    printer_defaults = wintypes.DEVHTND(PRINTER_DEFAULTS)
    winspool.OpenPrinterW(printer_name, ctypes.byref(hPrinter), ctypes.byref(printer_defaults))

    # Start a print job
    doc_info = wintypes.DOCINFOW()
    doc_info.pDocName = "My Document"
    doc_info.pOutputFile = None
    doc_info.pDatatype = RAW_DATA_TYPE
    winspool.StartDocPrinterW(hPrinter, 1, ctypes.byref(doc_info))

    # Start a page
    winspool.StartPagePrinter(hPrinter)

    # Write data to the printer
    data_len = len(data)
    bytes_written = wintypes.DWORD(0)
    winspool.WritePrinter(hPrinter, data, data_len, ctypes.byref(bytes_written))

    # End the page and print job
    winspool.EndPagePrinter(hPrinter)
    winspool.EndDocPrinter(hPrinter)

    # Close the printer
    winspool.ClosePrinter(hPrinter)
        result->Success();
      } else {
        result->Error("INVALID_ARGUMENT", "Invalid or missing filename.");
      }
    } else {
      result->Error("INVALID_ARGUMENT", "Invalid or missing bytes.");
    }
  } else {
    result->NotImplemented();
  }

}  // namespace my_windows_plugin
#include <flutter/plugin_registrar_windows.h>

#include "my_windows_print_plugin.h"

void MyWindowsPrintPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  // The plugin class must be registered.
  MyWindowsPrintPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}