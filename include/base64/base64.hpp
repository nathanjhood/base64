/**
 * @file base64.h
 * @author René Nyffenegger (rene.nyffenegger@adp-gmbh.ch)
 * @author Nathan J. Hood   (nathanjhood@googlemail.com)
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (C) 2004-2008 René Nyffenegger (original functions)
 * @copyright Copyright (C) 2023       Nathan J. Hood  (revisions)
 *
 * This source code is provided 'as-is', without any express or implied
 * warranty. In no event will the author be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented; you must not
 *    claim that you wrote the original source code. If you use this source code
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original source code.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <vector>
#include <string>

/**
 * @brief The base64 namespace.
 *
 */
namespace base64 {

#define BASE64_ALPHABET(_) \
  ( (_) == 'A' ? 0  \
  : (_) == 'B' ? 1  \
  : (_) == 'C' ? 2  \
  : (_) == 'D' ? 3  \
  : (_) == 'E' ? 4  \
  : (_) == 'F' ? 5  \
  : (_) == 'G' ? 6  \
  : (_) == 'H' ? 7  \
  : (_) == 'I' ? 8  \
  : (_) == 'J' ? 9  \
  : (_) == 'K' ? 10 \
  : (_) == 'L' ? 11 \
  : (_) == 'M' ? 12 \
  : (_) == 'N' ? 13 \
  : (_) == 'O' ? 14 \
  : (_) == 'P' ? 15 \
  : (_) == 'Q' ? 16 \
  : (_) == 'R' ? 17 \
  : (_) == 'S' ? 18 \
  : (_) == 'T' ? 19 \
  : (_) == 'U' ? 20 \
  : (_) == 'V' ? 21 \
  : (_) == 'W' ? 22 \
  : (_) == 'X' ? 23 \
  : (_) == 'Y' ? 24 \
  : (_) == 'Z' ? 25 \
  : (_) == 'a' ? 26 \
  : (_) == 'b' ? 27 \
  : (_) == 'c' ? 28                            \
  : (_) == 'd' ? 29                            \
  : (_) == 'e' ? 30                            \
  : (_) == 'f' ? 31                            \
  : (_) == 'g' ? 32                            \
  : (_) == 'h' ? 33                            \
  : (_) == 'i' ? 34                            \
  : (_) == 'j' ? 35                            \
  : (_) == 'k' ? 36                            \
  : (_) == 'l' ? 37                            \
  : (_) == 'm' ? 38                            \
  : (_) == 'n' ? 39                            \
  : (_) == 'o' ? 40                            \
  : (_) == 'p' ? 41                            \
  : (_) == 'q' ? 42                            \
  : (_) == 'r' ? 43                            \
  : (_) == 's' ? 44                            \
  : (_) == 't' ? 45                            \
  : (_) == 'u' ? 46                            \
  : (_) == 'v' ? 47                            \
  : (_) == 'w' ? 48                            \
  : (_) == 'x' ? 49                            \
  : (_) == 'y' ? 50                            \
  : (_) == 'z' ? 51                            \
  : (_) == '0' ? 52                            \
  : (_) == '1' ? 53                            \
  : (_) == '2' ? 54                            \
  : (_) == '3' ? 55                            \
  : (_) == '4' ? 56                            \
  : (_) == '5' ? 57                            \
  : (_) == '6' ? 58                            \
  : (_) == '7' ? 59                            \
  : (_) == '8' ? 60                            \
  : (_) == '9' ? 61                            \
  : (_) == '+' ? 62                            \
  : (_) == '/' ? 63                            \
  : -1)

static signed char const byte64_to_int[256] = {
  BASE64_ALPHABET(0),   BASE64_ALPHABET(1),   BASE64_ALPHABET(2),   BASE64_ALPHABET(3),
  BASE64_ALPHABET(4),   BASE64_ALPHABET(5),   BASE64_ALPHABET(6),   BASE64_ALPHABET(7),
  BASE64_ALPHABET(8),   BASE64_ALPHABET(9),   BASE64_ALPHABET(10),  BASE64_ALPHABET(11),
  BASE64_ALPHABET(12),  BASE64_ALPHABET(13),  BASE64_ALPHABET(14),  BASE64_ALPHABET(15),
  BASE64_ALPHABET(16),  BASE64_ALPHABET(17),  BASE64_ALPHABET(18),  BASE64_ALPHABET(19),
  BASE64_ALPHABET(20),  BASE64_ALPHABET(21),  BASE64_ALPHABET(22),  BASE64_ALPHABET(23),
  BASE64_ALPHABET(24),  BASE64_ALPHABET(25),  BASE64_ALPHABET(26),  BASE64_ALPHABET(27),
  BASE64_ALPHABET(28),  BASE64_ALPHABET(29),  BASE64_ALPHABET(30),  BASE64_ALPHABET(31),
  BASE64_ALPHABET(32),  BASE64_ALPHABET(33),  BASE64_ALPHABET(34),  BASE64_ALPHABET(35),
  BASE64_ALPHABET(36),  BASE64_ALPHABET(37),  BASE64_ALPHABET(38),  BASE64_ALPHABET(39),
  BASE64_ALPHABET(40),  BASE64_ALPHABET(41),  BASE64_ALPHABET(42),  BASE64_ALPHABET(43),
  BASE64_ALPHABET(44),  BASE64_ALPHABET(45),  BASE64_ALPHABET(46),  BASE64_ALPHABET(47),
  BASE64_ALPHABET(48),  BASE64_ALPHABET(49),  BASE64_ALPHABET(50),  BASE64_ALPHABET(51),
  BASE64_ALPHABET(52),  BASE64_ALPHABET(53),  BASE64_ALPHABET(54),  BASE64_ALPHABET(55),
  BASE64_ALPHABET(56),  BASE64_ALPHABET(57),  BASE64_ALPHABET(58),  BASE64_ALPHABET(59),
  BASE64_ALPHABET(60),  BASE64_ALPHABET(61),  BASE64_ALPHABET(62),  BASE64_ALPHABET(63),
  BASE64_ALPHABET(64),  BASE64_ALPHABET(65),  BASE64_ALPHABET(66),  BASE64_ALPHABET(67),
  BASE64_ALPHABET(68),  BASE64_ALPHABET(69),  BASE64_ALPHABET(70),  BASE64_ALPHABET(71),
  BASE64_ALPHABET(72),  BASE64_ALPHABET(73),  BASE64_ALPHABET(74),  BASE64_ALPHABET(75),
  BASE64_ALPHABET(76),  BASE64_ALPHABET(77),  BASE64_ALPHABET(78),  BASE64_ALPHABET(79),
  BASE64_ALPHABET(80),  BASE64_ALPHABET(81),  BASE64_ALPHABET(82),  BASE64_ALPHABET(83),
  BASE64_ALPHABET(84),  BASE64_ALPHABET(85),  BASE64_ALPHABET(86),  BASE64_ALPHABET(87),
  BASE64_ALPHABET(88),  BASE64_ALPHABET(89),  BASE64_ALPHABET(90),  BASE64_ALPHABET(91),
  BASE64_ALPHABET(92),  BASE64_ALPHABET(93),  BASE64_ALPHABET(94),  BASE64_ALPHABET(95),
  BASE64_ALPHABET(96),  BASE64_ALPHABET(97),  BASE64_ALPHABET(98),  BASE64_ALPHABET(99),
  BASE64_ALPHABET(100), BASE64_ALPHABET(101), BASE64_ALPHABET(102), BASE64_ALPHABET(103),
  BASE64_ALPHABET(104), BASE64_ALPHABET(105), BASE64_ALPHABET(106), BASE64_ALPHABET(107),
  BASE64_ALPHABET(108), BASE64_ALPHABET(109), BASE64_ALPHABET(110), BASE64_ALPHABET(111),
  BASE64_ALPHABET(112), BASE64_ALPHABET(113), BASE64_ALPHABET(114), BASE64_ALPHABET(115),
  BASE64_ALPHABET(116), BASE64_ALPHABET(117), BASE64_ALPHABET(118), BASE64_ALPHABET(119),
  BASE64_ALPHABET(120), BASE64_ALPHABET(121), BASE64_ALPHABET(122), BASE64_ALPHABET(123),
  BASE64_ALPHABET(124), BASE64_ALPHABET(125), BASE64_ALPHABET(126), BASE64_ALPHABET(127),
  BASE64_ALPHABET(128), BASE64_ALPHABET(129), BASE64_ALPHABET(130), BASE64_ALPHABET(131),
  BASE64_ALPHABET(132), BASE64_ALPHABET(133), BASE64_ALPHABET(134), BASE64_ALPHABET(135),
  BASE64_ALPHABET(136), BASE64_ALPHABET(137), BASE64_ALPHABET(138), BASE64_ALPHABET(139),
  BASE64_ALPHABET(140), BASE64_ALPHABET(141), BASE64_ALPHABET(142), BASE64_ALPHABET(143),
  BASE64_ALPHABET(144), BASE64_ALPHABET(145), BASE64_ALPHABET(146), BASE64_ALPHABET(147),
  BASE64_ALPHABET(148), BASE64_ALPHABET(149), BASE64_ALPHABET(150), BASE64_ALPHABET(151),
  BASE64_ALPHABET(152), BASE64_ALPHABET(153), BASE64_ALPHABET(154), BASE64_ALPHABET(155),
  BASE64_ALPHABET(156), BASE64_ALPHABET(157), BASE64_ALPHABET(158), BASE64_ALPHABET(159),
  BASE64_ALPHABET(160), BASE64_ALPHABET(161), BASE64_ALPHABET(162), BASE64_ALPHABET(163),
  BASE64_ALPHABET(164), BASE64_ALPHABET(165), BASE64_ALPHABET(166), BASE64_ALPHABET(167),
  BASE64_ALPHABET(168), BASE64_ALPHABET(169), BASE64_ALPHABET(170), BASE64_ALPHABET(171),
  BASE64_ALPHABET(172), BASE64_ALPHABET(173), BASE64_ALPHABET(174), BASE64_ALPHABET(175),
  BASE64_ALPHABET(176), BASE64_ALPHABET(177), BASE64_ALPHABET(178), BASE64_ALPHABET(179),
  BASE64_ALPHABET(180), BASE64_ALPHABET(181), BASE64_ALPHABET(182), BASE64_ALPHABET(183),
  BASE64_ALPHABET(184), BASE64_ALPHABET(185), BASE64_ALPHABET(186), BASE64_ALPHABET(187),
  BASE64_ALPHABET(188), BASE64_ALPHABET(189), BASE64_ALPHABET(190), BASE64_ALPHABET(191),
  BASE64_ALPHABET(192), BASE64_ALPHABET(193), BASE64_ALPHABET(194), BASE64_ALPHABET(195),
  BASE64_ALPHABET(196), BASE64_ALPHABET(197), BASE64_ALPHABET(198), BASE64_ALPHABET(199),
  BASE64_ALPHABET(200), BASE64_ALPHABET(201), BASE64_ALPHABET(202), BASE64_ALPHABET(203),
  BASE64_ALPHABET(204), BASE64_ALPHABET(205), BASE64_ALPHABET(206), BASE64_ALPHABET(207),
  BASE64_ALPHABET(208), BASE64_ALPHABET(209), BASE64_ALPHABET(210), BASE64_ALPHABET(211),
  BASE64_ALPHABET(212), BASE64_ALPHABET(213), BASE64_ALPHABET(214), BASE64_ALPHABET(215),
  BASE64_ALPHABET(216), BASE64_ALPHABET(217), BASE64_ALPHABET(218), BASE64_ALPHABET(219),
  BASE64_ALPHABET(220), BASE64_ALPHABET(221), BASE64_ALPHABET(222), BASE64_ALPHABET(223),
  BASE64_ALPHABET(224), BASE64_ALPHABET(225), BASE64_ALPHABET(226), BASE64_ALPHABET(227),
  BASE64_ALPHABET(228), BASE64_ALPHABET(229), BASE64_ALPHABET(230), BASE64_ALPHABET(231),
  BASE64_ALPHABET(232), BASE64_ALPHABET(233), BASE64_ALPHABET(234), BASE64_ALPHABET(235),
  BASE64_ALPHABET(236), BASE64_ALPHABET(237), BASE64_ALPHABET(238), BASE64_ALPHABET(239),
  BASE64_ALPHABET(240), BASE64_ALPHABET(241), BASE64_ALPHABET(242), BASE64_ALPHABET(243),
  BASE64_ALPHABET(244), BASE64_ALPHABET(245), BASE64_ALPHABET(246), BASE64_ALPHABET(247),
  BASE64_ALPHABET(248), BASE64_ALPHABET(249), BASE64_ALPHABET(250), BASE64_ALPHABET(251),
  BASE64_ALPHABET(252), BASE64_ALPHABET(253), BASE64_ALPHABET(254), BASE64_ALPHABET(255)
};

/**
 * @brief The base64 data type.
 *
 */
typedef unsigned char BYTE;

/**
 * @brief Returns a base64-encoded std::string from an array (or std::vector) of unsigned chars.
 *
 * @param buf
 * @param bufLen
 * @return std::string
 *
 * @note This signature carries the actual function definition.
 */
std::string encode(const base64::BYTE* buf, unsigned int bufLen); // definition

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from another std::vector of unsigned chars.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::vector<base64::BYTE>& s);

/**
 * @brief Returns a base64-encoded std::string from another std::string.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string const& s);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::string& s);


// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if __cplusplus >= 201703L
/**
 * @brief Returns a base64-encoded std::string from an std::string_view.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string_view const& s);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string_view.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(std::string_view const& s); // overload (definition is static)

#endif // __cplusplus >= 201703L

} // namespace base64

#endif // BASE64_H_
