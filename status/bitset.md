## Header `<bitset>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/bitset)  
[Implementation](../include/lsd/bitset.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<string>                                    | ![][legacy]          | ![][notyet]                       |
| \<iosfwd>                                    | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| bitset                                       | ![][legacy]          | ![][notyet]                       |
| lsd::hash\<lsd::bitset>                        | ![][cpp11]           | ![][notyet]                       |
| **Forward declarations**                     |                      |                                   |
| hash                                         | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator& <br/>operator| <br/>operator^      | ![][legacy]          | ![][notyet]                       |
| operator\<\< <br/>operator>>                 | ![][legacy]          | ![][notyet]                       |


<!--
	C++11: 7	| 0

	Total: 7	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red
[legacy]: https://img.shields.io/badge/legacy-grey

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
