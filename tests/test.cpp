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
  EXPECT_EQ(true, user->run("lsa || echo can i get 1--"));
  EXPECT_EQ(true, user->run("lsa ; echo hi"));
  EXPECT_EQ(false, user->run("echo no && lsa"));
  EXPECT_EQ(true, user->run("echo i hope i get 100 || lsa"));
  EXPECT_EQ(false, user->run("echo plz ; lsa"));

  EXPECT_EQ(true, user->run("ls ; pwd"));
  EXPECT_EQ(true, user->run("echo this is a lot of work  && pwd"));
  EXPECT_EQ(true, user->run("echo bye world || pwd"));

  EXPECT_EQ(true, user->run("echo hi || pwd"));
  EXPECT_EQ(true, user->run("echo hello world || pwd"));
  EXPECT_EQ(false, user->run("ls -z"));

  EXPECT_EQ(true, user->run("echo hi || #lsa"));
  EXPECT_EQ(true, user->run("echo hello && #sdf"));
  EXPECT_EQ(true, user->run("echo bye ; #asd"));
  EXPECT_EQ(true, user->run("echo see ya || # lsa"));
  EXPECT_EQ(true, user->run("echo okay && # sdf"));
  EXPECT_EQ(true, user->run("echo wow ; # asd"));

  EXPECT_EQ(false, user->run("ls-a && echo hi"));
  EXPECT_EQ(true, user->run("ls && exit"));
}

TEST(RShellTest, MultipleCommandTests) {
  User *user = new User();

  EXPECT_EQ(false, user->run("ls && echo hi || echo hello ; dir"));
  EXPECT_EQ(false, user->run("ls&& pwd || echo hello ; dir"));
  EXPECT_EQ(true, user->run("ls && echos hi || echo hello ; dir"));
  EXPECT_EQ(true, user->run("ls && pwd || echo hello ; exit"));
}

TEST(RShellTest, ParenthesesTest) {
  User *user = new User();

  EXPECT_EQ(false, user->run("(echo hi || #lsa)"));
  EXPECT_EQ(true, user->run("(echo hello) && (sdf)"));
  EXPECT_EQ(true, user->run("(echo bye ; asd)"));
  EXPECT_EQ(true, user->run("(echo see ya ||  ls) && pwda"));
  EXPECT_EQ(true, user->run("(echo okay && sdf || ls)"));
  EXPECT_EQ(true, user->run("echo hi && (echo wow ; asd)")); 
}

TEST(RShellTest, TestCommand) {
  User *user = new User();

  EXPECT_EQ(true, user->run("test"));
  EXPECT_EQ(true, user->run("test bin"));
  EXPECT_EQ(true, user->run("test -e bin"));
  EXPECT_EQ(false, user->run("test -f bin"));
  EXPECT_EQ(true, user->run("test -d bin"));
  EXPECT_EQ(false, user->run("test -e bind"));
  EXPECT_EQ(false, user->run("test -f bind"));
  EXPECT_EQ(false, user->run("test -d bind"));
  EXPECT_EQ(false, user->run("test bind"));

 
  EXPECT_EQ(false, user->run("[]"));
  EXPECT_EQ(false, user->run("[-e bin]"));
  EXPECT_EQ(false, user->run("[-e bin ]"));
  EXPECT_EQ(false, user->run("[ -e bin ]]"));
  EXPECT_EQ(true, user->run("[ -e bin ]"));
  EXPECT_EQ(true, user->run("[ bin ]"));
  EXPECT_EQ(false, user->run("[ -f bin ]"));
  EXPECT_EQ(true, user->run("[ -d bin ]"));
}

using namespace std;
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

