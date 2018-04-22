// Copyright (c) 2018 Personal (Binbin Zhang)
// Created on 2018-04-22
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

#include "tree.h"

int main(int argc, char* argv[]) {
  using xdecoder::Tree;
  const char *usage = "convert text transition id to pdf file into xdecoder"
    "format file\n"
    "Refer to"
    "https://github.com/ling0322/pocketkaldi/blob/master/tool/extract_id2pdf.cc"
    "to get text transition id to pdf file\n"
    "Usage: transition-id-to-pdf text_file binary_file\n";

  if (argc != 3) {
    printf("%s", usage);
    return -1;
  }

  Tree tree;
  tree.ReadTransitionIdToPdfTextFile(argv[1]);
  tree.WriteTransitionToPdf(argv[2]);
  return 0;
}

