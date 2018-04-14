// Copyright (c) 2016 Personal (Binbin Zhang)
// Created on 2016-11-08
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

#include "parse-option.h"
#include "fst.h"

int main(int argc, char* argv[]) {
  using xdecoder::Fst;
  using xdecoder::SymbolTable;
  using xdecoder::ParseOptions;
  const char *usage = "Convert Fst to dot format\n"
                      "Usage: aslp-fst-to-dot fsm_file\n"
                      "eg: aslp-fst-to-dot in.fsm\n";

  ParseOptions po(usage);
  std::string isymbols = "";
  po.Register("isymbols", &isymbols, "input symbol file");
  std::string osymbols = "";
  po.Register("osymbols", &osymbols, "output symbol file");

  po.Read(argc, argv);

  if (po.NumArgs() != 1) {
    po.PrintUsage();
    exit(1);
  }

  std::string fst_file = po.GetArg(1);
  SymbolTable isymbol_table(isymbols), osymbol_table(osymbols);
  Fst fst(fst_file);
  fst.Dot(isymbol_table, osymbol_table);
  return 0;
}

