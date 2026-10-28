#include <gtest/gtest.h>
#include "ip_filter.h"
#include <algorithm>
#include <vector>

// Тест 1: Корректный парсинг
TEST(IpFilter, ParseOk) {
    auto ip = parse_ip("1.2.3.4");
    EXPECT_EQ(std::get<0>(ip), 1);
    EXPECT_EQ(std::get<1>(ip), 2);
    EXPECT_EQ(std::get<2>(ip), 3);
    EXPECT_EQ(std::get<3>(ip), 4);
}

// Тест 2: Парсинг с ошибками
TEST(IpFilter, ParseBad) {
    EXPECT_THROW(parse_ip("1.2.3"), std::invalid_argument);
    EXPECT_THROW(parse_ip("1.2.3.256"), std::invalid_argument);
    EXPECT_THROW(parse_ip("a.b.c.d"), std::invalid_argument);
}

// Тест 3: Сортировка (числовая, а не строковая)
TEST(IpFilter, SortRevNumeric) {
    std::vector<IpAddr> v = {
        parse_ip("1.1.1.1"),
        parse_ip("1.10.1.1"),
        parse_ip("1.2.1.1"),
    };
    sort_reverse(v);
    EXPECT_EQ(v[0], parse_ip("1.10.1.1"));
    EXPECT_EQ(v[1], parse_ip("1.2.1.1"));
    EXPECT_EQ(v[2], parse_ip("1.1.1.1"));
}

// Тест 4: Фильтрация по первому байту (копируем лямбду из main.cpp)
TEST(IpFilter, FilterFirstByte) {
    std::vector<IpAddr> v = {
        parse_ip("1.1.1.1"), 
        parse_ip("2.1.1.1"), 
        parse_ip("1.5.5.5"),
    };
    
    auto is_first_byte_1 = [](const IpAddr& ip) { 
        return std::get<0>(ip) == 1; 
    };

    std::vector<IpAddr> r;
    for (const auto& ip : v) {
        if (is_first_byte_1(ip)) r.push_back(ip);
    }
    
    ASSERT_EQ(r.size(), 2u);
    EXPECT_EQ(r[0], parse_ip("1.1.1.1"));
    EXPECT_EQ(r[1], parse_ip("1.5.5.5"));
}

// Тест 5: Фильтрация по двум первым байтам (копируем лямбду из main.cpp)
TEST(IpFilter, FilterTwoBytes) {
    std::vector<IpAddr> v = {
        parse_ip("46.70.1.1"), 
        parse_ip("46.71.1.1"), 
        parse_ip("47.70.1.1"),
    };

    auto is_46_70 = [](const IpAddr& ip) { 
        return std::get<0>(ip) == 46 && std::get<1>(ip) == 70; 
    };

    std::vector<IpAddr> r;
    for (const auto& ip : v) {
        if (is_46_70(ip)) r.push_back(ip);
    }
    
    ASSERT_EQ(r.size(), 1u);
    EXPECT_EQ(r[0], parse_ip("46.70.1.1"));
}

// Тест 6: Фильтрация по любому байту (копируем лямбду из main.cpp)
TEST(IpFilter, FilterAnyByte) {
    std::vector<IpAddr> v = {
        parse_ip("46.1.1.1"), 
        parse_ip("1.46.1.1"),
        parse_ip("1.1.46.1"), 
        parse_ip("1.1.1.46"), 
        parse_ip("1.1.1.1"),
    };

    auto has_byte_46 = [](const IpAddr& ip) {
        return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || 
               std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
    };

    std::vector<IpAddr> r;
    for (const auto& ip : v) {
        if (has_byte_46(ip)) r.push_back(ip);
    }
    
    EXPECT_EQ(r.size(), 4u);
}