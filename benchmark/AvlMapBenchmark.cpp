#include <benchmark/benchmark.h>

#include <random>
#include <map>
#include <unordered_map>
#include "../include/avl_map.h"

#define RANGE_MULT  2
#define RANGE_MIN   1<<10
#define RANGE_MAX   1024<<10

class MapBenchmarkFixture : public benchmark::Fixture {
protected:
    virtual void SetUp(benchmark::State& state) {
        std::random_device rd;
        gen.seed(rd());
        dist.param(
                std::uniform_int_distribution<>::param_type(0, state.range(0))
        );

        for (int i = 0; i <= state.range(0); i++) {
            rb_mo.emplace(i, i);
            avl_mo.emplace(i, i);
        }

        int i = 0;
        while(rb_mr.size() < state.range(0)) {
            auto num = gen();
            if (rb_mr.emplace(num,num).second){
                index.emplace(i++,num);
                avl_mr.emplace(num,num);
            }
        }
    }

    std::unordered_map<int,int> index;
    std::map<int,int> rb_mo, rb_mr;
    not_std::map<int,int> avl_mo, avl_mr;

    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapOrderedInsertion)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        rb_mo.erase(state.range(0));

        state.ResumeTiming();
        rb_mo.emplace(state.range(0), state.range(0));
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapOrderedInsertion)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapOrderedInsertion)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        avl_mo.erase(state.range(0));

        state.ResumeTiming();
        avl_mo.emplace(state.range(0), state.range(0));
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapOrderedInsertion)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapRandomInsertion)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto num = gen();
        while(rb_mr.count(num))
            num = gen();

        state.ResumeTiming();
        rb_mr.emplace(num, num);

        state.PauseTiming();
        rb_mr.erase(num);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapRandomInsertion)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapRandomInsertion)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto num = gen();
        while(avl_mr.count(num))
            num = gen();

        state.ResumeTiming();
        avl_mr.emplace(num, num);

        state.PauseTiming();
        avl_mr.erase(num);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapRandomInsertion)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapAccess)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto key = index[dist(gen)];

        state.ResumeTiming();
        auto res = rb_mr[key];
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapAccess)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapAccess)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto key = index[dist(gen)];

        state.ResumeTiming();
        auto res = avl_mr[key];
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapAccess)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, RbMapErase)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto key = index[dist(gen)];

        state.ResumeTiming();
        rb_mr.erase(key);

        state.PauseTiming();
        rb_mr.emplace(key, key);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, RbMapErase)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_DEFINE_F(MapBenchmarkFixture, AvlMapErase)(benchmark::State& state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        auto key = index[dist(gen)];

        state.ResumeTiming();
        avl_mr.erase(key);

        state.PauseTiming();
        avl_mr.emplace(key, key);
    }
}
BENCHMARK_REGISTER_F(MapBenchmarkFixture, AvlMapErase)
        ->RangeMultiplier(RANGE_MULT)
        ->Range(RANGE_MIN, RANGE_MAX);

BENCHMARK_MAIN();
