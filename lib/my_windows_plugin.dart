// You have generated a new plugin project without specifying the `--platforms`
// flag. A plugin project with no platform support was generated. To add a
// platform, run `flutter create -t plugin --platforms <platforms> .` under the
// same directory. You can also find a detailed instruction on how to add
// platforms in the `pubspec.yaml` at
// https://flutter.dev/docs/development/packages-and-plugins/developing-packages#plugin-platforms.

import 'my_windows_plugin_platform_interface.dart';
import 'dart:typed_data';
import 'package:flutter/services.dart';

class MyWindowsPlugin {
  Future<String?> getPlatformVersion() {
    return MyWindowsPluginPlatform.instance.getPlatformVersion();
  }

  static const MethodChannel _channel = MethodChannel('my_windows_plugin');

  static Future<void> printBytes(Uint8List bytes, String filename) async {
    try {
      await _channel.invokeMethod('printBytes', {
        'bytes': bytes,
        'filename': filename,
      });
    } catch (e) {
      throw Exception('Error while printing: $e');
    }
  }
}
