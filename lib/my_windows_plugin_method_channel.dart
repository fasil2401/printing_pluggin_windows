import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'my_windows_plugin_platform_interface.dart';

/// An implementation of [MyWindowsPluginPlatform] that uses method channels.
class MethodChannelMyWindowsPlugin extends MyWindowsPluginPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('my_windows_plugin');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
