#include "ip_filter.h"
#include <iostream>
#include <algorithm>
#include <iterator>

int main() {
    try {
        std::vector<IpAddr> pool;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            try {
                pool.push_back(parse_line(line));
            } catch (const std::exception&) {}
        }

        sort_reverse(pool);

        print_all(std::cout, pool);

        auto is_first_byte_1 = [](const IpAddr& ip) { 
            return std::get<0>(ip) == 1; 
        };
        for (const auto& ip : pool) {
            if (is_first_byte_1(ip)) std::cout << ip << '\n';
        }

        auto is_46_70 = [](const IpAddr& ip) { 
            return std::get<0>(ip) == 46 && std::get<1>(ip) == 70; 
        };
        for (const auto& ip : pool) {
            if (is_46_70(ip)) std::cout << ip << '\n';
        }

        auto has_byte_46 = [](const IpAddr& ip) {
            return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || 
                   std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
        };
        for (const auto& ip : pool) {
            if (has_byte_46(ip)) std::cout << ip << '\n';
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}