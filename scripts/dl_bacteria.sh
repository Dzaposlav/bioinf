#!/usr/bin/env bash

# downloads bacteria fasta files

BASE_URL="ftp://ftp.ensemblgenomes.org/pub/bacteria/release-34/fasta/bacteria_0_collection"
BACTERIA="escherichia_coli_str_k_12_substr_mg1655/dna/Escherichia_coli_str_k_12_substr_mg1655.ASM584v2.dna.toplevel.fa.gz"

if [[ -d bacterias ]]; then
    echo "Bacterias already downloaded into folder bacterias"
    read -p "Do you want to download again? [y/N] " confirm && [[ ${confirm} == [yY] || ${confirm} == [yY][eE][sS] ]] || exit 1
    rm -rf bacterias
fi

mkdir bacterias

for bacteria in ${BACTERIA}; do
    URL=${BASE_URL}/${bacteria}
    wget -P bacterias ${URL}
done

gunzip bacterias/*
