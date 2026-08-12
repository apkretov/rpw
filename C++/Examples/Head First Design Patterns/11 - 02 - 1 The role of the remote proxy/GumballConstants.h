#pragma once

#include <chrono>

namespace gumball_constants {
inline constexpr unsigned short kServerPort = 12345;
inline constexpr char kGetAllInfoRequest[] = "getAllInfo\n";
inline constexpr char kDefaultServerHost[] = "localhost";
inline constexpr char kDefaultMachineLocation[] = "Seattle";
inline constexpr int kDefaultMachineCount = 5;
inline constexpr std::size_t kSocketBufferSize = 1024;
inline constexpr std::chrono::milliseconds kServerStartupDelay = std::chrono::milliseconds(100);
} // namespace gumball_constants
