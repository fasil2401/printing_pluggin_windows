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
        #include <iostream>
#include <windows.h>

void printRawData(const std::string& printerName, const uint8_t* data, size_t dataSize)
{
    HANDLE hPrinter;
    DOC_INFO_1 docInfo;
    DWORD bytesWritten = 0;

    // Open the printer
    if (!OpenPrinter(const_cast<LPSTR>(printerName.c_str()), &hPrinter, nullptr))
    {
        std::cerr << "Failed to open the printer. Error code: " << GetLastError() << std::endl;
        return;
    }

    // Set up the document information
    docInfo.pDocName = const_cast<LPSTR>("My Document");
    docInfo.pOutputFile = nullptr;
    docInfo.pDataType = const_cast<LPSTR>("RAW");

    // Start a print job
    if (StartDocPrinter(hPrinter, 1, reinterpret_cast<LPBYTE>(&docInfo)) == 0)
    {
        std::cerr << "Failed to start the print job. Error code: " << GetLastError() << std::endl;
        ClosePrinter(hPrinter);
        return;
    }

    // Start a page
    if (StartPagePrinter(hPrinter) == 0)
    {
        std::cerr << "Failed to start the page. Error code: " << GetLastError() << std::endl;
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return;
    }

    // Write data to the printer
    if (WritePrinter(hPrinter, data, static_cast<DWORD>(dataSize), &bytesWritten) == 0)
    {
        std::cerr << "Failed to write data to the printer. Error code: " << GetLastError() << std::endl;
        EndPagePrinter(hPrinter);
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return;
    }

    // End the page and print job
    if (EndPagePrinter(hPrinter) == 0)
    {
        std::cerr << "Failed to end the page. Error code: " << GetLastError() << std::endl;
    }

    if (EndDocPrinter(hPrinter) == 0)
    {
        std::cerr << "Failed to end the print job. Error code: " << GetLastError() << std::endl;
    }

    // Close the printer
    ClosePrinter(hPrinter);
}

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