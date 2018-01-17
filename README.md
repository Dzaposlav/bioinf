# Computing the Longest Common Prefix Array Based on the Burrows-Wheeler Transform.

[![License](https://img.shields.io/packagist/l/doctrine/orm.svg)](https://img.shields.io/packagist/l/doctrine/orm.svg)

Project assignment for [Bioinformatics course](http://www.fer.unizg.hr/predmet/bio) at University of Zagreb, Faculty of Electrical Engineering and Computing (UNIZG FER), academic year 2017/2018.

## Authors
- [Frane Džapo](https://github.com/Dzaposlav)
- [Darko Dašić](https://github.com/ledasko)

## Instructions

#### Getting started
```bash
git clone https://github.com/Dzaposlav/bioinf
cd bioinf
chmod +x scripts/*
```

#### Compilation
```bash
bash scripts/compile.sh
```
#### Usage
```
./bioinf input_file
```
#### File structure
Input file must be in [FASTA format](https://en.wikipedia.org/wiki/FASTA_format)

#### Create and download files
```bash
scripts/dl_bacteria.sh
scripts/gen_all.sh
```
This will download DNA FASTA file of four bacterias into bacterias folder, generate synthetic files of varying lengths (100-1M) into synth folder and generate commands of varying number of commands.

#### Example run
```bash
./bioinf synth/example_1000.fa
```

#### Testing
Testing is done via python script which takes files to test as arguments
```bash
python3 scripts/tests.py file1 [, file2, ...]
```


License
---------
MIT License

Copyright (c) 2017 Frane Džapo, Darko Dašić
