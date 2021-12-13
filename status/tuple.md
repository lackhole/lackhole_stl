## Header `<tuple>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/tuple)  
[Implementation](../ss/include/ss/tuple.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| tuple                                        | ![][cpp11]           | ![][notyet]                       |
| tuple_size                                   | ![][cpp11]           | ![][notyet]                       |
| tuple_element                                | ![][cpp11]           | ![][notyet]                       |
| ss::tuple_size\<ss::tuple>                   | ![][cpp11]           | ![][notyet]                       |
| ss::tuple_element\<ss::tuple>                | ![][cpp11]           | ![][notyet]                       |
| ss::uses_allocator\<ss::tuple>               | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| ignore                                       | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| make_tuple                                   | ![][cpp11]           | ![][notyet]                       |
| tie                                          | ![][cpp11]           | ![][notyet]                       |
| forward_as_tuple                             | ![][cpp11]           | ![][notyet]                       |
| tuple_cat                                    | ![][cpp11]           | ![][notyet]                       |
| ss::get(ss::tuple)                           | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator\<=~~ <br/>~~operator>~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][notyet]                       |
| ss::swap(ss::tuple)                          | ![][cpp11]           | ![][notyet]                       |
| apply                                        | ![][cpp17]           | ![][notyet]                       |
| make_from_tuple                              | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 13	| 0
	C++17: 2	| 0
	C++20: 1	| 0

	Total: 16	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red

[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue
[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue
[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue
[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue
[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
