#include <random>

#include <benchmark/benchmark.h>
#include "../include/avl_map.h"

class MapBenchmarkFixture : public benchmark::Fixture { };

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapOrderedInsertion)(benchmark::State& state) {
    std::map<int,int> m;
    for (int i = 0; i < state.range(0); i++)
        m.emplace(i,i);

    while (state.KeepRunning())
        m.emplace(state.range(0),state.range(0));
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapOrderedInsertion)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapOrderedInsertion)(benchmark::State& state) {
    not_std::map<int,int> m;
    for (int i = 0; i < state.range(0); i++)
        m.emplace(i,i);

    while (state.KeepRunning())
        m.emplace(state.range(0),state.range(0));
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapOrderedInsertion)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapRandomInsertion)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(m.count(num))
        num = gen();

    while (state.KeepRunning())
        m.emplace(num, num);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapRandomInsertion)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapRandomInsertion)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    not_std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(m.count(num))
        num = gen();

    while (state.KeepRunning())
        m.emplace(num, num);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapRandomInsertion)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapAccess)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(!m.count(num))
        num = gen();

    while (state.KeepRunning())
        auto res = m[num];
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapAccess)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapAccess)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    not_std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(!m.count(num))
        num = gen();

    while (state.KeepRunning())
        auto res = m[num];
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapAccess)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapErase)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(!m.count(num))
        num = gen();

    while (state.KeepRunning())
            m.erase(num);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapErase)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapErase)(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    not_std::map<int,int> m;

    while(m.size() < state.range(0)) {
        auto num = gen();
        m.emplace(num,num);
    }

    auto num = gen();
    while(!m.count(num))
        num = gen();

    while (state.KeepRunning())
        m.erase(num);
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapErase)
        ->RangeMultiplier(2)
        ->Range(1<<10,1024<<10);

BENCHMARK_MAIN();
