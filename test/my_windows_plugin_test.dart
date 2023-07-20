import 'package:flutter_test/flutter_test.dart';
import 'package:my_windows_plugin/my_windows_plugin.dart';
import 'package:my_windows_plugin/my_windows_plugin_platform_interface.dart';
import 'package:my_windows_plugin/my_windows_plugin_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockMyWindowsPluginPlatform
    with MockPlatformInterfaceMixin
    implements MyWindowsPluginPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final MyWindowsPluginPlatform initialPlatform = MyWindowsPluginPlatform.instance;

  test('$MethodChannelMyWindowsPlugin is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelMyWindowsPlugin>());
  });

  test('getPlatformVersion', () async {
    MyWindowsPlugin myWindowsPlugin = MyWindowsPlugin();
    MockMyWindowsPluginPlatform fakePlatform = MockMyWindowsPluginPlatform();
    MyWindowsPluginPlatform.instance = fakePlatform;

    expect(await myWindowsPlugin.getPlatformVersion(), '42');
  });
}
