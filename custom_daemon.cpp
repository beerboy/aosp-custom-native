/*
 * Custom Native Daemon for AOSP/AAOS
 *
 * This is a minimal native C++ process that:
 * - Runs as a system daemon
 * - Logs periodic heartbeat messages
 * - Demonstrates integration with Android logging system
 */

#include <android-base/logging.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

constexpr int HEARTBEAT_INTERVAL_SEC = 10;

int main(int argc, char** argv) {
    // Initialize Android logging
    android::base::InitLogging(argv, &android::base::KernelLogger);

    LOG(INFO) << "Custom Native Daemon starting...";
    LOG(INFO) << "Process ID: " << getpid();
    LOG(INFO) << "Heartbeat interval: " << HEARTBEAT_INTERVAL_SEC << " seconds";

    int heartbeat_count = 0;

    while (true) {
        heartbeat_count++;
        LOG(INFO) << "Heartbeat #" << heartbeat_count
                  << " - Custom daemon is alive";

        sleep(HEARTBEAT_INTERVAL_SEC);
    }

    // Unreachable code
    return 0;
}
