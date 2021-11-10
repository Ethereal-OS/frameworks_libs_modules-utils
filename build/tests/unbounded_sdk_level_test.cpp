/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "android-modules-utils/sdk_level.h"
#include "android-modules-utils/unbounded_sdk_level.h"
#include <gtest/gtest.h>

namespace android {
namespace modules {
namespace sdklevel {
namespace unbounded {

class UnboundedSdkLevelTest : public ::testing::Test {
protected:
  UnboundedSdkLevelTest() {
    device_codename_ =
        android::base::GetProperty("ro.build.version.codename", "");
    device_api_level_ = android_get_device_api_level();
  }

  std::string device_codename_;
  int device_api_level_;
};

using UnboundedSdkLevelDeathTest = UnboundedSdkLevelTest;

TEST_F(UnboundedSdkLevelTest, IntegerVersionsTest) {
  EXPECT_TRUE(IsAtLeast("1"));
  EXPECT_TRUE(IsAtLeast("31"));
  EXPECT_TRUE(IsAtLeast(std::to_string(device_api_level_)));

  EXPECT_FALSE(IsAtLeast(std::to_string(device_api_level_ + 1)));
  EXPECT_FALSE(IsAtLeast(std::to_string(__ANDROID_API_FUTURE__)));
}

TEST_F(UnboundedSdkLevelDeathTest, EmptyVersionDeathTest) {
  EXPECT_DEATH(IsAtLeast(""), "");
}

TEST_F(UnboundedSdkLevelTest, CodenameVersionsTest) {
  if ("REL" == device_codename_) {
    GTEST_SKIP();
  }

  EXPECT_TRUE(IsAtLeast("R"));
  EXPECT_TRUE(IsAtLeast("S"));
  EXPECT_TRUE(IsAtLeast("Sv2"));
  EXPECT_TRUE(IsAtLeast("Tiramisu"));

  EXPECT_FALSE(IsAtLeast("Zzz"));
  EXPECT_FALSE(IsAtLeast("current"));
}

} // namespace unbounded
} // namespace sdklevel
} // namespace modules
} // namespace android