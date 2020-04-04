#pragma once
#include "doctest.h"
#include "PhoneticFinder.hpp"
#include <string>
using namespace family;
using namespace std;



TEST_CASE("Test replacement of p and b and f") {
    string text = "xxx happy yyy";
    CHECK(find(text, "happy") == string("happy"));
    CHECK(find(text, "habby") == string("happy"));
    CHECK(find(text, "hapby") == string("happy"));
    CHECK(find(text, "habpy") == string("happy"));
    CHECK(find(text, "haffy") == string("happy"));
    CHECK(find(text, "hafby") == string("happy"));
    CHECK(find(text, "hapfy") == string("happy"));
    CHECK(find(text, "hafpy") == string("happy"));
    CHECK(find(text, "habfy") == string("happy"));
    CHECK(find(text, "haBBy") == string("happy"));
    CHECK(find(text, "hapBy") == string("happy"));
    CHECK(find(text, "haBpy") == string("happy"));
    CHECK(find(text, "haFFy") == string("happy"));
    CHECK(find(text, "haFby") == string("happy"));
    CHECK(find(text, "hapFy") == string("happy"));
    CHECK(find(text, "haFpy") == string("happy"));
    CHECK(find(text, "haBFy") == string("happy"));
}

TEST_CASE("Test replacement of lower-case and upper-case") {
    string text = "Happi xxx yyy";
    CHECK(find(text, "happi") == string("Happi"));
    CHECK(find(text, "Happi") == string("Happi"));
    CHECK(find(text, "HAPPI") == string("Happi"));
    CHECK(find(text, "HaPpI") == string("Happi"));
    CHECK(find(text, "hAppi") == string("Happi"));
    CHECK(find(text, "HappI") == string("Happi"));
    CHECK(find(text, "HAPpI") == string("Happi"));
    CHECK(find(text, "HaPPI") == string("Happi"));
    CHECK(find(text, "hAPpI") == string("Happi"));
    CHECK(find(text, "haPPI") == string("Happi"));
}

TEST_CASE("Test replacement of s and z and S and Z") {
    string text = "yyy xxx size";
    CHECK(find(text, "size") == string("size"));
    CHECK(find(text, "zize") == string("size"));
    CHECK(find(text, "sise") == string("size"));
    CHECK(find(text, "zise") == string("size"));
    CHECK(find(text, "Size") == string("size"));
    CHECK(find(text, "siZe") == string("size"));
    CHECK(find(text, "Zize") == string("size"));
    CHECK(find(text, "SiZe") == string("size"));
    CHECK(find(text, "ZiSe") == string("size"));
    CHECK(find(text, "Zise") == string("size"));
}

TEST_CASE("Test replacement of w and v and W and V") {
    string text = "wive wave xxx";
    CHECK(find(text, "wave") == string("wave"));
    CHECK(find(text, "wawe") == string("wave"));
    CHECK(find(text, "vawe") == string("wave"));
    CHECK(find(text, "vave") == string("wave"));
    CHECK(find(text, "Wave") == string("wave"));
    CHECK(find(text, "WaVe") == string("wave"));
    CHECK(find(text, "Vave") == string("wave"));
    CHECK(find(text, "vaWe") == string("wave"));
    CHECK(find(text, "waWe") == string("wave"));
    CHECK(find(text, "VaWe") == string("wave"));
}

TEST_CASE("Test replacement of g and j and G and J") {
    string text = "I want more giga byte";
    CHECK(find(text, "giga") == string("giga"));
    CHECK(find(text, "jiga") == string("giga"));
    CHECK(find(text, "gija") == string("giga"));
    CHECK(find(text, "jija") == string("giga"));
    CHECK(find(text, "Jiga") == string("giga"));
    CHECK(find(text, "JiJa") == string("giga"));
    CHECK(find(text, "giJa") == string("giga"));
    CHECK(find(text, "GiJa") == string("giga"));
    CHECK(find(text, "jiGa") == string("giga"));
    CHECK(find(text, "GiJa") == string("giga"));
}

TEST_CASE("Test replacement of d and t and D and T") {
    string text = "Detroit is a place";
    CHECK(find(text, "Detroit") == string("Detroit"));
    CHECK(find(text, "Dedroit") == string("Detroit"));
    CHECK(find(text, "Detroid") == string("Detroit"));
    CHECK(find(text, "tetroit") == string("Detroit"));
    CHECK(find(text, "Dedroid") == string("Detroit"));
    CHECK(find(text, "tedroit") == string("Detroit"));
    CHECK(find(text, "Tedroid") == string("Detroit"));
    CHECK(find(text, "DeDroit") == string("Detroit"));
    CHECK(find(text, "detroiD") == string("Detroit"));
    CHECK(find(text, "DeDroiD") == string("Detroit"));
    CHECK(find(text, "dedroiD") == string("Detroit"));
    CHECK(find(text, "DeDroid") == string("Detroit"));
}

TEST_CASE("Test replacement of o and u and O and U") {
    string text = "I want our giga byte";
    CHECK(find(text, "our") == string("our"));
    CHECK(find(text, "oor") == string("our"));
    CHECK(find(text, "uor") == string("our"));
    CHECK(find(text, "uur") == string("our"));
    CHECK(find(text, "oOr") == string("our"));
    CHECK(find(text, "Uur") == string("our"));
    CHECK(find(text, "UOr") == string("our"));
    CHECK(find(text, "uOr") == string("our"));
    CHECK(find(text, "OOr") == string("our"));
    CHECK(find(text, "UUr") == string("our"));
}

TEST_CASE("Test replacement of i and y and I and Y") {
    string text = "Iaely need to find problems";
    CHECK(find(text, "Iaely") == string("Iaely"));
    CHECK(find(text, "Iaeli") == string("Iaely"));
    CHECK(find(text, "yaely") == string("Iaely"));
    CHECK(find(text, "yaeli") == string("Iaely"));
    CHECK(find(text, "iaelY") == string("Iaely"));
    CHECK(find(text, "Yaely") == string("Iaely"));
    CHECK(find(text, "iaelI") == string("Iaely"));
    CHECK(find(text, "YaelI") == string("Iaely"));
    CHECK(find(text, "IaelI") == string("Iaely"));
    CHECK(find(text, "YaelY") == string("Iaely"));
}

TEST_CASE("Test replacement of c and k and q and C and K and Q") {
    string text = "Iaely want quaker";
    CHECK(find(text, "quaker") == string("quaker"));
    CHECK(find(text, "quacer") == string("quaker"));
    CHECK(find(text, "quaqer") == string("quaker"));
    CHECK(find(text, "kuaker") == string("quaker"));
    CHECK(find(text, "cuaker") == string("quaker"));
    CHECK(find(text, "kuacer") == string("quaker"));
    CHECK(find(text, "kuaqer") == string("quaker"));
    CHECK(find(text, "cuacer") == string("quaker"));
    CHECK(find(text, "cuaqer") == string("quaker"));
    CHECK(find(text, "quaCer") == string("quaker"));
    CHECK(find(text, "quaQer") == string("quaker"));
    CHECK(find(text, "Kuaker") == string("quaker"));
    CHECK(find(text, "Cuaker") == string("quaker"));
    CHECK(find(text, "KuaCer") == string("quaker"));
    CHECK(find(text, "KuaQer") == string("quaker"));
    CHECK(find(text, "CuaCer") == string("quaker"));
    CHECK(find(text, "CuaQer") == string("quaker"));
}