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

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <fstream>

#include "utils.h"

namespace xdecoder {

class Tree {
 public:
  Tree() {}
  // Refer to the following link to genertate transition id to pdf file
  // https://github.com/ling0322/pocketkaldi/blob/master/tool/extract_id2pdf.cc
  void ReadTransitionIdToPdfTextFile(const std::string& filename) {
    FILE *fp = fopen(filename.c_str(), "r");
    if (!fp) {
      ERROR("read file %s error, check!!!", filename.c_str());
    }
    int transition_id = 0, pdf_id = 0;
    char buffer[1024];
    while (fgets(buffer, 1024, fp)) {
      CHECK(transition_id >= 0);
      CHECK(pdf_id >= 0);
      if (sscanf(buffer, "%d %d", &transition_id, &pdf_id) == 2) {
        if (transition_id >=
             static_cast<int32_t>(transition_id_to_pdf_.size())) {
          transition_id_to_pdf_.resize(transition_id + 1);
        }
        transition_id_to_pdf_[transition_id] = pdf_id;
      } else {
        ERROR("unexpected line %s", buffer);
      }
    }
    printf("transition id in total %d\n",
           static_cast<int32_t>(transition_id_to_pdf_.size()));
    fclose(fp);
  }

  void ReadTransitionIdToPdf(const std::string& filename) {
    std::ifstream is(filename, std::ifstream::binary);
    if (is.fail()) {
      ERROR("read file %s error, check!!!", filename.c_str());
    }
    int32_t num_transitions = 0;
    ReadBasic(is, &num_transitions);
    transition_id_to_pdf_.resize(num_transitions);
    for (int32_t i = 0; i < num_transitions; i++) {
      ReadBasic(is, &transition_id_to_pdf_[i]);
    }
  }

  void WriteTransitionToPdf(const std::string& filename) const {
    std::ofstream os(filename, std::ofstream::binary);
    if (os.fail()) {
      ERROR("write file %s error, check!!!", filename.c_str());
    }
    int32_t num_transitions =
              static_cast<int32_t>(transition_id_to_pdf_.size());
    WriteBasic(os, num_transitions);
    for (int32_t i = 0; i < num_transitions; i++) {
      WriteBasic(os, transition_id_to_pdf_[i]);
    }
  }

  int32_t TransitionIdToPdf(int32_t transition_id) const {
    CHECK(transition_id < static_cast<int32_t>(transition_id_to_pdf_.size()));
    return transition_id_to_pdf_[transition_id];
  }

 private:
  std::vector<int32_t> transition_id_to_pdf_;
};

}  // namespace xdecoder

#endif  // TREE_H_
