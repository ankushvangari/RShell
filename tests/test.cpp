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
  EXPECT_EQ(false, user->run("pwd;ls"));

}

using namespace std;
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}

