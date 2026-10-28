#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

using IpAddr = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

IpAddr parse_ip(const std::string& s);
IpAddr parse_line(const std::string& line);

void sort_reverse(std::vector<IpAddr>& ips);

std::ostream& operator<<(std::ostream& os, const IpAddr& ip);
void print_all(std::ostream& os, const std::vector<IpAddr>& ips);