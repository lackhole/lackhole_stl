//
// Created by YongGyu Lee on 2021/07/11.
//

#ifndef LSD_TEST_H_
#define LSD_TEST_H_

#include <cstdio>
#include <cmath>

#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

namespace lsd {

class Tester {
 public:
  explicit Tester(std::string name) : test_name_(std::move(name)) {}
  ~Tester() {
    print_result();
  }

  void do_test(bool result, const char* source, int line) {
    if (result)
      test_data_.emplace_back("", line, result);
    else
      test_data_.emplace_back(source, line, result);
  }

  void do_test(bool result, const char* source, int line, std::string info) {
    if (result)
      test_data_.emplace_back("", line, result);
    else
      test_data_.emplace_back(source, line, result, std::move(info));
  }

  void print_result() const {
    std::vector<decltype(test_data_)::const_iterator> fails;

    for (auto it = test_data_.cbegin(); it != test_data_.cend(); ++it) {
      if (!it->success)
        fails.emplace_back(it);
    }
    print_result_impl(fails.begin(), fails.end());
  }

  int test_succeed() const {
    for (const auto& elem : test_data_) {
      if (!elem.success)
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

 private:
  template<typename It>
  void print_result_impl(It begin, It end) const {
    static constexpr const char* star60 = "............................................................";

    int failed_count = std::distance(begin, end);
    int succeed_count = static_cast<int>(test_data_.size()) - failed_count;

    std::stringstream ss;
    ss << '(' << std::to_string(test_data_.size() - failed_count) << " / " << test_data_.size() << ')';
    auto status = ss.str();

    std::cout
      << test_name_
      << star60 + std::min(static_cast<int>(status.size() + test_name_.size()), 60)
      << status
      << "\n";

    for (auto it = begin; it != end; ++it) {
      std::cout
          << "Test failed at " << (*it)->source
          << ", line " << (*it)->line;
      if (!(*it)->info.empty())
          std::cout << " (" << (*it)->info <<  ")";
      std::cout << '\n';
    }
  }

  enum class test_result { success, fail };
  struct tests {
    tests(const char* s, int line, bool r)
        : source(s), line(line), success(r) {}
    tests(const char* s, int line, bool r, std::string info)
        : source(s), line(line), success(r), info(std::move(info)) {}
    const char* source;
    int line;
    bool success;
    std::string info;
  };
  std::string test_name_;
  std::vector<tests> test_data_;
};

}

#define LSD_TEST_GET_FIRST_IMPL_1(x) x
#define LSD_TEST_GET_FIRST_IMPL_2(x, ...) x
#define LSD_TEST_GET_FIRST_IMPL(_1,_2,N,...) LSD_TEST_GET_FIRST_IMPL_##N
#define LSD_TEST_GET_FIRST(...) LSD_TEST_GET_FIRST_IMPL(__VA_ARGS__,2,1,0)(__VA_ARGS__)

#define LSD_TEST_GET_SECOND_OR_EMPTY_IMPL_1(x)
#define LSD_TEST_GET_SECOND_OR_EMPTY_IMPL_2(x, ...) , __VA_ARGS__
#define LSD_TEST_GET_SECOND_OR_EMPTY_IMPL(_1,_2,N,...) LSD_TEST_GET_SECOND_OR_EMPTY_IMPL_##N
#define LSD_TEST_GET_SECOND_OR_EMPTY(...) LSD_TEST_GET_SECOND_OR_EMPTY_IMPL(__VA_ARGS__,2,1,0)(__VA_ARGS__)

# define LSD_TEST_FILE_LINE_IMPL2(f, l) #l
# define LSD_TEST_FILE_LINE_IMPL(f, l) f ", line " #l
# define LSD_TEST_FILE_LINE LSD_TEST_FILE_LINE_IMPL(__FILE__, __LINE__)

# define LSD_TEST_MAKE_DUMMY_NAME_IMPL2(x, y) x ## y
# define LSD_TEST_MAKE_DUMMY_NAME_IMPL(x, y) LSD_TEST_MAKE_DUMMY_NAME_IMPL2(x, y)
# define LSD_TEST_MAKE_DUMMY_NAME(x) LSD_TEST_MAKE_DUMMY_NAME_IMPL(x, __COUNTER__)

# define LSD_TEST_DUMMY_NAME ss_$238be_$zzfe_

# define LSD_INIT_TEST(name) ::lsd::Tester LSD_TEST_DUMMY_NAME(name);
# define LSD_TEST(...) LSD_TEST_DUMMY_NAME.do_test(LSD_TEST_GET_FIRST(__VA_ARGS__), __FILE__, __LINE__ LSD_TEST_GET_SECOND_OR_EMPTY(__VA_ARGS__));
# define LSD_TEST_EQ(x, y) LSD_TEST_DUMMY_NAME.do_test((x) == (y), __FILE__, __LINE__);

# define LSD_TESTC(...) static_assert((__VA_ARGS__), " "); LSD_TEST(true) // if false this doesn't even compile.

# define LSD_TEST_CATCH(expr, excep)         \
try {                                       \
  (expr);                                   \
  LSD_TEST(false, "exception not thrown")    \
} catch (const excep&) {                    \
  LSD_TEST(true)                             \
} catch (...) {                             \
  LSD_TEST(false, "wrong exception thrown")  \
}

# define LSD_TEST_NOCATCH(expr)              \
try {                                       \
  (expr);                                   \
  LSD_TEST(true)                             \
} catch (...) {                             \
  LSD_TEST(false, "exception thrown")        \
}

# define LSD_TEST_RETURN return LSD_TEST_DUMMY_NAME.test_succeed();

// TODO: check real C++ language version

//# define LSD_TEST_MAKE_EXPR_TEST(expr) \
//template<typename

# define LSD_TEST_EXPR_VALID(expr)

#endif // LSD_TEST_H_
