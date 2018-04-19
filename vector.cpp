#include <iostream>
#include <vector>

template <typename T>
std::vector<T> make_table(int n, T v) {
    return std::vector<T>(n, v);
}

template <typename... Args>
auto make_table(int n, Args... args) {
    auto val = make_table(std::forward<Args>(args)...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main() {
    // vector<vector<vector<ll>>>
    auto table_i = make_table(10, 10, 10, 1);
    auto table_ll = make_table(10, 10, 10, 2LL);
    
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            for(int k = 0; k < 10; ++k) {
                std::cout << table_i[i][j][k] << std::endl;
            }
        }
    }
}
