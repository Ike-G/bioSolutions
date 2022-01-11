#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<int> oneInner(std::vector<int> v) {
    for (int i = v.size()-1; i >= 1; i--) {
        v[i] -= v[i-1];
        if (v[i] <= 0) v[i] += 26;
    }
    return v;
}

std::vector<int> oneForward(std::vector<int> v) {
    for (int i = 1; i < v.size(); i++) {
        v[i] += v[i-1];
        while (v[i] > 26) v[i] -= 26;
    }
    return v;
}

int oneTest(int n = 10000) {
    int l;
    int failed = 0;
    for (int i = 0; i < n; i++) {
        l = 1+rand()%10;
        std::vector<int> e(l);
        for (int& v : e) {
            v = 1+rand()%26;
        }
        if (oneForward(oneInner(e)) != e) {
            failed = 1;
        }
    }
    return failed;
}

int one() {
    std::string s;
    std::getline(std::cin, s);
    std::vector<int> v;
    for (char& c : s) v.push_back((int)c-64);
    for (int i = v.size()-1; i >= 1; i--) {
        v[i] -= v[i-1];
        if (v[i] <= 0) v[i] += 26;
    }
    for (int& i : v) std::cout << (char)(i+64);
    std::cout << "\n";
    return 0;
}

int two() {
    return 0;
}

int prod(std::vector<int>& v, int s) {
    int t = 1;
    for (int i = s; i < v.size(); i++) t*=v[i];
    return t;
}

std::vector<int> threeForward(std::vector<int> pl) {
    int n = pl.size();
    std::vector<int> arr(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = pl[i]; j < n; j++) {
            if (arr[j] == -1) {
                arr[j] = i;
                break;
            }
            if (j == n-1)
                return std::vector<int>{0};
        }
    }
    return arr;
}

std::vector<std::vector<int>> threeInner(std::vector<int> v) {
    int n = v.size();
    std::vector<std::vector<int>> ps(n, std::vector<int>());
    std::vector<int> pn(n,1);
    for (int j = 0; j < n; j++) {
        ps[v[j]].push_back(j);
        for (int k = 0; k < j; k++) {
            if (v[k] < v[j]) {
                ps[v[j]].push_back(k);
                pn[v[j]]++;
            }
        }
        std::sort(ps[v[j]].begin(), ps[v[j]].end());
    }
    int gs;
    int numPls = prod(pn,0);
    std::vector<std::vector<int>> pls(numPls, std::vector<int>(n));
    for (int i = 0; i < numPls; i++) {
        std::vector<int> o(n, 0);
        for (int j = 0; j < n; j++) {
            gs = prod(pn, j+1);
            while (i >= gs) {
                o[j]++;
                i -= gs;
            }
            pls[i][j] = ps[j][o[j]];
        }
    }
    return pls;
}

int threeTest(int n = 1000) {
    int cn;
    int failed = 0;
    std::vector<int> pl(cn), result;
    for (int i = 0; i < n; i++) {
        cn = 1+rand()%16;
        pl.clear();
        for (int j = 0; j < cn; j++) pl[i] = 1+rand()%16;
        result = threeForward(pl);
        if (result == std::vector<int>{0})
            continue;
        else {
            int present = 0;
            for (auto& v : threeInner(result)) {
                // TODO: FIX
                present |= v == result;
            }
            failed |= !present;
        }
    }
    return failed;
}

int three() {
    std::string rs;
    std::vector<int> v;
    int n = 0, i;
    getline(std::cin, rs);
    while (rs[n] != ' ') {
        v.push_back((int)rs[n]-97);
        n++;
    }
    std::vector<std::vector<int>> ps(n, std::vector<int>());
    std::vector<int> pn(n,1);
    i = std::stoi(rs.substr(n+1))-1;
    for (int j = 0; j < n; j++) {
        ps[v[j]].push_back(j);
        for (int k = 0; k < j; k++) {
            if (v[k] < v[j]) {
                ps[v[j]].push_back(k);
                pn[v[j]]++;
            }
        }
        std::sort(ps[v[j]].begin(), ps[v[j]].end());
    }
    int gs;
    std::vector<int> o(n, 0);
    for (int j = 0; j < n; j++) {
        gs = prod(pn, j+1);
        while (i >= gs) {
            o[j]++;
            i -= gs;
        }
        std::cout << static_cast<char>(ps[j][o[j]]+65);
    }
    return 0;
}

int main() {
    std::cout << "Isaac Glassbrook\n17\nBrighton College\nQuestion One\n";
    // std::cout << oneTest(999999) << "\n";
    // std::cout << threeTest();
    one();
    // two();
    // three();
    std::string nullstr;
    std::cin >> nullstr;
    return 0;
}
