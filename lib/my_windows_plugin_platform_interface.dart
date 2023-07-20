import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'my_windows_plugin_method_channel.dart';

abstract class MyWindowsPluginPlatform extends PlatformInterface {
  /// Constructs a MyWindowsPluginPlatform.
  MyWindowsPluginPlatform() : super(token: _token);

  static final Object _token = Object();

  static MyWindowsPluginPlatform _instance = MethodChannelMyWindowsPlugin();

  /// The default instance of [MyWindowsPluginPlatform] to use.
  ///
  /// Defaults to [MethodChannelMyWindowsPlugin].
  static MyWindowsPluginPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [MyWindowsPluginPlatform] when
  /// they register themselves.
  static set instance(MyWindowsPluginPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
