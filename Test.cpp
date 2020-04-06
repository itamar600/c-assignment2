
#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
// using namespace family;
using namespace std;





TEST_CASE("The classic case") {
  family::Tree T ("Yosef");
  T.addFather("Yosef", "Yaakov")
   .addMother("Yosef", "Rachel")
   .addFather("Yaakov", "Isaac")
   .addMother("Yaakov", "Rivca")
   .addFather("Isaac", "Avraham")
   .addMother("Isaac", "Sara");
   CHECK(T.relation("Yosef") == string("I"));
   CHECK(T.relation("Yaakov") == string("father"));
   CHECK(T.relation("Rachel") == string("mother"));
   CHECK(T.relation("Isaac") == string("grandfather"));
   CHECK(T.relation("Rivca") == string("grandmother"));
   CHECK(T.relation("Avraham") == string("great-grandfather"));
   CHECK(T.relation("Sara") == string("great-grandmother"));
   CHECK(T.relation("Ovadia") == string("unrelated"));
   CHECK(T.relation("sara") == string("unrelated"));

   CHECK(T.find("I") == string("Yosef"));
   CHECK(T.find("father") == string("Yaakov"));
   CHECK(T.find("mother") == string("Rachel"));
   CHECK(T.find("grandfather") == string("Isaac"));
   CHECK(T.find("grandmother") == string("Rivca"));
   CHECK(T.find("great-grandfather") == string("Avraham"));
   CHECK(T.find("great-grandmother") == string("Sara"));
   CHECK_THROWS_AS(T.find("great-great-grandmother"), std::exception);
}

TEST_CASE("The classic family - in a messy income order") {
  family::Tree T ("Yosef");
  T.addFather("Yosef", "Yaakov")
   .addFather("Yaakov", "Isaac")
   .addFather("Isaac", "Avraham")
   .addMother("Isaac", "Sara")
   .addMother("Yosef", "Rachel")
   .addMother("Yaakov", "Rivca");
   CHECK(T.relation("Yosef") == string("I"));
   CHECK(T.relation("Yaakov") == string("father"));
   CHECK(T.relation("Rachel") == string("mother"));
   CHECK(T.relation("Isaac") == string("grandfather"));
   CHECK(T.relation("Rivca") == string("grandmother"));
   CHECK(T.relation("Avraham") == string("great-grandfather"));
   CHECK(T.relation("Sara") == string("great-grandmother"));

   CHECK(T.find("I") == string("Yosef"));
   CHECK(T.find("father") == string("Yaakov"));
   CHECK(T.find("mother") == string("Rachel"));
   CHECK(T.find("grandfather") == string("Isaac"));
   CHECK(T.find("grandmother") == string("Rivca"));
   CHECK(T.find("great-grandfather") == string("Avraham"));
   CHECK(T.find("great-grandmother") == string("Sara"));
   CHECK_THROWS_AS(T.find("great-great-grandmother"), std::exception);
}

TEST_CASE("Incomplete family") {
  family::Tree T ("David");
  T.addMother("David", "Nitsevet")
   .addFather("David", "Ishay")
   .addFather("Ishay", "Oved")
   .addFather("Oved", "Boaz")
   .addMother("Oved", "Rut")
   .addFather("Boaz", "Salmon")
   .addFather("Salmon", "Nachshon")
   .addFather("Nachshon", "Aminadav")
   .addFather("Aminadav", "Ram")
   .addFather("Ram", "Hetsron")
   .addFather("Hetsron", "Perets")
   .addFather("Perets", "Yehuda")
   .addMother("Perets", "Tamar")
   .addFather("Oved", "Boaz Ivtsan")  // test an existing parent override
   .addFather("Nitsevet", "Adael");
   
   //check relation
   CHECK(T.relation("David") == string("I"));
   CHECK(T.relation("Ishay") == string("father"));
   CHECK(T.relation("Nitsevet") == string("mother"));
   CHECK(T.relation("Oved") == string("grandfather"));
   CHECK(T.relation("Adael") == string("grandfather"));
   CHECK(T.relation("Boaz Ivtsan") == string("great-grandfather"));
   CHECK(T.relation("Rut") == string("great-grandmother"));
   CHECK(T.relation("Salmon") == string("great-great-grandfather"));
   CHECK(T.relation("Nachshon") == string("great-great-great-grandfather"));
   CHECK(T.relation("Aminadav") == string("great-great-great-great-grandfather"));
   CHECK(T.relation("Ram") == string("great-great-great-great-great-grandfather"));
   CHECK(T.relation("Hetsron") == string("great-great-great-great-great-great-grandfather"));
   CHECK(T.relation("Yehuda") == string("great-great-great-great-great-great-great-grandfather"));
   CHECK(T.relation("Tamar") == string("great-great-great-great-great-great-great-grandmother"));
   CHECK(T.relation("Boaz") == string("unrelated"));
   CHECK(T.relation("") == string("unrelated"));
   
   //check find
   CHECK(T.find("I") == string("David"));
   CHECK(T.find("father") == string("Ishay"));
   CHECK(T.find("mother") == string("Nitsevet"));
   CHECK((T.find("grandfather") == string("Oved") || T.find("grandfather") == string("Adael")));
   CHECK(T.find("great-grandfather") == string("Boaz Ivtsan"));
   CHECK(T.find("great-grandmother") == string("Rut"));
   CHECK(T.find("great-great-grandfather") == string("Salmon"));
   CHECK(T.find("great-great-great-grandfather") == string("Nachshon"));
   CHECK(T.find("great-great-great-great-grandfather") == string("Aminadav"));
   CHECK(T.find("great-great-great-great-great-grandfather") == string("Ram"));
   CHECK(T.find("great-great-great-great-great-great-grandfather") == string("Hetsron"));
   CHECK(T.find("great-great-great-great-great-great-great-grandfather") == string("Yehuda"));
   CHECK(T.find("great-great-great-great-great-great-great-grandmother") == string("Tamar"));
   CHECK_THROWS_AS(T.find("great-great-great-great-grandmother"), std::exception);
   CHECK_THROWS_AS(T.find("great-great-great-great-great-great-great-great-grandmother"), std::exception);
   CHECK_THROWS_AS(T.find("grandmother"), std::exception);

   //check remove
   T.remove("Tamar");
   CHECK(T.relation("Tamar") == string("unrelated")); 
   CHECK_THROWS_AS(T.find("great-great-great-great-great-great-great-grandmother"), std::exception);
   T.remove("Ram");
   CHECK(T.relation("Ram") == string("unrelated"));
   CHECK(T.relation("Hetsron") == string("unrelated"));
   CHECK(T.relation("Yehuda") == string("unrelated"));
   CHECK(T.relation("Aminadav") == string("great-great-great-great-grandfather"));
   CHECK_THROWS_AS(T.find("great-great-great-great-great-grandfather"), std::exception);
   CHECK_THROWS_AS(T.find("great-great-great-great-great-great-grandfather"), std::exception);
   CHECK_THROWS_AS(T.find("great-great-great-great-great-great-great-grandfather"), std::exception);
   T.remove("Boaz Ivtsan");
   CHECK(T.relation("Rut") == string("great-grandmother"));
   CHECK(T.relation("Boaz Ivtsan") == string("unrelated"));
   CHECK(T.relation("Salmon") == string("unrelated"));
   CHECK(T.relation("Nachshon") == string("unrelated"));
   CHECK(T.relation("Aminadav") == string("unrelated"));
   CHECK_THROWS_AS(T.find("great-great-great-great-grandfather"), std::exception);
   CHECK_THROWS_AS(T.find("great-great-great-grandfather"), std::exception);
   CHECK_THROWS_AS(T.find("great-great-grandfather"), std::exception);
   CHECK_THROWS_AS(T.find("great-grandfather"), std::exception);
   T.addFather("Oved", "Boaz");
   CHECK(T.relation("Boaz") == string("great-grandfather"));
   T.remove("Adael");
   CHECK(T.find("grandfather") == string("Oved"));
}

TEST_CASE("Reccuring names") {
  family::Tree T ("Shimoni");
  T.addFather("Shimoni", "Shimon")
   .addMother("Shimoni", "Dina")
   .addFather("Shimon", "Yaakov")
   .addMother("Shimon", "Lea")
   .addFather("Dina", "Yaakov")
   .addMother("Dina", "Lea")
   .addMother("Lea", "Lea"); // Just for checking

   CHECK(T.relation("Shimoni") == string("I"));
   CHECK(T.relation("Shimon") == string("father"));
   CHECK(T.relation("Dina") == string("mother"));
   CHECK(T.relation("Yaakov") == string("grandfather"));
   CHECK((T.relation("Lea") == string("grandmother") || T.relation("Lea") == string("great-grandmother")));

   CHECK(T.find("I") == string("Shimoni"));
   CHECK(T.find("father") == string("Shimon"));
   CHECK(T.find("mother") == string("Dina"));
   CHECK(T.find("grandfather") == string("Yaakov"));
   CHECK(T.find("grandmother") == string("Lea"));
   CHECK(T.find("great-grandmother") == string("Lea"));
   CHECK_THROWS_AS(T.find("great-grandfather"), std::exception);
   
   T.remove("Yaakov");
   CHECK(T.relation("Yaakov") == string("grandfather"));
   CHECK(T.find("grandfather") == string("Yaakov"));

   T.remove("Lea");
   CHECK((T.relation("Lea") == string("grandmother") || T.relation("Lea") == string("great-grandmother")));
   CHECK(T.find("grandmother") == string("Lea"));
}

