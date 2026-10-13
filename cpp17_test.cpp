// cpp17_test.cpp —— 检测编译器是否支持 C++17 及其常用特性
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <numeric>

int main() {
    std::cout << "=== C++ 编译环境检测 ===\n\n";

    // C++ 版本
    std::cout << "__cplusplus = " << __cplusplus << "  ";
    if (__cplusplus >= 201703L) {
        std::cout << "(C++17 或更高) OK\n";
    } else if (__cplusplus >= 201402L) {
        std::cout << "(C++14，不够，需要 C++17)\n";
    } else if (__cplusplus >= 201103L) {
        std::cout << "(C++11，不够)\n";
    } else {
        std::cout << "(老标准)\n";
    }

    // C++17 特性 1：结构化绑定
    std::cout << "\n[1] 结构化绑定 (C++17)  ";
    std::pair<int, std::string> p{42, "hello"};
    auto [num, text] = p;
    std::cout << "OK  ->  " << num << " " << text << "\n";

    // C++17 特性 2：if 初始化语句
    std::cout << "[2] if 初始化语句 (C++17)  ";
    if (std::map<std::string, int> m{{"a", 1}}; m.count("a")) {
        std::cout << "OK\n";
    } else {
        std::cout << "不支持\n";
    }

    // 常用 STL
    std::cout << "\n[3] 常用 STL 容器\n";
    std::vector<int> v{5, 2, 8, 1, 9};
    std::sort(v.begin(), v.end());
    std::cout << "    vector + sort:  ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    std::string s = "hello";
    s += " world";
    std::cout << "    string:         " << s << " (长度 " << s.size() << ")\n";

    std::map<std::string, int> score;
    score["alice"] = 90;
    score["bob"] = 85;
    std::cout << "    map:            alice=" << score["alice"]
              << " bob=" << score["bob"] << "\n";

    std::cout << "    accumulate:     " << std::accumulate(v.begin(), v.end(), 0) << "\n";

    // 竞赛常用输入输出
    std::cout << "\n[4] 竞赛输入输出 (cin/cout)\n";
    std::cout << "    cin >> a >> b;   读入\n";
    std::cout << "    cout << a << '\\n';  输出\n";

    // 范围 for（C++11 起）
    std::cout << "\n[5] 范围 for 循环  ";
    int sum = 0;
    for (int x : v) sum += x;
    std::cout << "OK  ->  和 = " << sum << "\n";

    std::cout << "\n=== 结论 ===\n";
    if (__cplusplus >= 201703L) {
        std::cout << "编译器支持 C++17，可以直接开始学。\n";
    } else {
        std::cout << "需要加编译选项，见 README。\n";
    }
    return 0;
}
