# aosp-custom-native

Custom native C++ daemon process for AOSP/AAOS (Android 14).

## Overview

This repository contains a minimal native C++ daemon that demonstrates:
- Integration with AOSP build system (Soong/Android.bp)
- System service lifecycle management (init.rc)
- Android logging integration (logcat)
- SELinux policy configuration

## Components

### 1. `custom_daemon.cpp`
Main source file implementing a simple daemon that:
- Logs periodic heartbeat messages every 10 seconds
- Uses Android's `libbase` logging framework
- Runs as a long-lived system service

### 2. `Android.bp`
Soong build system definition:
- Defines `custom_daemon` as a `cc_binary` module
- Links against `libbase` and `liblog`
- Specifies C++17 standard with strict warnings
- References `custom_daemon.rc` for init integration

### 3. `custom_daemon.rc`
Android init script:
- Defines the service configuration
- Specifies user/group (system/system)
- Configures service to start on boot

### 4. `sepolicy/`
SELinux policy files:
- `custom_daemon.te`: Type enforcement rules
- `file_contexts`: File path to security context mapping

## Integration with AOSP

This repository is designed to be placed at:
```
vendor/custom/native-process/
```

in the AOSP source tree via repo manifest.

### Manifest Entry

```xml
<project path="vendor/custom/native-process"
         name="aosp-custom-native"
         remote="github"
         revision="main" />
```

## Building

### Full AOSP Build
```bash
source build/envsetup.sh
lunch sdk_aaos_x86_64-eng
m custom_daemon
```

### Incremental Build (mmma)
```bash
mmma vendor/custom/native-process
```

## Deployment

After building, the daemon will be installed to:
- Binary: `/system/bin/custom_daemon`
- Init script: `/system/etc/init/custom_daemon.rc`

The service will start automatically on boot.

## Verification

Check if the daemon is running:
```bash
adb shell ps -A | grep custom_daemon
```

View daemon logs:
```bash
adb logcat | grep custom_daemon
```

Expected output:
```
I custom_daemon: Custom Native Daemon starting...
I custom_daemon: Process ID: 1234
I custom_daemon: Heartbeat interval: 10 seconds
I custom_daemon: Heartbeat #1 - Custom daemon is alive
I custom_daemon: Heartbeat #2 - Custom daemon is alive
...
```

## License

Apache License 2.0

## Author

Created for AOSP/AAOS custom development on Android 14.
