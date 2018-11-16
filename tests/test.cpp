#include "../src/User.h"
#include "gtest/gtest.h"
#include <stdlib.h>
 
TEST(RShellTest, OneCommands) {
  User *user = new User();

  EXPECT_EQ(true, user->run("ls"));
  EXPECT_EQ(true, user->run("ls -a"));
  EXPECT_EQ(true, user->run("pwd"));
  EXPECT_EQ(true, user->run("echo hello world"));
  EXPECT_EQ(true, user->run("ls    "));
  EXPECT_EQ(true, user->run("      ls"));
  EXPECT_EQ(true, user->run("  ls    -a"));
  EXPECT_EQ(true, user->run("pwd asdfghjk"));
  EXPECT_EQ(false, user->run("ls -z"));
  EXPECT_EQ(false, user->run("asdfg"));
  EXPECT_EQ(false, user->run(";;;"));
  EXPECT_EQ(false, user->run("&&&"));
  EXPECT_EQ(false, user->run("|||"));

  EXPECT_EQ(false, user->run("||#lsa"));
  EXPECT_EQ(false, user->run("&&#sdf"));
  EXPECT_EQ(false, user->run(";#asd"));
  EXPECT_EQ(false, user->run("||# lsa"));
  EXPECT_EQ(false, user->run("&&# sdf"));
  EXPECT_EQ(false, user->run(";# asd"));

}

TEST(RShellTest, TwoCommandTests) {
  User *user = new User();
  
  EXPECT_EQ(false, user->run("lsa && ls"));
  EXPECT_EQ(true, user->run("lsa || ls"));
  EXPECT_EQ(true, user->run("lsa ; ls"));
  EXPECT_EQ(false, user->run("ls && lsa"));
  EXPECT_EQ(true, user->run("ls || lsa"));
  EXPECT_EQ(false, user->run("ls ; lsa"));

  EXPECT_EQ(true, user->run("ls ; pwd"));
  EXPECT_EQ(true, user->run("ls && pwd"));
  EXPECT_EQ(true, user->run("ls || pwd"));

  EXPECT_EQ(true, user->run("ls || pwd"));
  EXPECT_EQ(true, user->run("ls || pwd"));
  EXPECT_EQ(false, user->run("ls -z"));
  
  EXPECT_EQ(true, user->run("ls || #lsa"));
  EXPECT_EQ(true, user->run("ls && #sdf"));
  EXPECT_EQ(true, user->run("ls ; #asd"));
  EXPECT_EQ(true, user->run("ls || # lsa"));
  EXPECT_EQ(true, user->run("ls && # sdf"));
  EXPECT_EQ(true, user->run("ls ; # asd"));
}

TEST(RShellTest, MultipleCommandTests) {
  User* user = new User();

  EXPECT_EQ(true, user->run("ls && pwd || echo hello ; dir"));

}

using namespace std;
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}

