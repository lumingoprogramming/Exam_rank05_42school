#include "bigint.hpp"
#include <iostream>

static void section(const std::string& title)
{
    std::cout << "\n===== " << title << " =====" << std::endl;
}

int main()
{
    section("CONSTRUCTORS");

    bigint a;            // default -> 0
    bigint b(0u);        // explicit unsigned zero
    bigint c(42u);
    bigint d(1337u);
    bigint e(d);         // copy

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    section("ADDITION");

    std::cout << "42 + 21 = "
              << (bigint(42u) + bigint(21u)) << std::endl;

    std::cout << "0 + 0 = "
              << (bigint(0u) + bigint(0u)) << std::endl;

    std::cout << "999 + 1 = "
              << (bigint("999") + bigint("1")) << std::endl;

    std::cout << "1 + 999 = "
              << (bigint("1") + bigint("999")) << std::endl;

    bigint big1("1000000000000000000000000000000000000000000");
    bigint big2("999999999999999999999999999999999999999999");

    std::cout << "big1 + big2 = "
              << (big1 + big2) << std::endl;

    section("INCREMENT");

    bigint inc(9u);
    std::cout << "inc = " << inc << std::endl;
    std::cout << "++inc = " << ++inc << std::endl;
    std::cout << "inc++ = " << inc++ << std::endl;
    std::cout << "inc = " << inc << std::endl;

    section("DIGIT SHIFT LEFT");

    bigint x(42u);
    std::cout << "42 << 0 = " << (x << 0u) << std::endl;
    std::cout << "42 << 1 = " << (x << 1u) << std::endl;
    std::cout << "42 << 3 = " << (x << 3u) << std::endl;

    bigint z;
    z <<= 10u;
    std::cout << "0 << 10 = " << z << std::endl;

    section("DIGIT SHIFT RIGHT");

    bigint y(1337u);
    std::cout << "1337 >> 1 = " << (y >> 1u) << std::endl;
    std::cout << "1337 >> 2 = " << (y >> 2u) << std::endl;
    std::cout << "1337 >> 4 = " << (y >> 4u) << std::endl;

    bigint r(100u);
    r >>= 10u;
    std::cout << "100 >> 10 = " << r << std::endl;

    section("NO LEADING ZEROS");

    bigint lead("00000000042");
    std::cout << "normalized = " << lead << std::endl;

    bigint zero("0000");
    std::cout << "zero = " << zero << std::endl;

    section("COMPARISONS");

    bigint p("999");
    bigint q("1000");

    std::cout << "(999 < 1000)  = " << (p < q) << std::endl;
    std::cout << "(999 <= 1000) = " << (p <= q) << std::endl;
    std::cout << "(999 > 1000)  = " << (p > q) << std::endl;
    std::cout << "(999 >= 1000) = " << (p >= q) << std::endl;
    std::cout << "(999 == 1000) = " << (p == q) << std::endl;
    std::cout << "(999 != 1000) = " << (p != q) << std::endl;

    section("SELF CONSISTENCY");

    bigint s("1");
    for (int i = 0; i < 50; ++i)
        s <<= 1u;

    for (int i = 0; i < 50; ++i)
        s >>= 1u;

    std::cout << "after <<50 then >>50: " << s << std::endl;

    return 0;
}
