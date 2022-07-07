// https://github.com/RefactoringGuru/design-patterns-cpp/blob/main/src/Strategy/Conceptual/main.cc

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>

template <class T>
concept is_range = requires(T& a) {
    std::begin(a);
    std::end(a);
};

// Interface for sorting algorithms
template <class Range, class T>
requires is_range<Range>
struct SortAlgorithm {
    virtual void operator ()(Range& range) const = 0;
};

template <class Range, class T>
struct AscendingSort : SortAlgorithm<Range, T> {
    void operator ()(Range& range) const override {
        std::sort(std::begin(range), std::end(range));
    }
};

template <class Range, class T>
struct DescendingSort : SortAlgorithm<Range, T> {
    void operator ()(Range& range) const override {
        std::sort(std::begin(range), std::end(range), std::greater<T>());
    }
};

class Context {
public:
    explicit Context(std::vector<int> nums)
        : _nums(std::move(nums)),
          _sort(new AscendingSort<std::vector<int>, int>) {}

    Context(std::vector<int> nums, SortAlgorithm<std::vector<int>, int>* sort)
        : _nums(std::move(nums)),
          _sort(sort) {}

    // Replace sorting algorithm with new algorithm
    void set_new_sort_algorithm(SortAlgorithm<std::vector<int>, int>* sort) {
        _sort.reset(sort);
    }

    void sort_nums() {
        (*_sort)(_nums);
    }

    void print_nums() const {
        for (auto& i : _nums)
            std::cout << i << ' ';

        std::cout << '\n';
    }

private:
    std::vector<int> _nums;

    // The Context maintains a reference to one of the
    // Strategy objects. The Context does not know the concrete class of a
    // strategy. It should work with all strategies via the Strategy interface.
    std::unique_ptr<SortAlgorithm<std::vector<int>, int>> _sort;
};

int main() {
    Context context{{5, 3, 6, 3, 7, 8, 5}, new AscendingSort<std::vector<int>, int>};
    context.sort_nums();
    context.print_nums();   // 3 3 5 5 6 7 8

    context.set_new_sort_algorithm(new DescendingSort<std::vector<int>, int>);

    context.sort_nums();
    context.print_nums();   // 8 7 6 5 5 3 3

    return 0;
}
