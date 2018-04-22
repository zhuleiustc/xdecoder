#!/usr/bin/bash

if [ $# != 2 ]; then 
    echo "Usage: convert_openfst_to_xdecoder_fst.sh kaldi_hclg xdecoder_fst" 
    exit 0;
fi

hclg=$1
xdecoder_fst=$2

openfst_txt_tempfile=$(mktemp /tmp/fst.XXXXXX)
fstprint $hclg > $openfst_txt_tempfile
./tools/fst-init $openfst_txt_tempfile $xdecoder_fst


