/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "fboss/agent/state/StateUtils.h"

#include <folly/Format.h>

#include "fboss/agent/FbossError.h"

namespace {
const std::string kTunIntfPrefix = "fboss";
} // anonymous namespace

namespace facebook {
namespace fboss {
namespace util {

std::string getCpp2EnumName(const std::string& enumValue) {
  auto pos = enumValue.find("::");
  if (pos == std::string::npos) {
    return enumValue;
  }

  return enumValue.substr(pos + 2);
}

bool isTunIntfName(std::string const& ifName) {
  return ifName.find(kTunIntfPrefix) == 0;
}

std::string createTunIntfName(InterfaceID ifID) {
  return folly::sformat("{}{}", kTunIntfPrefix, folly::to<std::string>(ifID));
}

InterfaceID getIDFromTunIntfName(std::string const& ifName) {
  if (not isTunIntfName(ifName)) {
    throw FbossError(ifName, " is not a valid tun interface");
  }

  return InterfaceID(atoi(ifName.substr(kTunIntfPrefix.size()).c_str()));
}

} // namespace util
} // namespace fboss
} // namespace facebook
