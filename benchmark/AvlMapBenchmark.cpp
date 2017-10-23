#include <random>

#include <benchmark/benchmark.h>
#include "../include/avl_map.h"

class MapBenchmarkFixture : public benchmark::Fixture { };

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapOrderedInsertion)(benchmark::State& state) {
    std::map<int,int> m;
    while (state.KeepRunning())
        for (int i = 0; i < state.range(0); i++)
            m.emplace(i,i);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapOrderedInsertion)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapOrderedInsertion)(benchmark::State& state) {
    not_std::map<int,int> m;
    while (state.KeepRunning())
        for (int i = 0; i < state.range(0); i++)
            m.emplace(i,i);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapOrderedInsertion)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapRandomInsertion)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    std::map<int,int> m;

    while(s.size() < state.range(0))
        s.emplace(gen());

    while (state.KeepRunning()) {
        for (auto it = s.begin(); it != s.end(); it++)
            m.emplace(*it, *it);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapRandomInsertion)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapRandomInsertion)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    not_std::map<int,int> m;

    while(s.size() < state.range(0))
        s.emplace(gen());

    while (state.KeepRunning())
        for (auto it = s.begin(); it != s.end(); it++)
            m.emplace(*it, *it);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapRandomInsertion)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapAccess)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    std::map<int,int> m;

    while(s.size() < state.range(0))
    {
        auto key = gen();
        if (s.emplace(key).second)
            m.emplace(key,key);
    }

    while (state.KeepRunning()) {
        for (auto it = s.begin(); it != s.end(); it++)
            auto res = m[*it];
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapAccess)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapAccess)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    not_std::map<int,int> m;

    while(s.size() < state.range(0))
    {
        auto key = gen();
        if (s.emplace(key).second)
            m.emplace(key,key);
    }

    while (state.KeepRunning()) {
        for (auto it = s.begin(); it != s.end(); it++)
            auto res = m[*it];
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapAccess)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapErase)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    std::map<int,int> m;

    while(s.size() < state.range(0))
    {
        auto key = gen();
        if (s.emplace(key).second)
            m.emplace(key,key);
    }

    while (state.KeepRunning()) {
        for (auto it = s.begin(); it != s.end(); it++)
            m.erase(*it);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapErase)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapErase)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::set<int> s;
    not_std::map<int,int> m;

    while(s.size() < state.range(0))
    {
        auto key = gen();
        if (s.emplace(key).second)
            m.emplace(key,key);
    }

    while (state.KeepRunning()) {
        for (auto it = s.begin(); it != s.end(); it++)
            m.erase(*it);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapErase)->RangeMultiplier(2)->Range(1024,1024<<10);

BENCHMARK_MAIN();
