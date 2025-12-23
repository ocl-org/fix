/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_FIX_PARSER
#define __OCL_FIX_PARSER

#include <ocl/fix/detail/config.hpp>
#include <string>
#include <memory>

namespace ocl::fix
{

	class visitor;
	struct range;
	class range_buffer;

	/// @brief Buffer+Length structure
	using range_ptr_type = range*;
	using range_type	 = range;

	using tag_type	 = std::string;
	using value_type = std::string;


	struct range final
	{
		char*  bytes_{nullptr};
		size_t length_{};

		bool is_valid() noexcept
		{
			return this->bytes_ && this->length_ > 0;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief Convert range to usable string.
	/// @note This function assumes that the range is valid and contains ASCII bytes.
	inline std::string to_string(range& range) noexcept
	{
		if (range.length_ < 1)
			return std::string{};

		return std::string(range.bytes_, range.length_);
	}

	/// @brief a range object containing the FIX packet values.
	class range_buffer final
	{
	public:
		std::size_t					magic_len_{};
		std::string					magic_{};
		string_hash_map<value_type> message_{};

		static inline const char* begin;

		explicit range_buffer() = default;
		~range_buffer()			= default;

		range_buffer& operator=(const range_buffer&) = default;
		range_buffer(const range_buffer&)			 = default;

		[[nodiscard("please use the returned value of the tag.")]]
		value_type operator[](const tag_type& key)
		{
			if (key.empty())
				return value_type{};

			auto it = message_.find(key);
			if (it != message_.end())
				return it->second;

			return value_type{};
		}

		bool is_valid()
		{
			constexpr auto magic_tag = "8";
			return this->operator[](magic_tag).empty() == false;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief visitor object which returns a fix::range_buffer instance.
	class visitor final
	{
        struct impl;
        std::unique_ptr<impl> impl_;

	public:
		visitor();
        ~visitor();

        /// \brief Alias of visit.
		range_buffer operator()(const std::string& in);

		/// @brief Visits a FIX message and parse it into a range_buffer object.
		/// @param in The input FIX message as a string.
		/// @warning This function may throw exceptions.
		range_buffer visit(const std::string& in);
	};

} // namespace ocl::fix

#endif // ifndef __OCL_FIX_PARSER
