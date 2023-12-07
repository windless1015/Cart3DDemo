
#ifndef CART3D_UTIL_STRING_SYSTEM_H
#define CART3D_UTIL_STRING_SYSTEM_H

#include <Cart3DCommonDefine.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>


namespace Cart3D {

    namespace string {

        /**
         * \brief Splits a string into parts
         * \details Splits the string \p in into a list of substrings \p out
         * wherever \p separator occurs.
         * \param[in] in the input string to split
         * \param[in] separator the separator character
         * \param[in] out the resulting list of substrings
         * \param[in] skip_empty_fields specifies whether empty parts should
         * be ignored and not stored in list \p out (this is true by default).
         * \see join_strings()
         */
		CART3D_COMMON_API void split(const std::string &in, char separator, std::vector<std::string> &out, bool skip_empty_fields = true);

        /**
         * \brief Splits a string into two parts.
         * \param[in] in the input string to split
         * \param[in] separator the separator character
         * \param[in] left the part of the input string on the left
         *   of the separator or the empty string if the separator
         *   did not appear in the input string
         * \param[in] right the right of the input string on the left
         *   of the separator or the empty string if the separator
         *   did not appear in the input string
         * \retval true if the separator was found in the input string
         * \retval false otherwise
         */
		CART3D_COMMON_API bool split(const std::string &in, char separator, std::string &left, std::string &right);

        /**
         * \brief Join multiple strings
         * \details Joins all the strings in list \p in into a single string
         * with each element separated by the given \p separator character.
         * \param[in] in the list of strings to join
         * \param[in] separator the separator character
         * \return the joined string
         * \see split_string()
         */
		CART3D_COMMON_API std::string join(const std::vector<std::string> &in, char separator);

        /**
         * \brief Join multiple strings
         * \details Joins all the strings in list \p in into a single string
         * with each element separated by the given \p separator string.
         * \param[in] in the list of strings to join
         * \param[in] separator the separator string (can be an empty string)
         * \return the joined string
         * \see split_string()
         */
		CART3D_COMMON_API std::string join(const std::vector<std::string> &in, const std::string &separator);

        /**
         * \brief Replaces the old sub-string by a new sub-string
         */
		CART3D_COMMON_API void replace(std::string &in, const std::string &old_substr, const std::string &new_substr);

        /**
         * \brief Converts a string to lowercase
         * \details The conversion is done in place in the string \p s.
         * \param[in,out] s The string to convert
         * \see to_uppercase()
         */
		CART3D_COMMON_API std::string to_lowercase(const std::string &s);

        /**
         * \brief Converts a string to uppercase
         * \details The conversion is done in place in the string \p s.
         * \param[in,out] s The string to convert
         * \see to_lowercase()
         */
		CART3D_COMMON_API std::string to_uppercase(const std::string &s);

        /**
         * \brief Creates a one char string
         * \param[in] c the character to convert to a string
         * \return a string that contains character \p c
         */
        inline std::string to_string(char c) {
            const char s[2] = { c, '\0' };
            return std::string(s);
        }

        /**
         * \brief Adds quotes to a string
         * \details Adds character \p quote at the beginning and the end of
         * string \p s and returns the resulting string.
         * \param[in] s the string to quote
         * \param[in] quotes the quoting char (default is '"')
         * \return the quoted string
         */
		CART3D_COMMON_API std::string quote(const std::string &s, char quotes = '\"');

        /**
         * \brief Checks if a string starts with a substring
         * \param[in] haystack the input string
         * \param[in] needle the substring to check
         * \return \c true if \p haystack starts with \p needle, \c false
         * otherwise.
         */
		CART3D_COMMON_API bool starts_with(const std::string &haystack, const std::string &needle);

        /**
         * \brief Checks if a string ends with a substring
         * \param[in] haystack the input string
         * \param[in] needle the substring to check
         * \return \c true if \p haystack ends with \p needle, \c false
         * otherwise.
         */
		CART3D_COMMON_API bool ends_with(const std::string &haystack, const std::string &needle);

        /**
         * \brief Converts an integer \p value to a string of a desired length.
         * \details Different from the std::to_string(), this method results in a fixed-width string by filling the
         *      missing parts with character \p fill.
         */
		CART3D_COMMON_API std::string to_string(int value, int width, char fill = '0');

        /**
         * Return a C++ string and work like printf.
         */
		CART3D_COMMON_API std::string printf(const char *format, ...);

        /**
         * @brief Appends the resulting string to a supplied string.
         */
		CART3D_COMMON_API void appendf(std::string &dst, const char *format, ...);

        /**
         * @brief Gets the time string, e.g., "Fri Jan 09 11:39:32 2015"
         */
		CART3D_COMMON_API std::string date_time();

        /**
         * @brief Converts \p time (in millisecond) into a string with the most suitable/readable unit.
         * The result will look like e.g., 88ms, 2.3s, 1.7m, 0.1h.
         */
		CART3D_COMMON_API std::string time(double time, int num_digits = 1);

        /**
         * @brief Converts from std::string to std::wstring.
         */
		CART3D_COMMON_API std::wstring to_wstring(const std::string &str);

        /**
         * @brief Converts from std::wstring to std::string.
         */
		CART3D_COMMON_API std::string from_wstring(const std::wstring &wstr);

    }

}


#endif

