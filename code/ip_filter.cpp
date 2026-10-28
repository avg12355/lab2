#include "ip_filter.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

static std::vector<std::string> split_tab(const std::string& s) {
    std::vector<std::string> r;
    std::istringstream ss(s);
    std::string t;
    while (std::getline(ss, t, '\t')) {
        r.push_back(t);
    }
    return r;
}

IpAddr parse_ip(const std::string& s) {
    std::istringstream ss(s);
    std::string p;
    std::vector<int> nums;
    while (std::getline(ss, p, '.')) {
        int x = std::stoi(p);
        if (x < 0 || x > 255) {
            throw std::invalid_argument("bad octet: " + s);
        }
        nums.push_back(x);
    }
    if (nums.size() != 4) {
        throw std::invalid_argument("bad ip: " + s);
    }

    auto res = std::make_tuple(
        static_cast<uint8_t>(nums[0]),
        static_cast<uint8_t>(nums[1]),
        static_cast<uint8_t>(nums[2]),
        static_cast<uint8_t>(nums[3])
    );
    return res;
}

IpAddr parse_line(const std::string& line) {
    auto v = split_tab(line); 
    if (v.empty() || v.front().empty()) {
        throw std::invalid_argument("empty line");
    }
    return parse_ip(v.front());
}

void sort_reverse(std::vector<IpAddr>& ips) {
    std::sort(ips.begin(), ips.end(), [](const auto& a, const auto& b) {
        return a > b; 
    });
}

std::ostream& operator<<(std::ostream& os, const IpAddr& ip) {
    decltype(std::get<0>(ip)) b1 = std::get<0>(ip);
    decltype(std::get<1>(ip)) b2 = std::get<1>(ip);
    decltype(std::get<2>(ip)) b3 = std::get<2>(ip);
    decltype(std::get<3>(ip)) b4 = std::get<3>(ip);
    
    os << int(b1) << '.' << int(b2) << '.' << int(b3) << '.' << int(b4);
    return os;
}

void print_all(std::ostream& os, const std::vector<IpAddr>& ips) {
    for (const auto& ip : ips) {
        os << ip << '\n';
    }
}