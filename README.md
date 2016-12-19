# CuteVCF
simple GUI viewer for [vcf file](https://samtools.github.io/hts-specs/VCFv4.2.pdf) (variant call format) using htslib. 
Only tested on Linux for now. But binary will come soon after compiling htslib on windows.

# Compile 
## From Qt Creator 
* Install Qt SDK 5.7 from https://www.qt.io/download/
* Open the CuteVcf.pro from Qt creator 
* Compile it and Run it 

## From Shell  

    qmake CuteVcf.pro 
    make 
