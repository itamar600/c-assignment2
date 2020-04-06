#pragma once

#include "doctest.h"
#include "FamilyTree.hpp"
//#include <string>



TEST_CASE("The classic case") {
  family::Tree T ("Yosef");
  T.addFather("Yosef", "Yaakov")
   .addMother("Yosef", "Rachel")
   .addFather("Yaakov", "Isaac")
   .addMother("Yaakov", "Rivca")
   .addFather("Isaac", "Avraham")
   .addMother("Isaac", "Sara");
}

TEST_CASE("The classic family - in a messy income order") {
  family::Tree T ("Yosef");
  T.addFather("Yosef", "Yaakov")
   .addFather("Yaakov", "Isaac")
   .addFather("Isaac", "Avraham")
   .addMother("Isaac", "Sara")
   .addMother("Yosef", "Rachel")
   .addMother("Yaakov", "Rivca");
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
}
