// Copyright (c) 2018 Personal (Binbin Zhang)
// Created on 2018-04-09
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <stdio.h>

#include <sstream>

#include "utils.h"
#include "varint.h"

int main() {
  using xdecoder::Varint;
  CHECK(Varint::ZigzagToInt32(Varint::Int32ToZigzag(0)) == 0);
  CHECK(Varint::ZigzagToInt32(Varint::Int32ToZigzag(-1)) == -1);
  CHECK(Varint::ZigzagToInt32(Varint::Int32ToZigzag(9999)) == 9999);

  std::ostringstream os;
  CHECK(Varint::WriteInt32(os, 0) == 1);
  CHECK(Varint::WriteInt32(os, 128) == 2);
  CHECK(Varint::WriteInt32(os, 65536) == 3);
  CHECK(Varint::WriteInt32(os, 2147483647) == 5);  // 2^31 - 1
  CHECK(Varint::WriteInt32(os, -1) == 1);
  std::istringstream is(os.str());
  CHECK(Varint::ReadInt32(is) == 0);
  CHECK(Varint::ReadInt32(is) == 128);
  CHECK(Varint::ReadInt32(is) == 65536);
  CHECK(Varint::ReadInt32(is) == 2147483647);
  CHECK(Varint::ReadInt32(is) == -1);
  return 0;
}
