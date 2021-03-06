// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2017                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#pragma once
#include <boost/array.hpp>
#include <string>
#include <iterator>

namespace cryptox {
	namespace detail {
		template <class InputIterator, class OutputIterator>
		OutputIterator copy_hex_string(InputIterator first, InputIterator last, OutputIterator d_first) {
			for (size_t i=0; first != last; ++i) {
				const bool high_nibble = (i%2 == 0);
				*d_first++ = "0123456789abcdef"[*first >> 4*high_nibble & 0x0f];
				if (!high_nibble)
					++first;
			}

			return d_first;
		}

		template <class InputIterator>
		std::string hex_string(InputIterator first, InputIterator last) {
			std::string result;
			detail::copy_hex_string(first, last, std::back_inserter(result));
			return result;
		}

		template <class T>
		std::string hex_string(const T& x) {
			return hex_string(x.begin(), x.end());
		}
	}

	template <class InputIterator>
	std::string to_hex(InputIterator first, InputIterator last) {
		return detail::hex_string(first, last);
	}

	template <typename T>
	std::string to_hex(const T& x) {
		return detail::hex_string(x);
	}

	template <class Generator>
	class to_hex_decorator {
		const Generator& _generator;
	public:
		to_hex_decorator(const Generator& generator)
		 : _generator(generator) {}

		template <typename T>
		std::string operator()(const T& x) const {
			return to_hex(_generator(x));
		}
	};

	using detail::hex_string;
}
