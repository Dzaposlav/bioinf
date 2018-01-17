#!/usr/bin/env bash

ALPHA='ACTG'

if [[ -d synth ]]; then
    rm -rf synth
fi
mkdir synth


len=10
while [[ ${len} -lt 1000000 ]]; do
    len=$((len*10))
    >&2 echo "Generating for length ${len}..."
    # create example
    ./scripts/gen_rand.sh ${len} ${ALPHA} > "./synth/example_${len}.in"
done

ALPHA='AHFEPNOIP'

if [[ -d alphabet ]]; then
    rm -rf alphabet
fi
mkdir alphabet


len=10
while [[ ${len} -lt 1000000 ]]; do
    len=$((len*10))
    >&2 echo "Generating for length ${len}..."
    # create example
    ./scripts/gen_rand.sh ${len} ${ALPHA} > "./alphabet/example_${len}.in"
done